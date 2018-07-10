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
	traderId tId;
	auto size = setMaxQ(providerMaxQ);
	if (mpi == 1)
	{
		std::shared_ptr<Provider> p;
		for (auto i = 0; i != numProviders; ++i)
		{
			tId = 1000 + i;
			p = std::make_shared<Provider>(static_cast<int>(floor(distExpP(engine) + 1)) * size, tId, size, pDelta, mpi);
//			traderMap[tId] = p;
			providerMap[tId] = p;
//			allTraders.push_back(tId);
//			providers.push_back(tId);
			allTraders.push_back(p);
			providers.push_back(p);
		}
	}
	else
	{
		std::shared_ptr<Provider5> p;
		for (auto i = 0; i != numProviders; ++i)
		{
			tId = 1000 + i;
			p = std::make_shared<Provider5>(static_cast<int>(floor(distExpP(engine) + 1)) * size, tId, size, pDelta, mpi);
//			traderMap[tId] = p;
			providerMap[tId] = p;
//			allTraders.push_back(tId);
//			providers.push_back(tId);
			allTraders.push_back(p);
			providers.push_back(p);
		}
	}
}

void Runner::buildTakers()
{
	std::exponential_distribution<double> distExpT(tMu);
//	traderId tId;
	for (auto i = 0; i != numTakers; ++i)
	{
		auto size = setMaxQ(takerMaxQ);
//		tId = 2000 + i;
//		traderMap[tId] = std::make_shared<Taker>(static_cast<int>(floor(distExpT(engine) + 1)) * size, tId, size, mpi);
//		allTraders.push_back(tId);
		allTraders.emplace_back(std::make_shared<Taker>(static_cast<int>(floor(distExpT(engine) + 1)) * size, 2000 + i, size, mpi));
	}
}

void Runner::buildInformed()
{
	int takerTrades = 0;
	int informedTrades;
	if (taker)
	{
//		for (std::pair<traderId, std::shared_ptr<ZITrader>> x : traderMap)
		for (auto &x : allTraders)
		{
//			if (x.second->traderType == 'T')
			if (x->traderType == 'T')
//				takerTrades += x.second->orderSize * runSteps / x.second->arrInt;
				takerTrades += x->orderSize * runSteps / x->arrInt;
		}
		informedTrades = static_cast<int>(floor(takerTrades * iMu));
	}
	else
		informedTrades = static_cast<int>(1 / iMu);

	std::uniform_int_distribution<int> distUintI(prime1, runSteps);
//	traderMap[5000] = std::make_shared<Informed>(5000, informedQ, informedSide, informedRun, informedTrades, engine, distUintI);
//	allTraders.push_back(5000);
	allTraders.emplace_back(std::make_shared<Informed>(5000, informedQ, informedSide, informedRun, informedTrades, engine, distUintI));
}

void Runner::buildMarketMakers()
{
	auto size = setMaxQ(mmMaxQ);
	traderId tId;
	if (mpi == 1)
	{
		std::shared_ptr<MarketMaker> m;
		for (auto i = 0; i != numMMs; ++i)
		{
			tId = 3000 + i;
			m = std::make_shared<MarketMaker>(size, tId, size, mmDelta, mmRange, mmQuotes);
//			traderMap[tId] = m;
			providerMap[tId] = m;
//			allTraders.push_back(tId);
			allTraders.push_back(m);
		}
	}
	else
	{
		std::shared_ptr<MarketMaker5> m;
		for (auto i = 0; i != numMMs; ++i)
		{
			tId = 3000 + i;
			m = std::make_shared<MarketMaker5>(size, tId, size, mmDelta, mmRange, mmQuotes);
//			traderMap[tId] = m;
			providerMap[tId] = m;
//			allTraders.push_back(tId);
			allTraders.push_back(m);
		}
	}
}

void Runner::buildPennyJumper()
{
	j1 = std::make_shared<PennyJumper>(1, 4000, 1, mpi);
	providerMap[4000] = j1;
}

std::pair<std::vector<double>, std::vector<double>> Runner::buildLambda()
{
	double denom = 0.0, qt9 = 0.5, qt1 = 0.5;
	double qt10, qt2, x, lambdaDenom, lambda;
	std::vector<double> qTake;
	std::vector<double> lambdaT;
	std::uniform_real_distribution<> distUreal(0, 1);
	auto noise = std::bind(distUreal, engine);
	for (auto i = 1; i != runSteps; ++i)
	{
		x = noise();
		qt10 = (x > qt9) ? qt9 + whiteNoise : qt9 - whiteNoise;
		qt9 = qt10;
		denom += (qt10 - 0.5) * (qt10 - 0.5);
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

void Runner::seedBook()
{
	std::exponential_distribution<double> distExpP(pAlpha);
	std::shared_ptr<Provider> p = std::make_shared<Provider>(static_cast<int>(floor(distExpP(engine) + 1)), 9999, 1, pDelta, mpi);
	providerMap[9999] = p;
	std::uniform_int_distribution<int> distUintBid(997995, 999996);
	std::uniform_int_distribution<int> distUintAsk(1000005, 1002001);
	Order b = p->makeAddQuote(0, Side::BUY, 5 * (distUintBid(engine) / 5));
	Order a = p->makeAddQuote(0, Side::SELL, 5 * ((distUintAsk(engine) / 5) + 1));
	p->localBook[b.oid] = b;
	p->localBook[a.oid] = a;
	exchange.addHistory(b);
	exchange.addHistory(a);
	exchange.addBook2(b.id, b.oid, b.side, b.price, b.qty, b.step);
	exchange.addBook2(a.id, a.oid, a.side, a.price, a.qty, a.step);
}

void Runner::makeSetup()
{
	std::uniform_real_distribution<> distUreal(0, 1);
	for (auto i = 1; i != prime1; ++i)
	{
		shuffle(providers.begin(), providers.end(), engine);
		for (auto &x : providers)
		{
//			if ((i % x->arrInt) == 0)
			if (!(i % x->arrInt))
			{
				exchange.bookTop2(i);
				x->processSignal(exchange.tob.back(), i, qProvide, -lambda0, engine, distUreal);
				exchange.process(x->quoteCollector.back());
			}

		}
	}
}

void Runner::qTakeToCsv(std::string &filename)
{
	std::ofstream csvfile;
	csvfile.open(filename);
	csvfile << "QTake,LambdaT\n";
	for (auto i = 0; i != runSteps; ++i)
		csvfile << i << "," << QL.first[i] << "," << QL.second[i] << "\n";
	csvfile.close();
}