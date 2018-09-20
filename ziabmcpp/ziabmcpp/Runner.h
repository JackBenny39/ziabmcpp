// Runner.h

#pragma once

#ifndef RUNNER_H
#define RUNNER_H

#include "stdafx.h"

#include <cmath>
#include <functional>
#include <memory>
#include <random>
#include <valarray>

#include "Sharedstx.h"

#include "Orderbook.h"

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

	std::vector<traderId> allTraders;
	std::vector<std::shared_ptr<Provider>> providers;
	std::vector<std::shared_ptr<Provider5>> providers5;
	std::vector<std::shared_ptr<Taker>> takers;
	std::unique_ptr<Informed> informedTrader;
	std::vector<std::shared_ptr<MarketMaker>> makers;
	std::vector<std::shared_ptr<MarketMaker5>> makers5;
	std::unique_ptr<PennyJumper> jumper1;
	std::pair<std::vector<double>, std::vector<double>> QL;

	int setMaxQ(int);
	void buildProviders();
	void buildTakers();
	void buildInformed();
	void buildMarketMakers();
	void buildPennyJumper();
	std::pair<std::vector<double>, std::vector<double>> buildLambda();
	void qTakeToCsv(std::string &);
	void mmProfitsToCsv(std::string &);
	void seedBook();
//	void makeSetup();
//	void doCancels(std::shared_ptr<ZITrader> &);
//	void doTrades();
//	void runMCS();
//	void runMCSPJ();
	void run();

	Prc mpi;
	Step prime1, runSteps, writeInterval, informedRun;
	bool provider, taker, informed, jumper, maker, qTake;
	unsigned numProviders, numTakers, numMMs, mmQuotes, mmRange, seed;
	Qty providerMaxQ, takerMaxQ, informedQ, mmMaxQ;
	double pAlpha, pDelta, qProvide, tMu, iMu, jAlpha, mmDelta;
	double lambda0, whiteNoise, cLambda, lambdaDenom;
	Side informedSide;
	Orderbook exchange;
	
};

#endif
