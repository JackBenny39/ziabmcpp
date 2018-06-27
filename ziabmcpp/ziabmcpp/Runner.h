// Runner.h

#pragma once

#ifndef RUNNER_H
#define RUNNER_H

#include "stdafx.h"

#include <memory>
#include <random>

#include "Sharedstx.h"

#include "Orderbook.h"

#include "ZITrader.h"
#include "Taker.h"
#include "Informed.h"
#include "Provider.h"
#include "Provider5.h"
#include "MarketMaker.h"
#include "MarketMaker5.h"
#include "PennyJumper.h"


class Runner
{
public:
	Runner(Prc, Step, Step, Step, 
		bool, unsigned, Qty, double, double, double,
		bool, unsigned, Qty, double,
		bool, Step, Qty, double, Side,
		bool, double,
		bool, unsigned, Qty, unsigned, unsigned, double,
		bool, double, double, double, std::mt19937 &, unsigned);

	std::mt19937 engine;
	std::vector<int> defaultVec;
//	std::exponential_distribution<double> distExpP;
//	std::uniform_int_distribution<> distUint;
//	std::uniform_real_distribution<> distUreal;

	int setMaxQ(int);
	void buildProviders();
	void buildTakers();
	void buildInformed();
	void buildMarketMakers();

	std::vector<std::shared_ptr<ZITrader>> bucket;

	Prc mpi;
	Step prime1, runSteps, writeInterval, informedRun;
	bool provider, taker, informed, jumper, maker, qTake;
	unsigned numProviders, numTakers, numMMs, mmQuotes, mmRange, seed;
	Qty providerMaxQ, takerMaxQ, informedQ, mmMaxQ;
	double pAlpha, pDelta, qProvide, tMu, iMu, jAlpha, mmDelta;
	double lambda0, whiteNoise, cLambda;
	Side informedSide;
	Orderbook exchange;
	PennyJumper* j1;
};

#endif
