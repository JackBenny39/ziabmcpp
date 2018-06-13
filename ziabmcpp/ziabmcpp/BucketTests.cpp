// BucketTests.cpp
// BucketTests class

#include "stdafx.h"

#include <iostream>

#include "BucketTests.h"


BucketTests::BucketTests(std::vector<int> &dVec, std::uniform_int_distribution<> &dUint, std::mt19937 &eng) :
	defaultVec(dVec), distUint(dUint), engine(eng)
{
	std::uniform_real_distribution<> distUreal(0, 1);
	
	engine.seed(44);
	bucket.push_back(std::make_shared<PennyJumper>(1, 4001, setMaxQ(50), 1));
	engine.seed(39);
	bucket.push_back(std::make_shared<ZITrader>(7, 1, setMaxQ(50), 1));
	bucket.push_back(std::make_shared<Taker>(11, 1001, setMaxQ(50), 1));
	bucket.push_back(std::make_shared<Informed>(2001, 1, Side::SELL, 1, 100, engine, distUint));
	bucket.push_back(std::make_shared<Provider>(17, 3001, setMaxQ(50), 0.85, 1));
	bucket.push_back(std::make_shared<Provider5>(22, 3005, setMaxQ(50), 0.05, 5));
	bucket.push_back(std::make_shared<MarketMaker>(1, 7001, setMaxQ(50), 0.05, 60, 12));
	bucket.push_back(std::make_shared<MarketMaker5>(1, 7005, setMaxQ(50), 0.05, 60, 12));
}

int BucketTests::setMaxQ(int maxq)
{
	std::vector<int> actualVec(0);
	std::copy_if(defaultVec.begin(), defaultVec.end(), std::back_inserter(actualVec), [&maxq](int i) { return i <= maxq; });
	std::uniform_int_distribution<int> distUintV(0, actualVec.size() - 1);
	return actualVec[distUintV(engine)];
}

void BucketTests::testInstances()
{
	cSide cSide1;

	std::cout << "Trader Type: " << bucket[0]->traderType << "; Max Quantity: " << bucket[0]->orderSize << "; Trader ID: " << bucket[0]->tId << "; MPI: "
		<< bucket[0]->mpi << "\n";
	std::cout << "Trader Type: " << bucket[1]->traderType << "; Max Quantity: " << bucket[1]->orderSize << "; Trader ID: " << bucket[1]->tId << "; MPI: "
		<< bucket[1]->mpi << "\n";
	std::cout << "Trader Type: " << bucket[2]->traderType << "; Max Quantity: " << bucket[2]->orderSize << "; Trader ID: " << bucket[2]->tId << "; MPI: "
		<< bucket[2]->mpi << "\n";
	cSide1 = bucket[3]->side == Side::BUY ? 'B' : 'S';
	std::cout << "Trader Type: " << bucket[3]->traderType << "; Max Quantity: " << bucket[3]->orderSize << "; Trader ID: " << bucket[3]->tId << "; Price:"
		<< bucket[3]->price << "; Side:" << cSide1 << "\n";
	std::cout << "Trader Type: " << bucket[4]->traderType << "; Max Quantity: " << bucket[4]->orderSize << "; Trader ID: " << bucket[4]->tId << "; MPI: "
		<< bucket[4]->mpi << "; Delta: " << bucket[4]->delta << "\n";
	std::cout << "Trader Type: " << bucket[5]->traderType << "; Max Quantity: " << bucket[5]->orderSize << "; Trader ID: " << bucket[5]->tId << "; MPI: "
		<< bucket[5]->mpi << "; Delta: " << bucket[5]->delta << "\n";
	std::cout << "Trader Type: " << bucket[6]->traderType << "; Max Quantity: " << bucket[6]->orderSize << "; Trader ID: " << bucket[6]->tId << "; NumQuotes: "
		<< bucket[6]->numQuotes << "; Quote Range: " << bucket[6]->quoteRange << "; Position: " << bucket[6]->position << "; Cash Flow: "
		<< bucket[6]->cashFlow << "\n";
	std::cout << "Trader Type: " << bucket[7]->traderType << "; Max Quantity: " << bucket[7]->orderSize << "; Trader ID: " << bucket[7]->tId << "; NumQuotes: "
		<< bucket[7]->numQuotes << "; Quote Range: " << bucket[7]->quoteRange << "; Position: " << bucket[7]->position << "; Cash Flow: "
		<< bucket[7]->cashFlow << "\n";

	std::cout << std::endl;
}

