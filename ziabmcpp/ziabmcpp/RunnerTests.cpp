// RunnerTests.cpp
// RunnerTests class

#include "stdafx.h"

#include <chrono>
#include <iostream>

#include "RunnerTests.h"

using namespace std::chrono;


RunnerTests::RunnerTests() 
{
	mpi = 1;
	prime1 = 20; 
	runSteps = 100001;
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
	providerMaxQ = 1;
	takerMaxQ = 1;
	informedQ = 1;
	mmMaxQ = 1;
	pAlpha = 0.0375;
	pDelta = 0.025; 
	qProvide = 0.5; 
	tMu = 0.001;
	iMu = 0.01;
	jAlpha = 0.05;
	mmDelta = 0.025;
	qTake = true;
	lambda0 = 100.0;
	whiteNoise = 0.001;
	cLambda = 5.0;
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
	std::cout << "From providers map: \n";
	for (auto &x : market1.providers)
		std::cout << "Trader Type: " << x.second->traderType << "; Trader ID: " << x.second->tId << "; Arrival Interval: " << x.second->arrInt
			<< "; Max Q: " << x.second->orderSize << "\n";
	std::cout << "\nFrom allTraderIds integers: \n";
	for (auto &x : market1.allTraderIds)
		std::cout << "Trader ID: " << x << "\n";
	std::cout << "\nFrom providerIds integers: \n";
	for (auto &x : market1.providerIds)
		std::cout << "Trader ID: " << x << "\n";
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

	if (provider) { market1.buildProviders(); }
	if (taker) { market1.buildTakers(); }

	std::cout << "Taker Mu: " << market1.tMu << "\n";
	std::cout << "From takers map\n";
	for (auto &x : market1.takers)
		std::cout << "Trader Type: " << x.second->traderType << "; Trader ID: " << x.second->tId << "; Arrival Interval: " << x.second->arrInt
			<< "; Max Q: " << x.second->orderSize << "\n";
	std::cout << "From allTraders integers: \n";
	for (auto &x : market1.allTraderIds)
		std::cout << "Trader ID: " << x << "\n";
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

	std::cout << "From informedTrader unique_ptr: \n";
	std::cout << "Trader Type: " << market1.informed1->traderType << "; Trader ID: " << market1.informed1->tId << "; Arrival Interval: " 
		<< market1.informed1->arrInt << "; Max Q: " << market1.informed1->orderSize << "\n";
	std::cout << "From allTraders integers: \n";
	for (auto &x : market1.allTraderIds)
		std::cout << "Trader ID: " << x << "\n";
	std::cout << std::endl;
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

	if (taker) { market1.buildTakers(); }
	if (maker) { market1.buildMarketMakers(); }

	std::cout << "From makers map: \n";
	for (auto &x : market1.makers)
		std::cout << "Trader Type: " << x.second->traderType << "; Trader ID: " << x.second->tId << "; Arrival Interval: " << x.second->arrInt
			<< "; Order Size: " << x.second->orderSize << "; MM Delta: " << x.second->delta << "; MM Quote Range: " << x.second->quoteRange << "; MM Quotes: "
			<< x.second->numQuotes << "\n";
	std::cout << "\nFrom allTraderIds integers: \n";
	for (auto &x : market1.allTraderIds)
		std::cout << "Trader ID: " << x << "\n";
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

	if (jumper) { market1.buildPennyJumper(); }

	std::cout << "Trader Type: " << market1.jumper1->traderType << "; Trader ID: " << market1.jumper1->tId << "; Max Q: " 
		<< market1.jumper1->orderSize << "; PJ MPI: " << market1.jumper1->mpi << "\n";
	std::cout << std::endl;
}

void RunnerTests::testBuildLambda()
{
	Runner market1 = Runner(mpi, prime1, runSteps, writeInterval,
		provider, numProviders, providerMaxQ, pAlpha, pDelta, qProvide,
		taker, numTakers, takerMaxQ, tMu,
		informed, informedRun, informedQ, iMu, informedSide,
		jumper, jAlpha,
		maker, numMMs, mmMaxQ, mmQuotes, mmRange, mmDelta,
		qTake, lambda0, whiteNoise, cLambda, engine, seed);

	auto t0 = high_resolution_clock::now();
	std::pair<std::vector<double>, std::vector<double>> test = market1.buildLambda();
	auto t1 = high_resolution_clock::now();
	std::cout << duration_cast<milliseconds>(t1 - t0).count() << " ms\n";
	std::cout << "cLambda: " << market1.cLambda << "\n";
	std::cout << "QL position 0 = " << test.first[0] << " : " << test.second[0] << "\n";
	std::cout << "QL position 100 = " << test.first[100] << " : " << test.second[100] << "\n";
	std::cout << "QL position 1000 = " << test.first[1000] << " : " << test.second[1000] << "\n";
	std::cout << "QL position 10000 = " << test.first[10000] << " : " << test.second[10000] << "\n";
	std::cout << "QL position 99999 = " << test.first[99999] << " : " << test.second[99999] << "\n";
	std::cout << "QL Length: " << test.first.size() << " : " << test.second.size() << "\n";
	std::cout << std::endl;
}

