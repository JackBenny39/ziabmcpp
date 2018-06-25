// RunnerTests.h

#pragma once

#ifndef RUNNERTESTS_H
#define RUNNERTESTS_H

#include "stdafx.h"

#include "Sharedstx.h"

#include "Runner.h"

class RunnerTests
{
public:
	RunnerTests();

	void testConstructor();
	void testBuildProvider();

	Prc mpi;
	Step prime1, runSteps, writeInterval, informedRun;
	bool provider, taker, informed, jumper, maker, qTake;
	unsigned numProviders, numTakers, numMMs, mmQuotes, mmRange, seed;
	Qty providerMaxQ, takerMaxQ, informedMaxQ, mmMaxQ;
	double pAlpha, pDelta, qProvide, tMu, iMu, jAlpha, mmDelta;
	double lambda0, whiteNoise, cLambda;
	std::mt19937 engine;
};

#endif