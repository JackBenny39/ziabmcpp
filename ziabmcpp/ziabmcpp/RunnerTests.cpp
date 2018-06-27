// RunnerTests.cpp
// RunnerTests class

#include "stdafx.h"

#include <iostream>

#include "RunnerTests.h"


RunnerTests::RunnerTests() 
{
	mpi = 1;
	prime1 = 20; 
	runSteps = 100000;
	writeInterval = 5000; 
	informedRun = 3;
	provider = true;
	taker = true;
	informed = true;
	jumper = true;
	maker = true;
	numProviders = 38;
	numTakers = 50;
	numMMs = 1;
	mmQuotes = 12;
	mmRange = 60;
	providerMaxQ = 50;
	takerMaxQ = 1;
	informedQ = 1;
	mmMaxQ = 1;
	pAlpha = 0.0375;
	pDelta = 0.025; 
	qProvide = 0.05; 
	tMu = 0.001;
	iMu = 0.001;
	jAlpha = 0.05;
	mmDelta = 0.025;
	qTake = true;
	lambda0 = 100.0;
	whiteNoise = 0.001;
	cLambda = 1.0;
	std::random_device random_device;
	std::mt19937 engine{ random_device() };
	informedSide = Side::BUY;
	seed = 39;
}

void RunnerTests::testConstructor()
{
	Runner market1 = Runner(mpi, prime1, runSteps, writeInterval,
		provider, numProviders, providerMaxQ, pAlpha, pDelta, qProvide,
		taker, numTakers, takerMaxQ, tMu,
		informed, informedRun, informedQ, iMu, informedSide,
		jumper, jAlpha,
		maker, numMMs, mmMaxQ, mmQuotes, mmRange, mmDelta,
		qTake, lambda0, whiteNoise, cLambda, engine, seed);

	std::cout << "MPI: " << market1.mpi << "\n";
	std::cout << "Prime1: " << market1.prime1 << "\n";
	std::cout << "Run Steps: " << market1.runSteps << "\n";
	std::cout << "Write Interval: " << market1.writeInterval << "\n";
	std::cout << "Provider: " << market1.provider << "\n";
	std::cout << "Number of Providers: " << market1.numProviders << "\n";
	std::cout << "Provider Max Quantity: " << market1.providerMaxQ << "\n";
	std::cout << "Provider Alpha: " << market1.pAlpha << "\n";
	std::cout << "Provider Delta: " << market1.pDelta << "\n";
	std::cout << "Provider Arrival: " << market1.qProvide << "\n";
	std::cout << "Taker: " << market1.taker << "\n";
	std::cout << "Number of Takers: " << market1.numTakers << "\n";
	std::cout << "Taker Max Quantity: " << market1.takerMaxQ << "\n";
	std::cout << "Taker Mu: " << market1.tMu << "\n";
	std::cout << "Informed: " << market1.informed << "\n";
	std::cout << "Informed Run Length: " << market1.informedRun << "\n";
	std::cout << "Informed Max Quantity: " << market1.informedQ << "\n";
	std::cout << "Informed Mu: " << market1.iMu << "\n";
	std::cout << "Jumper: " << market1.jumper << "\n";
	std::cout << "Jumper Alpha: " << market1.jAlpha << "\n";
	std::cout << "Maker: " << market1.maker << "\n";
	std::cout << "Number of MarketMakers: " << market1.numMMs << "\n";
	std::cout << "MarketMaker Max Quantity: " << market1.mmMaxQ << "\n";
	std::cout << "MarketMaker Number of Quotes: " << market1.mmQuotes << "\n";
	std::cout << "MarketMaker Quote Range: " << market1.mmRange << "\n";
	std::cout << "MarketMaker Delta: " << market1.mmDelta << "\n";
	std::cout << "QTake: " << market1.qTake << "\n";
	std::cout << "Lambda 0: " << market1.lambda0 << "\n";
	std::cout << "White Noise: " << market1.whiteNoise << "\n";
	std::cout << "C Lambda: " << market1.cLambda << "\n";

	std::cout << std::endl;
}