void RunnerTests::testQTakeToCsv(std::string file1)
{
	Runner market1 = Runner(mpi, prime1, runSteps, writeInterval,
		provider, numProviders, providerMaxQ, pAlpha, pDelta, qProvide,
		taker, numTakers, takerMaxQ, tMu,
		informed, informedRun, informedQ, iMu, informedSide,
		jumper, jAlpha,
		maker, numMMs, mmMaxQ, mmQuotes, mmRange, mmDelta,
		qTake, lambda0, whiteNoise, cLambda, engine, seed);

	market1.QL = market1.buildLambda();
	market1.qTakeToCsv(file1);
}

void RunnerTests::testmmProfitsToCsv(std::string file1)
{
	Runner market1 = Runner(mpi, prime1, runSteps, writeInterval,
		provider, numProviders, providerMaxQ, pAlpha, pDelta, qProvide,
		taker, numTakers, takerMaxQ, tMu,
		informed, informedRun, informedQ, iMu, informedSide,
		jumper, jAlpha,
		maker, numMMs, mmMaxQ, mmQuotes, mmRange, mmDelta,
		qTake, lambda0, whiteNoise, cLambda, engine, seed);

	market1.buildMarketMakers();
	std::shared_ptr<MarketMaker> mm = market1.makers[3000];
	mm->cashFlowCollector.emplace_back(CFlow{ 3001, 27, 1000, 20 });
	mm->cashFlowCollector.emplace_back(CFlow{ 3001, 30, 2000, 40 });
	mm->cashFlowCollector.emplace_back(CFlow{ 3001, 33, 0, 0 });
	mm->cashFlowCollector.emplace_back(CFlow{ 3001, 35, -1000, -20 });
	mm->cashFlowCollector.emplace_back(CFlow{ 3001, 39, -2000, -40 });
	market1.mmProfitsToCsv(file1);
}

void RunnerTests::testSeedBook()
{
	Runner market1 = Runner(mpi, prime1, runSteps, writeInterval,
		provider, numProviders, providerMaxQ, pAlpha, pDelta, qProvide,
		taker, numTakers, takerMaxQ, tMu,
		informed, informedRun, informedQ, iMu, informedSide,
		jumper, jAlpha,
		maker, numMMs, mmMaxQ, mmQuotes, mmRange, mmDelta,
		qTake, lambda0, whiteNoise, cLambda, engine, seed);

	if (provider) { market1.buildProviders(); }
	market1.seedBook();

	std::cout << "Provider Lookup\n";
	std::cout << "Seed Provider ID: " << market1.providers[numProviders]->tId << "\n";
	std::cout << "Seed Provider Bid Order Price: " << market1.providers[numProviders]->localBook[1].price << "\n";
	std::cout << "Seed Provider Ask Order Price: " << market1.providers[numProviders]->localBook[2].price << "\n";
	std::cout << "Exchange History 0: " << market1.exchange.history[0].price << "\n";
	std::cout << "Exchange History 1: " << market1.exchange.history[1].price << "\n";
	std::cout << "Bids:\n";
	for (auto &x : market1.exchange.bids)
	{
		std::cout << "Price: " << x.first << ", Qty: " << x.second.qty << "\n";
		for (auto &y : x.second.quotes)
			std::cout << "Trader Id: " << y.id << ", Order Id: " << y.oid << ", Qty: " << y.qty << "\n";
	}
	std::cout << "Asks:\n";
	for (auto &x : market1.exchange.asks)
	{
		std::cout << "Price: " << x.first << ", Qty: " << x.second.qty << "\n";
		for (auto &y : x.second.quotes)
			std::cout << "Trader Id: " << y.id << ", Order Id: " << y.oid << ", Qty: " << y.qty << "\n";
	}
	std::cout << std::endl;
}

