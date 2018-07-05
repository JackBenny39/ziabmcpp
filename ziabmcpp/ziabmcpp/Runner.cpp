// Runner.cpp
// Runner class

#include "stdafx.h"

#include <fstream>
#include <iostream>

#include "Runner.h"


Runner::Runner(Prc mpi, Step prime1, Step runSteps, Step writeInterval,
	bool provider, unsigned numProviders, Qty providerMaxQ, double pAlpha, double pDelta, double qProvide,
	bool taker, unsigned numTakers, Qty takerMaxQ, double tMu,
	bool informed, Step informedRun, Qty informedQ, double iMu, Side informedSide,
	bool jumper, double jAlpha,
	bool maker, unsigned numMMs, Qty mmMaxQ, unsigned mmQuotes, unsigned mmRange, double mmDelta,
	bool qTake, double lambda0, double whiteNoise, double cLambda, std::mt19937 &eng, unsigned seed) :
	mpi(mpi), prime1(prime1), runSteps(runSteps), writeInterval(writeInterval),
	provider(provider), numProviders(numProviders), providerMaxQ(providerMaxQ), pAlpha(pAlpha), pDelta(pDelta), qProvide(qProvide),
	taker(taker), numTakers(numTakers), takerMaxQ(takerMaxQ), tMu(tMu),
	informed(informed), informedRun(informedRun), informedQ(informedQ), iMu(iMu), informedSide(informedSide),
	jumper(jumper), jAlpha(jAlpha),
	maker(maker), numMMs(numMMs), mmMaxQ(mmMaxQ), mmQuotes(mmQuotes), mmRange(mmRange), mmDelta(mmDelta),
	qTake(qTake), lambda0(lambda0), whiteNoise(whiteNoise), cLambda(cLambda), engine(eng), seed(seed)
{
	defaultVec = { 1, 5, 10, 25, 50 };
	engine.seed(seed);

	exchange = Orderbook();
	if (jumper) { j1 = std::make_unique<PennyJumper>(1, 4000, 1, mpi); }
	QL = buildLambda();
}

int Runner::setMaxQ(int maxq)
{
	std::vector<int> actualVec(0);
	std::copy_if(defaultVec.begin(), defaultVec.end(), std::back_inserter(actualVec), [&maxq](int i) { return i <= maxq; });
	std::uniform_int_distribution<int> distUintV(0, actualVec.size() - 1);
	return actualVec[distUintV(engine)];
}

void Runner::buildProviders()
{
	std::exponential_distribution<double> distExpP(pAlpha);
	for (auto i = 0; i != numProviders; ++i)
	{
		auto size = setMaxQ(providerMaxQ);
		traderId tId = 1000 + i;
		if (mpi == 1)
			traderMap[tId] = std::make_shared<Provider>(static_cast<int>(floor(distExpP(engine) + 1)) * size, tId, size, pDelta, mpi);
//			bucket.push_back(std::make_shared<Provider>(static_cast<int>(floor(distExpP(engine) + 1)) * size, (1000 + i), size, pDelta, mpi));
		else
			traderMap[tId] = std::make_shared<Provider5>(static_cast<int>(floor(distExpP(engine) + 1)) * size, tId, size, pDelta, mpi);
//			bucket.push_back(std::make_shared<Provider5>(static_cast<int>(floor(distExpP(engine) + 1)) * size, (1000 + i), size, pDelta, mpi));
	}
}

void Runner::buildTakers()
{

	std::exponential_distribution<double> distExpT(tMu);
	for (auto i = 0; i != numTakers; ++i)
	{
		auto size = setMaxQ(takerMaxQ);
		traderId tId = 2000 + i;
		traderMap[tId] = std::make_shared<Taker>(static_cast<int>(floor(distExpT(engine) + 1)) * size, tId, size, mpi);
//		bucket.push_back(std::make_shared<Taker>(static_cast<int>(floor(distExpT(engine) + 1)) * size, (2000 + i), size, mpi));
	}
}

void Runner::buildInformed()
{
	int takerTrades = 0;
	int informedTrades;
	if (taker)
	{
		for (std::pair<traderId, std::shared_ptr<ZITrader>> x : traderMap)
		{
			if (x.second->traderType == 'T')
				takerTrades += x.second->orderSize * runSteps / x.second->arrInt;
		}
		informedTrades = static_cast<int>(floor(takerTrades * iMu));
	}
	else
		informedTrades = static_cast<int>(1 / iMu);

	std::uniform_int_distribution<int> distUintI(prime1, runSteps);
	traderMap[5000] = std::make_shared<Informed>(5000, informedQ, informedSide, informedRun, informedTrades, engine, distUintI);
//	bucket.push_back(std::make_shared<Informed>(5000, informedQ, informedSide, informedRun, informedTrades, engine, distUintI));
}

void Runner::buildMarketMakers()
{
	for (auto i = 0; i != numMMs; ++i)
	{
		auto size = setMaxQ(mmMaxQ);
		traderId tId = 3000 + i;
		if (mpi == 1)
			traderMap[tId] = std::make_shared<MarketMaker>(size, tId, size, mmDelta, mmRange, mmQuotes);
//			bucket.push_back(std::make_shared<MarketMaker>(size, tId, size, mmDelta, mmRange, mmQuotes));
		else
			traderMap[tId] = std::make_shared<MarketMaker5>(size, tId, size, mmDelta, mmRange, mmQuotes);
//			bucket.push_back(std::make_shared<MarketMaker5>(size, tId, size, mmDelta, mmRange, mmQuotes));
	}
}

std::pair<std::vector<double>, std::vector<double>> Runner::buildLambda()
{
//	std::valarray<double> qt0(runSteps);
//	qt0[0] = 0.5;
	double denom = 0.0, qt9 = 0.5, qt1 = 0.5;
	double qt10, qt2, x, lambdaDenom, lambda;
	std::vector<double> qTake;
	std::vector<double> lambdaT;
//	double x;
	std::uniform_real_distribution<> distUreal(0, 1);
	auto noise = std::bind(distUreal, engine);
	for (auto i = 1; i != runSteps; ++i)
	{
		x = noise();
		qt10 = (x > qt9) ? qt9 + whiteNoise : qt9 - whiteNoise;
		qt9 = qt10;
//		denom += std::pow(qt10 - 0.5, 2);
		denom += (qt10 - 0.5) * (qt10 - 0.5);
//		qt0[i] = (x > qt0[i - 1]) ? qt0[i - 1] + whiteNoise : qt0[i - 1] - whiteNoise;
//		denom += std::pow(qt0[i] - 0.5, 2);
	}
	lambdaDenom = std::sqrt(denom / runSteps);
	
	qTake.emplace_back(qt1);
	lambdaT.emplace_back(-lambda0);
	for (auto i = 1; i != runSteps; ++i)
	{
		x = noise();
		qt2 = (x > qt1) ? qt1 + whiteNoise : qt1 - whiteNoise;
		qt1 = qt2;
		qTake.emplace_back(qt2);
		lambda = -lambda0 * (1 + (abs(qt2 - 0.5) / lambdaDenom) * cLambda);
		lambdaT.emplace_back(lambda);
	}
	return std::make_pair(qTake, lambdaT);
}

void Runner::qTakeToCsv(std::string filename)
{
	std::ofstream csvfile;
	csvfile.open(filename);
	csvfile << "QTake,LambdaT\n";
	for (auto i = 0; i != runSteps ; ++i)
		csvfile << i << "," << QL.first[i] << "," << QL.second[i] << "\n";
	csvfile.close();
}