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
	void testBuildTakers();
//	void testBuildInformed();
//	void testBuildPennyJumper();
//	void testBuildMarketMakers();
//	void testBuildLambda();
//	void testQTakeToCsv(std::string);
//	void testmmProfitsToCsv(std::string);
//	void testSeedBook();
//	void testMakeSetup();
//	void testDoCancels();
//	void testDoTrades();
//	void testRun();

	Prc mpi;
	Step prime1, runSteps, writeInterval, informedRun;
	bool provider, taker, informed, jumper, maker, qTake;
	unsigned numProviders, numTakers, numMMs, mmQuotes, mmRange, seed;
	Qty providerMaxQ, takerMaxQ, informedQ, mmMaxQ;
	double pAlpha, pDelta, qProvide, tMu, iMu, jAlpha, mmDelta;
	double lambda0, whiteNoise, cLambda;
	Side informedSide;
	std::mt19937 engine;
	std::unique_ptr<PennyJumper> j1;
};

#endif