void RunnerTests::testMakeSetup()
{
	Runner market1 = Runner(mpi, prime1, runSteps, writeInterval,
		provider, numProviders, providerMaxQ, pAlpha, pDelta, qProvide,
		taker, numTakers, takerMaxQ, tMu,
		informed, informedRun, informedQ, iMu, informedSide,
		jumper, jAlpha,
		maker, numMMs, mmMaxQ, mmQuotes, mmRange, mmDelta,
		qTake, lambda0, whiteNoise, cLambda, engine, seed);

	if (provider) { market1.buildProviders(); }
	market1.seedBook();
	for (auto &x : market1.providers)
		std::cout << "Trader Type: " << x.second->traderType << "; Trader ID: " << x.second->tId << "; Arrival Interval: " 
			<< x.second->arrInt << "; Max Q: " << x.second->orderSize << "\n";
	market1.makeSetup();
	// Tests include trader.processSignal tests and orderbook.process & addBook2 tests
	// Interrogate the trader's localBook if arrival interval is less than prime1
	std::cout << "\n\n Check Provider's localBook if arrival interval less than prime1\n";
	auto t0 = high_resolution_clock::now();
	for (auto &x : market1.providers)
	{
		if (x.second->arrInt < prime1)
		{
			std::cout << "\n***Trader ID: " << x.second->tId << "; Arrival Interval: " << x.second->arrInt << "\n";
			for (auto &b : x.second->localBook)
			{
				std::cout << "TraderId: " << b.second.id
					<< " Order Id: " << b.second.oid
					<< " Order Type: " << b.second.otype
					<< " Order Price: " << b.second.price
					<< " Order Qty: " << b.second.qty
					<< " Order Side: " << (b.second.side == Side::BUY ? 'B' : 'S')
					<< " Order Step: " << b.second.step << "\n";
			}
		}
	}
	auto t1 = high_resolution_clock::now();
	std::cout << "Direct map access: " << duration_cast<microseconds>(t1 - t0).count() << " us\n";
/*
	auto t2 = high_resolution_clock::now();
	for (auto &x : market1.providers)
	{
		std::shared_ptr<Provider> pptr = x.second;
		if (pptr->arrInt < prime1)
		{
			std::cout << "\n***Trader ID: " << pptr->tId << "; Arrival Interval: " << pptr->arrInt << "\n";
			for (auto &b : pptr->localBook)
			{
				std::cout << "TraderId: " << b.second.id
					<< " Order Id: " << b.second.oid
					<< " Order Type: " << b.second.otype
					<< " Order Price: " << b.second.price
					<< " Order Qty: " << b.second.qty
					<< " Order Side: " << (b.second.side == Side::BUY ? 'B' : 'S')
					<< " Order Step: " << b.second.step << "\n";
			}
		}
	}
	auto t3 = high_resolution_clock::now();
	std::cout << "Pointer access: " << duration_cast<microseconds>(t3 - t2).count() << " us\n";
*/
	// Check the exchange top of book
	std::cout << "\n\n Check exchange top of book\n";
	for (auto &x : market1.exchange.tob)
	{
		std::cout << "Step: " << x.step << "; Best Bid: " << x.bestbid << "; Best Bid Size: " << x.bestbidsz 
			<< "; Best Ask: " << x.bestask << "; Best Ask Size: " << x.bestasksz << "\n";
	}
	// Check the bid book
//	std::cout << "\n\n Check exchange bid book\n";
//	std::cout << "Bids:\n";
//	for (auto &x : market1.exchange.bids)
//	{
//		std::cout << "Price: " << x.first << ", Qty: " << x.second.qty << "\n";
//		for (auto &y : x.second.quotes)
//			std::cout << "Trader Id: " << y.id << ", Order Id: " << y.oid << ", Qty: " << y.qty << "\n";
//	}
	// Check the ask book
//	std::cout << "\n\n Check exchange ask book\n";
//	std::cout << "Asks:\n";
//	for (auto &x : market1.exchange.asks)
//	{
//		std::cout << "Price: " << x.first << ", Qty: " << x.second.qty << "\n";
//		for (auto &y : x.second.quotes)
//			std::cout << "Trader Id: " << y.id << ", Order Id: " << y.oid << ", Qty: " << y.qty << "\n";
//	}
	std::cout << std::endl;
}
/*
void RunnerTests::testRun()
{
	auto t0 = high_resolution_clock::now();
	Runner market1 = Runner(mpi, prime1, runSteps, writeInterval,
		provider, numProviders, providerMaxQ, pAlpha, pDelta, qProvide,
		taker, numTakers, takerMaxQ, tMu,
		informed, informedRun, informedQ, iMu, informedSide,
		jumper, jAlpha,
		maker, numMMs, mmMaxQ, mmQuotes, mmRange, mmDelta,
		qTake, lambda0, whiteNoise, cLambda, engine, seed);

	market1.run();
	auto t1 = high_resolution_clock::now();
	std::cout << duration_cast<seconds>(t1 - t0).count() << " s\n";
}
*/