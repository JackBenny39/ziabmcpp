// Runner.cpp
// Runner class

#include "stdafx.h"

#include "Runner.h"


Runner::Runner(Prc mpi, Step prime1, Step runSteps, Step writeInterval, 
	bool provider, unsigned numProviders, Qty providerMaxQ, double pAlpha, double pDelta, double qProvide,
	bool taker, unsigned numTakers, Qty takerMaxQ, double tMu,
	bool informed, Step informedRun, Qty informedMaxQ, double iMu,
	bool jumper, double jAlpha,
	bool maker, unsigned numMMs, Qty mmMaxQ, unsigned mmQuotes, unsigned mmRange, double mmDelta,
	bool qTake, double lambda0, double whiteNoise, double cLambda) :
	mpi(mpi), prime1(prime1), runSteps(runSteps), writeInterval(writeInterval), 
	provider(provider), numProviders(numProviders), providerMaxQ(providerMaxQ), pAlpha(pAlpha), pDelta(pDelta), qProvide(qProvide),
	taker(taker), numTakers(numTakers), takerMaxQ(takerMaxQ), tMu(tMu),
	informed(informed), informedRun(informedRun), informedMaxQ(informedMaxQ), iMu(iMu),
	jumper(jumper), jAlpha(jAlpha),
	maker(maker), numMMs(numMMs), mmMaxQ(mmMaxQ), mmQuotes(mmQuotes), mmRange(mmRange), mmDelta(mmDelta),
	qTake(qTake), lambda0(lambda0), whiteNoise(whiteNoise), cLambda(cLambda)
{
	exchange = Orderbook();
}