void BucketTests::testZITrader()
{
	Step step1;
	Side side1;
	Prc price1;
	cSide cSide1;

	std::cout << "Trader Type: " << bucket[1]->traderType << "\n";
	std::cout << "Arrival Interval: " << bucket[1]->arrInt << "\n";
	std::cout << "Max Quantity: " << bucket[1]->orderSize << "\n";
	std::cout << "Trader ID: " << bucket[1]->tId << "\n";
	std::cout << "MPI: " << bucket[1]->mpi << "\n";
	std::cout << "Quote Collector Before: " << bucket[1]->quoteCollector.size() << "\n";


	step1 = 23;
	side1 = Side::SELL;
	price1 = 1099;

	Order q1 = bucket[1]->makeAddQuote(step1, side1, price1);
	cSide1 = q1.side == Side::BUY ? 'B' : 'S';
	std::cout << "\nFirst Order: \n";
	std::cout << "Trader ID: " << q1.id << "\n";
	std::cout << "Order ID: " << q1.oid << "\n";
	std::cout << "Timestamp: " << q1.step << "\n";
	std::cout << "Type: " << q1.otype << "\n";
	std::cout << "Quantity: " << q1.qty << "\n";
	std::cout << "Side: " << cSide1 << "\n";
	std::cout << "Price: " << q1.price << "\n";

	step1 = 27;
	side1 = Side::BUY;
	price1 = 888;

	Order q2 = bucket[1]->makeAddQuote(step1, side1, price1);
	cSide1 = q2.side == Side::BUY ? 'B' : 'S';
	std::cout << "\nSecond Order: \n";
	std::cout << "Trader ID: " << q2.id << "\n";
	std::cout << "Order ID: " << q2.oid << "\n";
	std::cout << "Timestamp: " << q2.step << "\n";
	std::cout << "Type: " << q2.otype << "\n";
	std::cout << "Quantity: " << q2.qty << "\n";
	std::cout << "Side: " << cSide1 << "\n";
	std::cout << "Price: " << q2.price << "\n";
	std::cout << std::endl;
}

void BucketTests::testTaker()
{
	std::cout << "Trader Type: " << bucket[2]->traderType << "\n";
	std::cout << "Arrival Interval: " << bucket[2]->arrInt << "\n";
	std::cout << "Max Quantity: " << bucket[2]->orderSize << "\n";
	std::cout << "Trader ID: " << bucket[2]->tId << "\n";
	std::cout << "MPI: " << bucket[2]->mpi << "\n";
	std::cout << "Quote Collector Before: " << bucket[2]->quoteCollector.size() << "\n";

	Step step1 = 27;
	double qTake = 0.5;

	bucket[2]->processSignal(step1, qTake, engine, distUreal);
	cSide cSide3 = bucket[2]->quoteCollector[0].side == Side::BUY ? 'B' : 'S';
	std::cout << "\nQuote Collector After: " << bucket[2]->quoteCollector.size() << "\n";
	std::cout << "First Order: \n";
	std::cout << "Trader ID: " << bucket[2]->quoteCollector[0].id << "\n";
	std::cout << "Order ID: " << bucket[2]->quoteCollector[0].oid << "\n";
	std::cout << "Timestamp: " << bucket[2]->quoteCollector[0].step << "\n";
	std::cout << "Type: " << bucket[2]->quoteCollector[0].otype << "\n";
	std::cout << "Quantity: " << bucket[2]->quoteCollector[0].qty << "\n";
	std::cout << "Side: " << cSide3 << "\n";
	std::cout << "Price: " << bucket[2]->quoteCollector[0].price << "\n";
	std::cout << std::endl;
}

