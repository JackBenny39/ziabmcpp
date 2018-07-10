// ziabmcpp.cpp : Defines the entry point for the console application.
//

//#define _CRTDBG_MAP_ALLOC
//#include <stdlib.h>
//#include <crtdbg.h>

#include "stdafx.h"

#include <iostream>     // std::cout, std::endl
#include <list>			// std::list
#include <map>			// std::map
#include <random>		// std::random_device, std::mt19937, std::uniform_real_distribution, std::uniform_int_distribution
#include <string>		// std::string
#include <tuple>        // std::tuple, std::get
#include <vector>		// std::vector
#include <fstream>
#include <memory>
#include <unordered_set>
#include <set>
#include <algorithm>

#include "Sharedstx.h"

#include "TraderTests.h"
#include "OrderbookTests.h"
#include "BucketTests2.h"
#include "BucketTests.h"
#include "RunnerTests.h"
/*
#include "ZITrader.h"
#include "Taker.h"
#include "Informed.h"
#include "Provider.h"
#include "Provider5.h"
#include "MarketMaker.h"
#include "MarketMaker5.h"
#include "PennyJumper.h"
#include "Orderbook.h"
*/

using cSide = char;

//std::random_device random_device;
//std::mt19937 engine{ random_device() };
//std::vector<int> defaultVec = { 1, 5, 10, 25, 50 };
//std::uniform_real_distribution<> distUreal(0, 1);
//std::exponential_distribution<double> distExp(1.0);
//std::uniform_int_distribution<> distA(1, 100000);