void RunnerTests::testBuildProvider()
{
	Runner market1 = Runner(mpi, prime1, runSteps, writeInterval,
		provider, numProviders, providerMaxQ, pAlpha, pDelta, qProvide,
		taker, numTakers, takerMaxQ, tMu,
		informed, informedRun, informedQ, iMu, informedSide,
		jumper, jAlpha,
		maker, numMMs, mmMaxQ, mmQuotes, mmRange, mmDelta,
		qTake, lambda0, whiteNoise, cLambda, engine, seed);

	if (provider) { market1.buildProviders(); }

	std::cout << "Provider Alpha: " << market1.pAlpha << "\n";
	for (auto &x : market1.bucket)
		std::cout << "Trader Type: " << x->traderType << "; Trader ID: " << x->tId << "; Arrival Interval: " << x->arrInt << "; Max Q: " << x->orderSize << "\n";
	std::cout << std::endl;
}

void RunnerTests::testBuildTakers()
{
	Runner market1 = Runner(mpi, prime1, runSteps, writeInterval,
		provider, numProviders, providerMaxQ, pAlpha, pDelta, qProvide,
		taker, numTakers, takerMaxQ, tMu,
		informed, informedRun, informedQ, iMu, informedSide,
		jumper, jAlpha,
		maker, numMMs, mmMaxQ, mmQuotes, mmRange, mmDelta,
		qTake, lambda0, whiteNoise, cLambda, engine, seed);

	if (taker) { market1.buildTakers(); }

	std::cout << "Taker Mu: " << market1.tMu << "\n";
	for (auto &x : market1.bucket)
		std::cout << "Trader Type: " << x->traderType << "; Trader ID: " << x->tId << "; Arrival Interval: " << x->arrInt << "; Max Q: " << x->orderSize << "\n";
	std::cout << std::endl;
}

void RunnerTests::testBuildInformed()
{
	Runner market1 = Runner(mpi, prime1, runSteps, writeInterval,
		provider, numProviders, providerMaxQ, pAlpha, pDelta, qProvide,
		taker, numTakers, takerMaxQ, tMu,
		informed, informedRun, informedQ, iMu, informedSide,
		jumper, jAlpha,
		maker, numMMs, mmMaxQ, mmQuotes, mmRange, mmDelta,
		qTake, lambda0, whiteNoise, cLambda, engine, seed);

	if (taker) { market1.buildTakers(); }
	if (informed) { market1.buildInformed(); }

	std::cout << "Trader Type: " << market1.bucket[numTakers]->traderType << "; Trader ID: " << market1.bucket[numTakers]->tId << "; Max Q: " 
		<< market1.bucket[numTakers]->orderSize << "\n";
	for (auto &x : market1.bucket[numTakers]->steps)
		std::cout << "Arrival Interval: " << x << "\n";
	std::cout << std::endl;
}

void RunnerTests::testBuildPennyJumper()
{
	Runner market1 = Runner(mpi, prime1, runSteps, writeInterval,
		provider, numProviders, providerMaxQ, pAlpha, pDelta, qProvide,
		taker, numTakers, takerMaxQ, tMu,
		informed, informedRun, informedQ, iMu, informedSide,
		jumper, jAlpha,
		maker, numMMs, mmMaxQ, mmQuotes, mmRange, mmDelta,
		qTake, lambda0, whiteNoise, cLambda, engine, seed);

	std::cout << "Trader Type: " << market1.j1->traderType << "; Trader ID: " << market1.j1->tId << "; Max Q: " << market1.j1->orderSize 
		<< "; PJ MPI: " << market1.j1->mpi << "\n";
}

void RunnerTests::testBuildMarketMakers()
{
	Runner market1 = Runner(mpi, prime1, runSteps, writeInterval,
		provider, numProviders, providerMaxQ, pAlpha, pDelta, qProvide,
		taker, numTakers, takerMaxQ, tMu,
		informed, informedRun, informedQ, iMu, informedSide,
		jumper, jAlpha,
		maker, numMMs, mmMaxQ, mmQuotes, mmRange, mmDelta,
		qTake, lambda0, whiteNoise, cLambda, engine, seed);

	if (maker) { market1.buildMarketMakers(); }

	for (auto &x : market1.bucket)
		std::cout << "Trader Type: " << x->traderType << "; Trader ID: " << x->tId << "; Arrival Interval: " << x->arrInt << "; Order Size: " << x->orderSize 
			<< "; MM Delta: " << x->delta << ": MM Quote Range" << x->quoteRange << ": MM Quotes: " << x->numQuotes << "\n";
	std::cout << std::endl;
}