void BucketTests::testInformed()
{
	cSide cSide1;
	Step step1;
	Qty maxQ;
	unsigned runL, numT, numChoices;

	std::cout << "Trader Type: " << bucket[3]->traderType << "\n";
	std::cout << "Max Quantity: " << bucket[3]->orderSize << "\n";
	std::cout << "Trader ID: " << bucket[3]->tId << "\n";

	int counter = 0;
	std::set<int> srtd1(bucket[3]->steps.begin(), bucket[3]->steps.end());
	std::cout << "\n\nArrival steps: \n";
	for (auto &x : srtd1)
		std::cout << "Choice " << ++counter << ": " << x << "\n";

	std::cout << "\n\nQuote Collector Before: " << bucket[3]->quoteCollector.size() << "\n";

	step1 = 27;

	bucket[3]->processSignal(step1);
	cSide1 = bucket[3]->quoteCollector[0].side == Side::BUY ? 'B' : 'S';

	std::cout << "Quote Collector After: " << bucket[3]->quoteCollector.size() << "\n";
	std::cout << "First Order: \n";
	std::cout << "Trader ID: " << bucket[3]->quoteCollector[0].id << "\n";
	std::cout << "Order ID: " << bucket[3]->quoteCollector[0].oid << "\n";
	std::cout << "Timestamp: " << bucket[3]->quoteCollector[0].step << "\n";
	std::cout << "Type: " << bucket[3]->quoteCollector[0].otype << "\n";
	std::cout << "Quantity: " << bucket[3]->quoteCollector[0].qty << "\n";
	std::cout << "Side: " << cSide1 << "\n";
	std::cout << "Price: " << bucket[3]->quoteCollector[0].price << "\n";

	maxQ = 5;
	runL = 3;
	numT = 100;
	numChoices = (numT / (runL*maxQ)) + 1;
	bucket.push_back(std::make_shared<Informed>(2, maxQ, Side::BUY, runL, numChoices, engine, distUint));

	std::cout << "\n\nTrader Type: " << bucket[8]->traderType << "\n";
	std::cout << "Max Quantity: " << bucket[8]->orderSize << "\n";
	std::cout << "Trader ID: " << bucket[8]->tId << "\n";
	std::cout << "Quote Collector Before: " << bucket[8]->quoteCollector.size() << "\n";

	counter = 0;
	std::set<int> srtd2(bucket[8]->steps.begin(), bucket[8]->steps.end());
	std::cout << "\n\nArrival steps: \n";
	for (auto &x : srtd2)
		std::cout << "Choice " << ++counter << ": " << x << "\n";

	step1 = 29;

	bucket[8]->processSignal(step1);
	cSide1 = bucket[8]->quoteCollector[0].side == Side::BUY ? 'B' : 'S';

	std::cout << "\n\nQuote Collector After: " << bucket[8]->quoteCollector.size() << "\n";
	std::cout << "First Order: \n";
	std::cout << "Trader ID: " << bucket[8]->quoteCollector[0].id << "\n";
	std::cout << "Order ID: " << bucket[8]->quoteCollector[0].oid << "\n";
	std::cout << "Timestamp: " << bucket[8]->quoteCollector[0].step << "\n";
	std::cout << "Type: " << bucket[8]->quoteCollector[0].otype << "\n";
	std::cout << "Quantity: " << bucket[8]->quoteCollector[0].qty << "\n";
	std::cout << "Side: " << cSide1 << "\n";
	std::cout << "Price: " << bucket[8]->quoteCollector[0].price << "\n";
	std::cout << std::endl;
}

