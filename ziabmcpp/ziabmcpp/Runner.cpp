// Runner.cpp
// Runner class

#include "stdafx.h"

#include <iostream>

#include "Runner.h"


Runner::Runner(Prc mpi, Step prime1, Step runSteps, Step writeInterval,
	bool provider, unsigned numProviders, Qty providerMaxQ, double pAlpha, double pDelta, double qProvide,
	bool taker, unsigned numTakers, Qty takerMaxQ, double tMu,
	bool informed, Step informedRun, Qty informedMaxQ, double iMu,
	bool jumper, double jAlpha,
	bool maker, unsigned numMMs, Qty mmMaxQ, unsigned mmQuotes, unsigned mmRange, double mmDelta,
	bool qTake, double lambda0, double whiteNoise, double cLambda, std::mt19937 &eng, unsigned seed) :
	mpi(mpi), prime1(prime1), runSteps(runSteps), writeInterval(writeInterval),
	provider(provider), numProviders(numProviders), providerMaxQ(providerMaxQ), pAlpha(pAlpha), pDelta(pDelta), qProvide(qProvide),
	taker(taker), numTakers(numTakers), takerMaxQ(takerMaxQ), tMu(tMu),
	informed(informed), informedRun(informedRun), informedMaxQ(informedMaxQ), iMu(iMu),
	jumper(jumper), jAlpha(jAlpha),
	maker(maker), numMMs(numMMs), mmMaxQ(mmMaxQ), mmQuotes(mmQuotes), mmRange(mmRange), mmDelta(mmDelta),
	qTake(qTake), lambda0(lambda0), whiteNoise(whiteNoise), cLambda(cLambda), engine(eng), seed(seed)
{
	defaultVec = { 1, 5, 10, 25, 50 };
	std::uniform_real_distribution<> distUreal(0, 1); // move when needed!
	engine.seed(seed);

	exchange = Orderbook();
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
		if (mpi == 1)
			bucket.push_back(std::make_shared<Provider>(static_cast<int>(floor(distExpP(engine) + 1)) * size, (3000 + i), size, pDelta, mpi));
		else
			bucket.push_back(std::make_shared<Provider5>(static_cast<int>(floor(distExpP(engine) + 1)) * size, (3000 + i), size, pDelta, mpi));
	}
}