/*
double buySellP()
{
	return distUreal(engine);
}

void simpleTest(std::mt19937 &engine, std::uniform_real_distribution<> &dist)
{
	for (int i = 1; i != 21; ++i)
		std::cout << dist(engine) << "\n";
	std::cout << std::endl;
}

void testExp()
{
	std::exponential_distribution<double> distribution(1.0);
	std::ofstream expfile;
	expfile.open("C:\\Users\\user\\Documents\\Agent-Based Models\\csv files\\exp2.csv");

	for (int i = 1; i != 1000; i++)
	{
		double exp = distribution(engine);
		expfile << exp << "\n";
	}
	expfile.close();
		
}

void testExp2()
{
	std::exponential_distribution<double> distribution(1.0);
	std::ofstream expfile;

	for (int i = 1; i != 1000; i++)
	{
		double exp = distribution(engine);
		std::cout << i << " : " << exp << "\n";
	}
	std::cout << std::endl;

}


void testFromUnifrom(std::mt19937 &engine, std::uniform_real_distribution<> &dist)
{
	std::ofstream expfile;
	expfile.open("C:\\Users\\user\\Documents\\Agent-Based Models\\csv files\\uni1.csv");

	for (int i = 1; i != 1000; i++)
	{
		double uni = log(dist(engine));
		expfile << uni << "\n";
	}
	expfile.close();
}

void testInformedSteps()
{
	std::unordered_set<unsigned> steps;
	unsigned maxQ, runL, numT, numChoices, count;
	maxQ = 1;
	runL = 5;
	numT = 100;
	Step j;

	numChoices = (numT / (runL*maxQ)) + 1;
	std::cout << "Number of Choices: " << numChoices << "\n";

	std::uniform_int_distribution<Prc> distA(1, 100000);
	for (int i = 1; i != numChoices; ++i)
	{
		j = distA(engine);
		count = 0;
		while (count < runL)
		{
			while (steps.count(j) > 0)
				j++;
			steps.insert(j);
			count++;
		}
	}
	int counter = 0;
	std::set<int> srtd1(steps.begin(), steps.end());
	for (auto &x : srtd1)
		std::cout << "Choice " << ++counter << ": " << x << "\n";

	std::cout << std::endl;
}

void testMM5PS()
{
	Prc maxBid = 90;
	Prc minAsk = 100;
	Prc quoteRange = 60;
	int numQuotes = 12;
	std::vector<Prc> collectorA;
	std::vector<Prc> collectorB;
	std::uniform_int_distribution<Prc> distA(minAsk, minAsk + quoteRange - 1);
	std::uniform_int_distribution<Prc> distB(maxBid - quoteRange + 1, maxBid);
	for (int i = 1; i < numQuotes; i++)
		collectorA.push_back(static_cast<Prc>(5 * nearbyint(distA(engine) / 5.0)));
	for (auto &x : collectorA)
		std::cout << "From Collector Ask: " << x << "\n";
	for (int i = 1; i < numQuotes; i++)
		collectorB.push_back(static_cast<Prc>(5 * nearbyint(distB(engine) / 5.0)));
	for (auto &x : collectorB)
		std::cout << "From Collector Bid: " << x << "\n";
	std::cout << std::endl;
}
*/
/*
void testBucket()
{
	cSide cSide1;

	ZITrader z1(7, 1, setMaxQ(50), 1);
	Taker t1(11, 1001, setMaxQ(50), 1);
	Informed i1(2001, setMaxQ(50), Side::BUY, 1, 100, engine, distA);
	Provider p1(17, 3001, setMaxQ(50), 0.85, 1);
	Provider5 p5(22, 3005, setMaxQ(50), 0.05, 5);
	MarketMaker m1(1, 7001, setMaxQ(50), 0.05, 60, 12);
	MarketMaker5 m5(1, 7005, setMaxQ(50), 0.05, 60, 12);
	PennyJumper j1(1, 4001, setMaxQ(50), 1);

	std::vector<std::shared_ptr<ZITrader>> bucket;

	bucket.push_back(std::make_shared<ZITrader>(7, 1, setMaxQ(50), 1));
	bucket.push_back(std::make_shared<Taker>(11, 1001, setMaxQ(50), 1));
	bucket.push_back(std::make_shared<Informed>(2001, 1, Side::SELL, 1, 100, engine, distA));
	bucket.push_back(std::make_shared<Provider>(17, 3001, setMaxQ(50), 0.85, 1));
	bucket.push_back(std::make_shared<Provider5>(22, 3005, setMaxQ(50), 0.05, 5));
	bucket.push_back(std::make_shared<MarketMaker>(1, 7001, setMaxQ(50), 0.05, 60, 12));
	bucket.push_back(std::make_shared<MarketMaker5>(1, 7005, setMaxQ(50), 0.05, 60, 12));
	bucket.push_back(std::make_shared<PennyJumper>(1, 4001, setMaxQ(50), 1));

	std::cout << "Trader Type: " << bucket[0]->traderType << "; Max Quantity: " << bucket[0]->orderSize << "; Trader ID: " << bucket[0]->tId << "; MPI: "
		<< bucket[0]->mpi << "\n";
	std::cout << "Trader Type: " << bucket[1]->traderType << "; Max Quantity: " << bucket[1]->orderSize << "; Trader ID: " << bucket[1]->tId << "; MPI: "
		<< bucket[1]->mpi << "\n";
	cSide1 = bucket[2]->side == Side::BUY ? 'B' : 'S';
	std::cout << "Trader Type: " << bucket[2]->traderType << "; Max Quantity: " << bucket[2]->orderSize << "; Trader ID: " << bucket[2]->tId << "; Price:" 
		<< bucket[2]->price << "; Side:" << cSide1 << "\n";
	std::cout << "Trader Type: " << bucket[3]->traderType << "; Max Quantity: " << bucket[3]->orderSize << "; Trader ID: " << bucket[3]->tId << "; MPI: "
		<< bucket[3]->mpi << "; Delta: " << bucket[3]->delta << "\n";
	std::cout << "Trader Type: " << bucket[4]->traderType << "; Max Quantity: " << bucket[4]->orderSize << "; Trader ID: " << bucket[4]->tId << "; MPI: "
		<< bucket[4]->mpi << "; Delta: " << bucket[4]->delta << "\n";
	std::cout << "Trader Type: " << bucket[5]->traderType << "; Max Quantity: " << bucket[5]->orderSize << "; Trader ID: " << bucket[5]->tId << "; NumQuotes: "
		<< bucket[5]->numQuotes << "; Quote Range: " << bucket[5]->quoteRange << "; Position: " << bucket[5]->position << "; Cash Flow: " 
		<< bucket[5]->cashFlow << "\n";
	std::cout << "Trader Type: " << bucket[6]->traderType << "; Max Quantity: " << bucket[6]->orderSize << "; Trader ID: " << bucket[6]->tId << "; NumQuotes: "
		<< bucket[6]->numQuotes << "; Quote Range: " << bucket[6]->quoteRange << "; Position: " << bucket[6]->position << "; Cash Flow: "
		<< bucket[6]->cashFlow << "\n";
	std::cout << "Trader Type: " << bucket[7]->traderType << "; Max Quantity: " << bucket[7]->orderSize << "; Trader ID: " << bucket[7]->tId << "; MPI: "
		<< bucket[7]->mpi << "\n";

	std::cout << std::endl;
}
*/