void BucketTests::testProvider()
{
	cSide cSide1;

	// Test constructor
	std::cout << "Trader Type: " << bucket[4]->traderType << "\n";
	std::cout << "Max Quantity: " << bucket[4]->orderSize << "\n";
	std::cout << "Trader ID: " << bucket[4]->tId << "\n";
	std::cout << "Delta: " << bucket[4]->delta << "\n";
	std::cout << "MPI: " << bucket[4]->mpi << "\n";
	std::cout << "Quote Collector Before: " << bucket[4]->quoteCollector.size() << "\n";

	// Test makeCancelQuote
	Order o3{ 3001, 2, 3, 'A', 100, Side::SELL, 1005 };
	Order c1 = bucket[4]->makeCancelQuote(o3, 132);
	cSide1 = c1.side == Side::BUY ? 'B' : 'S';
	std::cout << "\n\nTest makeCancelQuote: \n";
	std::cout << "First Cancel: \n";
	std::cout << "Trader ID: " << c1.id << "\n";
	std::cout << "Order ID: " << c1.oid << "\n";
	std::cout << "Timestamp: " << c1.step << "\n";
	std::cout << "Type: " << c1.otype << "\n";
	std::cout << "Quantity: " << c1.qty << "\n";
	std::cout << "Side: " << cSide1 << "\n";
	std::cout << "Price: " << c1.price << "\n";

	// Test processSignal and chooseP (seed = 39)
	engine.seed(39);
	Step step1;
	TopOfBook tob;

	bucket.push_back(std::make_shared<Provider>(17, 3001, setMaxQ(50), 0.85, 1));
	
	step1 = 27;
	tob = { step1, 999, 250, 1008, 300 };

	bucket[8]->processSignal(tob, step1, 0.5, -100, engine, distUreal);
	cSide1 = bucket[8]->quoteCollector[0].side == Side::BUY ? 'B' : 'S';
	std::cout << "\n\nQuote Collector After: " << bucket[8]->quoteCollector.size() << "\n";
	std::cout << "First Order (Sell @ 1019): \n";
	std::cout << "Trader ID: " << bucket[8]->quoteCollector[0].id << "\n";
	std::cout << "Order ID: " << bucket[8]->quoteCollector[0].oid << "\n";
	std::cout << "Timestamp: " << bucket[8]->quoteCollector[0].step << "\n";
	std::cout << "Type: " << bucket[8]->quoteCollector[0].otype << "\n";
	std::cout << "Quantity: " << bucket[8]->quoteCollector[0].qty << "\n";
	std::cout << "Side: " << cSide1 << "\n";
	std::cout << "Price: " << bucket[8]->quoteCollector[0].price << "\n";

	bucket[8]->processSignal(tob, step1, 0.5, -100, engine, distUreal);
	cSide1 = bucket[8]->quoteCollector[1].side == Side::BUY ? 'B' : 'S';
	std::cout << "\n\nQuote Collector After: " << bucket[8]->quoteCollector.size() << "\n";
	std::cout << "Second Order (Buy @ 957): \n";
	std::cout << "Trader ID: " << bucket[8]->quoteCollector[1].id << "\n";
	std::cout << "Order ID: " << bucket[8]->quoteCollector[1].oid << "\n";
	std::cout << "Timestamp: " << bucket[8]->quoteCollector[1].step << "\n";
	std::cout << "Type: " << bucket[8]->quoteCollector[1].otype << "\n";
	std::cout << "Quantity: " << bucket[8]->quoteCollector[1].qty << "\n";
	std::cout << "Side: " << cSide1 << "\n";
	std::cout << "Price: " << bucket[8]->quoteCollector[1].price << "\n";

	bucket[8]->processSignal(tob, step1, 0.5, -100, engine, distUreal);
	cSide1 = bucket[8]->quoteCollector[2].side == Side::BUY ? 'B' : 'S';
	std::cout << "\n\nQuote Collector After: " << bucket[8]->quoteCollector.size() << "\n";
	std::cout << "Third Order (Sell @ 1076): \n";
	std::cout << "Trader ID: " << bucket[8]->quoteCollector[2].id << "\n";
	std::cout << "Order ID: " << bucket[8]->quoteCollector[2].oid << "\n";
	std::cout << "Timestamp: " << bucket[8]->quoteCollector[2].step << "\n";
	std::cout << "Type: " << bucket[8]->quoteCollector[2].otype << "\n";
	std::cout << "Quantity: " << bucket[8]->quoteCollector[2].qty << "\n";
	std::cout << "Side: " << cSide1 << "\n";
	std::cout << "Price: " << bucket[8]->quoteCollector[2].price << "\n";

	bucket[8]->processSignal(tob, step1, 0.5, -100, engine, distUreal);
	cSide1 = bucket[8]->quoteCollector[3].side == Side::BUY ? 'B' : 'S';
	std::cout << "\n\nQuote Collector After: " << bucket[8]->quoteCollector.size() << "\n";
	std::cout << "Fourth Order (Buy @ 962): \n";
	std::cout << "Trader ID: " << bucket[8]->quoteCollector[3].id << "\n";
	std::cout << "Order ID: " << bucket[8]->quoteCollector[3].oid << "\n";
	std::cout << "Timestamp: " << bucket[8]->quoteCollector[3].step << "\n";
	std::cout << "Type: " << bucket[8]->quoteCollector[3].otype << "\n";
	std::cout << "Quantity: " << bucket[8]->quoteCollector[3].qty << "\n";
	std::cout << "Side: " << cSide1 << "\n";
	std::cout << "Price: " << bucket[8]->quoteCollector[3].price << "\n";

	bucket[8]->processSignal(tob, step1, 0.5, -100, engine, distUreal);
	cSide1 = bucket[8]->quoteCollector[4].side == Side::BUY ? 'B' : 'S';
	std::cout << "\n\nQuote Collector After: " << bucket[8]->quoteCollector.size() << "\n";
	std::cout << "Fifth Order (Sell @ 1020): \n";
	std::cout << "Trader ID: " << bucket[8]->quoteCollector[4].id << "\n";
	std::cout << "Order ID: " << bucket[8]->quoteCollector[4].oid << "\n";
	std::cout << "Timestamp: " << bucket[8]->quoteCollector[4].step << "\n";
	std::cout << "Type: " << bucket[8]->quoteCollector[4].otype << "\n";
	std::cout << "Quantity: " << bucket[8]->quoteCollector[4].qty << "\n";
	std::cout << "Side: " << cSide1 << "\n";
	std::cout << "Price: " << bucket[8]->quoteCollector[4].price << "\n";

	std::cout << "\nOrder Book:" << "\n";
	for (auto &x : bucket[8]->localBook)
		std::cout << "TraderId: " << x.second.id
		<< " Order Id: " << x.second.oid
		<< " Order Type: " << x.second.otype
		<< " Order Price: " << x.second.price
		<< " Order Qty: " << x.second.qty
		<< " Order Side: " << (x.second.side == Side::BUY ? 'B' : 'S')
		<< " Order Step: " << x.second.step << "\n";

	// Test bulkCancel with delta = 0.85
	bucket[8]->bulkCancel(45, engine, distUreal);
	std::cout << "\nCancel Collector should have two orders: 3&4" << "\n";
	for (auto &x : bucket[8]->cancelCollector)
		std::cout << "TraderId: " << x.id
		<< " Order Id: " << x.oid
		<< " Order Type: " << x.otype
		<< " Order Price: " << x.price
		<< " Order Qty: " << x.qty
		<< " Order Side: " << (x.side == Side::BUY ? 'B' : 'S')
		<< " Order Step: " << x.step << "\n";

	// Test confirm Cancel by removing #5 from localBook
	bucket[8]->confirmCancel(5);
	std::cout << "\nOrder Book should be missing #5:" << "\n";
	for (auto &x : bucket[8]->localBook)
		std::cout << "TraderId: " << x.second.id
		<< " Order Id: " << x.second.oid
		<< " Order Type: " << x.second.otype
		<< " Order Price: " << x.second.price
		<< " Order Qty: " << x.second.qty
		<< " Order Side: " << (x.second.side == Side::BUY ? 'B' : 'S')
		<< " Order Step: " << x.second.step << "\n";

	//Test confirmTrade by removing 30 shares, then the remaining 20
	TConfirm t1{ 3001, 4, 89, 30, Side::BUY, 962 };
	bucket[8]->confirmTrade(t1);
	std::cout << "\nOrder Book #4 should have quantity = 20:" << "\n";
	for (auto &x : bucket[8]->localBook)
		std::cout << "TraderId: " << x.second.id
		<< " Order Id: " << x.second.oid
		<< " Order Type: " << x.second.otype
		<< " Order Price: " << x.second.price
		<< " Order Qty: " << x.second.qty
		<< " Order Side: " << (x.second.side == Side::BUY ? 'B' : 'S')
		<< " Order Step: " << x.second.step << "\n";

	TConfirm t2{ 3001, 4, 92, 20, Side::BUY, 962 };
	bucket[8]->confirmTrade(t2);
	std::cout << "\nOrder Book should be missing #4:" << "\n";
	for (auto &x : bucket[8]->localBook)
		std::cout << "TraderId: " << x.second.id
		<< " Order Id: " << x.second.oid
		<< " Order Type: " << x.second.otype
		<< " Order Price: " << x.second.price
		<< " Order Qty: " << x.second.qty
		<< " Order Side: " << (x.second.side == Side::BUY ? 'B' : 'S')
		<< " Order Step: " << x.second.step << "\n";
	std::cout << std::endl;
}