int main()
{
//	engine.seed(39);

//	TraderTests tTests(defaultVec, distA, engine);
//	tTests.testZITrader();
//	tTests.testTaker();
//	tTests.testInformed();
//	tTests.testProvider();
//	tTests.testProvider5();
//	tTests.testMarketMaker();
//	tTests.testMarketMaker5();
//	engine.seed(44); 
//	tTests.testPJ();

//	OrderbookTests bTests;
//	std::string file1;

//	bTests.testExchangeAddHistory();
//	bTests.testExchangeAddBook2();
//	bTests.testOrderbookRemove();
//	bTests.testOrderbookModify();
//	bTests.testExchangeAddTrade();
//	bTests.testExchangeConfirmTrade();
//	bTests.testExchangeConfirmModify();
//	bTests.testExchangeBookTop();
//	bTests.testExchangeBookTop2();
//	bTests.testExchangeProcess();
//	bTests.testExchangeCrossCrash();
//	bTests.testExchangeCrossSell1();
//	bTests.testExchangeCrossBuy1();
//	file1 = "C:\\Users\\user\\Documents\\Agent-Based Models\\csv files\\history_1.csv";
//	bTests.testExchangeOrdersToCsv(file1);
//	file1 = "C:\\Users\\user\\Documents\\Agent-Based Models\\csv files\\trades_1.csv";
//	bTests.testExchangeTradesToCsv(file1);
//	file1 = "C:\\Users\\user\\Documents\\Agent-Based Models\\csv files\\sip_1.csv";
//	bTests.testExchangeSipToCsv(file1);

//	BucketTests kTests(defaultVec, distA, engine);
//	kTests.testZITrader();
//	kTests.testTaker();
//	kTests.testInformed();
//	kTests.testProvider();
//	kTests.testProvider5();
//	kTests.testMarketMaker();
//	kTests.testMarketMaker5();
//	kTests.testPJ();
//	kTests.testShuffle();

//	BucketTests2 kTests(defaultVec, distA, engine);
//	kTests.testZITrader();
//	kTests.testTaker();
//	kTests.testInformed();
//	kTests.testProvider();
//	kTests.testProvider5();
//	kTests.testMarketMaker();
//	kTests.testMarketMaker5();
//	kTests.testPJ();
//	kTests.testShuffle();

	RunnerTests rTests;
//	rTests.testConstructor();
//	rTests.testBuildProvider();
//	rTests.testBuildTakers();
//	rTests.testBuildInformed();
//	rTests.testBuildPennyJumper();
//	rTests.testBuildMarketMakers();
//	rTests.testBuildLambda();
//	std::string file1;
//	file1 = "C:\\Users\\user\\Documents\\Agent-Based Models\\csv files\\qtake_1.csv";
//	rTests.testQTakeToCsv(file1);
//	rTests.testSeedBook();
	rTests.testMakeSetup();

//	simpleTest(engine, distUreal);
//	simpleTest(engine, distUreal);
//	testMM5PS();
//	testInformedSteps();
//	testBucket();
//	_CrtDumpMemoryLeaks();

//	testExp2();


	return 0;
}