void BucketTests::testProvider5()
{
	engine.seed(39); 
	cSide cSide1;

	bucket.push_back(std::make_shared<Provider5>(22, 3005, setMaxQ(50), 0.05, 5));

	// Test constructor
	std::cout << "Trader Type: " << bucket[8]->traderType << "\n";
	std::cout << "Max Quantity: " << bucket[8]->orderSize << "\n";
	std::cout << "Trader ID: " << bucket[8]->tId << "\n";
	std::cout << "Delta: " << bucket[8]->delta << "\n";
	std::cout << "Quote Collector Before: " << bucket[8]->quoteCollector.size() << "\n";

	// Test processSignal and chooseP (seed = 39)
	Step step1;
	TopOfBook tob;

	step1 = 27;
	tob = { step1, 995, 250, 1010, 300 };
	//	simpleTest(engine, distUreal);

	bucket[8]->processSignal(tob, step1, 0.5, -100, engine, distUreal);
	cSide1 = bucket[8]->quoteCollector[0].side == Side::BUY ? 'B' : 'S';
	std::cout << "\n\nQuote Collector After: " << bucket[8]->quoteCollector.size() << "\n";
	std::cout << "First Order (Sell @ 1020): \n";
	std::cout << "Trader ID: " << bucket[8]->quoteCollector[0].id << "\n";
	std::cout << "Order ID: " << bucket[8]->quoteCollector[0].oid << "\n";
	std::cout << "Timestamp: " << bucket[8]->quoteCollector[0].step << "\n";
	std::cout << "Type: " << bucket[8]->quoteCollector[0].otype << "\n";
	std::cout << "Quantity: " << bucket[8]->quoteCollector[0].qty << "\n";
	std::cout << "Side: " << cSide1 << "\n";
	std::cout << "Price: " << bucket[8]->quoteCollector[0].price << "\n";

	bucket[8]->processSignal(tob, step1, 0.5, -100, engine, distUreal);
	cSide1 = bucket[8]->quoteCollector[1].side == Side::BUY ? 'B' : 'S';
	std::cout << "\n\nQuote Collector After: " << bucket[8]->quoteCollector.size() << "\n";
	std::cout << "Second Order (Buy @ 955): \n";
	std::cout << "Trader ID: " << bucket[8]->quoteCollector[1].id << "\n";
	std::cout << "Order ID: " << bucket[8]->quoteCollector[1].oid << "\n";
	std::cout << "Timestamp: " << bucket[8]->quoteCollector[1].step << "\n";
	std::cout << "Type: " << bucket[8]->quoteCollector[1].otype << "\n";
	std::cout << "Quantity: " << bucket[8]->quoteCollector[1].qty << "\n";
	std::cout << "Side: " << cSide1 << "\n";
	std::cout << "Price: " << bucket[8]->quoteCollector[1].price << "\n";

	bucket[8]->processSignal(tob, step1, 0.5, -100, engine, distUreal);
	cSide1 = bucket[8]->quoteCollector[2].side == Side::BUY ? 'B' : 'S';
	std::cout << "\n\nQuote Collector After: " << bucket[8]->quoteCollector.size() << "\n";
	std::cout << "Third Order (Sell @ 1075): \n";
	std::cout << "Trader ID: " << bucket[8]->quoteCollector[2].id << "\n";
	std::cout << "Order ID: " << bucket[8]->quoteCollector[2].oid << "\n";
	std::cout << "Timestamp: " << bucket[8]->quoteCollector[2].step << "\n";
	std::cout << "Type: " << bucket[8]->quoteCollector[2].otype << "\n";
	std::cout << "Quantity: " << bucket[8]->quoteCollector[2].qty << "\n";
	std::cout << "Side: " << cSide1 << "\n";
	std::cout << "Price: " << bucket[8]->quoteCollector[2].price << "\n";

	bucket[8]->processSignal(tob, step1, 0.5, -100, engine, distUreal);
	cSide1 = bucket[8]->quoteCollector[3].side == Side::BUY ? 'B' : 'S';
	std::cout << "\n\nQuote Collector After: " << bucket[8]->quoteCollector.size() << "\n";
	std::cout << "Fourth Order (Buy @ 960): \n";
	std::cout << "Trader ID: " << bucket[8]->quoteCollector[3].id << "\n";
	std::cout << "Order ID: " << bucket[8]->quoteCollector[3].oid << "\n";
	std::cout << "Timestamp: " << bucket[8]->quoteCollector[3].step << "\n";
	std::cout << "Type: " << bucket[8]->quoteCollector[3].otype << "\n";
	std::cout << "Quantity: " << bucket[8]->quoteCollector[3].qty << "\n";
	std::cout << "Side: " << cSide1 << "\n";
	std::cout << "Price: " << bucket[8]->quoteCollector[3].price << "\n";

	bucket[8]->processSignal(tob, step1, 0.5, -100, engine, distUreal);
	cSide1 = bucket[8]->quoteCollector[4].side == Side::BUY ? 'B' : 'S';
	std::cout << "\n\nQuote Collector After: " << bucket[8]->quoteCollector.size() << "\n";
	std::cout << "Fifth Order (Sell @ 1020): \n";
	std::cout << "Trader ID: " << bucket[8]->quoteCollector[4].id << "\n";
	std::cout << "Order ID: " << bucket[8]->quoteCollector[4].oid << "\n";
	std::cout << "Timestamp: " << bucket[8]->quoteCollector[4].step << "\n";
	std::cout << "Type: " << bucket[8]->quoteCollector[4].otype << "\n";
	std::cout << "Quantity: " << bucket[8]->quoteCollector[4].qty << "\n";
	std::cout << "Side: " << cSide1 << "\n";
	std::cout << "Price: " << bucket[8]->quoteCollector[4].price << "\n";

	std::cout << "\nOrder Book:" << "\n";
	for (auto &x : bucket[8]->localBook)
		std::cout << "TraderId: " << x.second.id
		<< " Order Id: " << x.second.oid
		<< " Order Type: " << x.second.otype
		<< " Order Price: " << x.second.price
		<< " Order Qty: " << x.second.qty
		<< " Order Side: " << (x.second.side == Side::BUY ? 'B' : 'S')
		<< " Order Step: " << x.second.step << "\n";
	std::cout << std::endl;
}