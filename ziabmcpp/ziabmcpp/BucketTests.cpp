// BucketTests.cpp
// BucketTests class

#include "stdafx.h"

#include <iostream>

#include "BucketTests.h"


BucketTests::BucketTests(std::vector<int> &dVec, std::uniform_int_distribution<> &dUint, std::mt19937 &eng) :
	defaultVec(dVec), distUint(dUint), engine(eng)
{
	std::uniform_real_distribution<> distUreal(0, 1);
}

int BucketTests::setMaxQ(int maxq)
{
	std::vector<int> actualVec(0);
	std::copy_if(defaultVec.begin(), defaultVec.end(), std::back_inserter(actualVec), [&maxq](int i) { return i <= maxq; });
	std::uniform_int_distribution<int> distUintV(0, actualVec.size() - 1);
	return actualVec[distUintV(engine)];
}

void BucketTests::testZITrader()
{
	Step step1;
	Side side1;
	Prc price1;
	cSide cSide1;

	mappedBucket[1] = std::make_shared<ZITrader>(7, 1, setMaxQ(50), 1);

	std::cout << "Trader Type: " << mappedBucket[1]->traderType << "\n";
	std::cout << "Arrival Interval: " << mappedBucket[1]->arrInt << "\n";
	std::cout << "Max Quantity: " << mappedBucket[1]->orderSize << "\n";
	std::cout << "Trader ID: " << mappedBucket[1]->tId << "\n";
	std::cout << "MPI: " << mappedBucket[1]->mpi << "\n";
	std::cout << "Quote Collector Before: " << mappedBucket[1]->quoteCollector.size() << "\n";


	step1 = 23;
	side1 = Side::SELL;
	price1 = 1099;

	Order q1 = mappedBucket[1]->makeAddQuote(step1, side1, price1);
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

	Order q2 = mappedBucket[1]->makeAddQuote(step1, side1, price1);
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
	mappedBucket[1001] = std::make_shared<Taker>(11, 1001, setMaxQ(50), 1);

	std::cout << "Trader Type: " << mappedBucket[1001]->traderType << "\n";
	std::cout << "Arrival Interval: " << mappedBucket[1001]->arrInt << "\n";
	std::cout << "Max Quantity: " << mappedBucket[1001]->orderSize << "\n";
	std::cout << "Trader ID: " << mappedBucket[1001]->tId << "\n";
	std::cout << "MPI: " << mappedBucket[1001]->mpi << "\n";
	std::cout << "Quote Collector Before: " << mappedBucket[1001]->quoteCollector.size() << "\n";

	Step step1 = 27;
	double qTake = 0.5;

	mappedBucket[1001]->processSignal(step1, qTake, engine, distUreal);
	cSide cSide3 = mappedBucket[1001]->quoteCollector[0].side == Side::BUY ? 'B' : 'S';
	std::cout << "\nQuote Collector After: " << mappedBucket[1001]->quoteCollector.size() << "\n";
	std::cout << "First Order: \n";
	std::cout << "Trader ID: " << mappedBucket[1001]->quoteCollector[0].id << "\n";
	std::cout << "Order ID: " << mappedBucket[1001]->quoteCollector[0].oid << "\n";
	std::cout << "Timestamp: " << mappedBucket[1001]->quoteCollector[0].step << "\n";
	std::cout << "Type: " << mappedBucket[1001]->quoteCollector[0].otype << "\n";
	std::cout << "Quantity: " << mappedBucket[1001]->quoteCollector[0].qty << "\n";
	std::cout << "Side: " << cSide3 << "\n";
	std::cout << "Price: " << mappedBucket[1001]->quoteCollector[0].price << "\n";
	std::cout << std::endl;
}

void BucketTests::testInformed()
{
	mappedBucket[2001] = std::make_shared<Informed>(2001, 1, Side::SELL, 1, 100, engine, distUint);

	cSide cSide1;
	Step step1;
	Qty maxQ;
	unsigned runL, numT, numChoices;

	std::cout << "Trader Type: " << mappedBucket[2001]->traderType << "\n";
	std::cout << "Max Quantity: " << mappedBucket[2001]->orderSize << "\n";
	std::cout << "Trader ID: " << mappedBucket[2001]->tId << "\n";

	int counter = 0;
	std::cout << "\n\nArrival steps: \n";
	for (auto &x : mappedBucket[2001]->steps)
		std::cout << "Choice " << ++counter << ": " << x << "\n";

	std::cout << "\n\nQuote Collector Before: " << mappedBucket[2001]->quoteCollector.size() << "\n";

	step1 = mappedBucket[2001]->arrInt;

	std::cout << "First step from arrival interval = " << mappedBucket[2001]->arrInt << "\n";

	mappedBucket[2001]->processSignal(step1);
	cSide1 = mappedBucket[2001]->quoteCollector[0].side == Side::BUY ? 'B' : 'S';

	std::cout << "Second step from arrival interval = " << mappedBucket[2001]->arrInt << "\n";

	std::cout << "Quote Collector After: " << mappedBucket[2001]->quoteCollector.size() << "\n";
	std::cout << "First Order: \n";
	std::cout << "Trader ID: " << mappedBucket[2001]->quoteCollector[0].id << "\n";
	std::cout << "Order ID: " << mappedBucket[2001]->quoteCollector[0].oid << "\n";
	std::cout << "Timestamp: " << mappedBucket[2001]->quoteCollector[0].step << "\n";
	std::cout << "Type: " << mappedBucket[2001]->quoteCollector[0].otype << "\n";
	std::cout << "Quantity: " << mappedBucket[2001]->quoteCollector[0].qty << "\n";
	std::cout << "Side: " << cSide1 << "\n";
	std::cout << "Price: " << mappedBucket[2001]->quoteCollector[0].price << "\n";

	maxQ = 5;
	runL = 3;
	numT = 100;
	numChoices = (numT / (runL*maxQ)) + 1;
	mappedBucket[2002] = std::make_shared<Informed>(2002, 1, Side::SELL, 1, 100, engine, distUint);

	std::cout << "\n\nTrader Type: " << mappedBucket[2002]->traderType << "\n";
	std::cout << "Max Quantity: " << mappedBucket[2002]->orderSize << "\n";
	std::cout << "Trader ID: " << mappedBucket[2002]->tId << "\n";
	std::cout << "Quote Collector Before: " << mappedBucket[2002]->quoteCollector.size() << "\n";

	counter = 0;
	std::cout << "\n\nArrival steps: \n";
	for (auto &x : mappedBucket[2002]->steps)
		std::cout << "Choice " << ++counter << ": " << x << "\n";

	step1 = mappedBucket[2002]->arrInt;

	std::cout << "First step from arrival interval = " << mappedBucket[2002]->arrInt << "\n";

	mappedBucket[2002]->processSignal(step1);
	cSide1 = mappedBucket[2002]->quoteCollector[0].side == Side::BUY ? 'B' : 'S';

	std::cout << "Second step from arrival interval = " << mappedBucket[2002]->arrInt << "\n";

	std::cout << "\n\nQuote Collector After: " << mappedBucket[2002]->quoteCollector.size() << "\n";
	std::cout << "First Order: \n";
	std::cout << "Trader ID: " << mappedBucket[2002]->quoteCollector[0].id << "\n";
	std::cout << "Order ID: " << mappedBucket[2002]->quoteCollector[0].oid << "\n";
	std::cout << "Timestamp: " << mappedBucket[2002]->quoteCollector[0].step << "\n";
	std::cout << "Type: " << mappedBucket[2002]->quoteCollector[0].otype << "\n";
	std::cout << "Quantity: " << mappedBucket[2002]->quoteCollector[0].qty << "\n";
	std::cout << "Side: " << cSide1 << "\n";
	std::cout << "Price: " << mappedBucket[2002]->quoteCollector[0].price << "\n";
	std::cout << std::endl;
}

void BucketTests::testProvider()
{
	mappedBucket[3001] = std::make_shared<Provider>(17, 3001, setMaxQ(50), 0.85, 1);

	cSide cSide1;

	// Test constructor
	std::cout << "Trader Type: " << mappedBucket[3001]->traderType << "\n";
	std::cout << "Max Quantity: " << mappedBucket[3001]->orderSize << "\n";
	std::cout << "Trader ID: " << mappedBucket[3001]->tId << "\n";
	std::cout << "Delta: " << mappedBucket[3001]->delta << "\n";
	std::cout << "MPI: " << mappedBucket[3001]->mpi << "\n";
	std::cout << "Quote Collector Before: " << mappedBucket[3001]->quoteCollector.size() << "\n";

	// Test makeCancelQuote
	Order o3{ 3001, 2, 3, 'A', 100, Side::SELL, 1005 };
	Order c1 = mappedBucket[3001]->makeCancelQuote(o3, 132);
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

	mappedBucket[3002] = std::make_shared<Provider>(17, 3002, setMaxQ(50), 0.85, 1);
	
	step1 = 27;
	tob = { step1, 999, 250, 1008, 300 };

	mappedBucket[3002]->processSignal(tob, step1, 0.5, -100, engine, distUreal);
	cSide1 = mappedBucket[3002]->quoteCollector[0].side == Side::BUY ? 'B' : 'S';
	std::cout << "\n\nQuote Collector After: " << mappedBucket[3002]->quoteCollector.size() << "\n";
	std::cout << "First Order (Sell @ 1019): \n";
	std::cout << "Trader ID: " << mappedBucket[3002]->quoteCollector[0].id << "\n";
	std::cout << "Order ID: " << mappedBucket[3002]->quoteCollector[0].oid << "\n";
	std::cout << "Timestamp: " << mappedBucket[3002]->quoteCollector[0].step << "\n";
	std::cout << "Type: " << mappedBucket[3002]->quoteCollector[0].otype << "\n";
	std::cout << "Quantity: " << mappedBucket[3002]->quoteCollector[0].qty << "\n";
	std::cout << "Side: " << cSide1 << "\n";
	std::cout << "Price: " << mappedBucket[3002]->quoteCollector[0].price << "\n";

	mappedBucket[3002]->processSignal(tob, step1, 0.5, -100, engine, distUreal);
	cSide1 = mappedBucket[3002]->quoteCollector[1].side == Side::BUY ? 'B' : 'S';
	std::cout << "\n\nQuote Collector After: " << mappedBucket[3002]->quoteCollector.size() << "\n";
	std::cout << "Second Order (Buy @ 957): \n";
	std::cout << "Trader ID: " << mappedBucket[3002]->quoteCollector[1].id << "\n";
	std::cout << "Order ID: " << mappedBucket[3002]->quoteCollector[1].oid << "\n";
	std::cout << "Timestamp: " << mappedBucket[3002]->quoteCollector[1].step << "\n";
	std::cout << "Type: " << mappedBucket[3002]->quoteCollector[1].otype << "\n";
	std::cout << "Quantity: " << mappedBucket[3002]->quoteCollector[1].qty << "\n";
	std::cout << "Side: " << cSide1 << "\n";
	std::cout << "Price: " << mappedBucket[3002]->quoteCollector[1].price << "\n";

	mappedBucket[3002]->processSignal(tob, step1, 0.5, -100, engine, distUreal);
	cSide1 = mappedBucket[3002]->quoteCollector[2].side == Side::BUY ? 'B' : 'S';
	std::cout << "\n\nQuote Collector After: " << mappedBucket[3002]->quoteCollector.size() << "\n";
	std::cout << "Third Order (Sell @ 1076): \n";
	std::cout << "Trader ID: " << mappedBucket[3002]->quoteCollector[2].id << "\n";
	std::cout << "Order ID: " << mappedBucket[3002]->quoteCollector[2].oid << "\n";
	std::cout << "Timestamp: " << mappedBucket[3002]->quoteCollector[2].step << "\n";
	std::cout << "Type: " << mappedBucket[3002]->quoteCollector[2].otype << "\n";
	std::cout << "Quantity: " << mappedBucket[3002]->quoteCollector[2].qty << "\n";
	std::cout << "Side: " << cSide1 << "\n";
	std::cout << "Price: " << mappedBucket[3002]->quoteCollector[2].price << "\n";

	mappedBucket[3002]->processSignal(tob, step1, 0.5, -100, engine, distUreal);
	cSide1 = mappedBucket[3002]->quoteCollector[3].side == Side::BUY ? 'B' : 'S';
	std::cout << "\n\nQuote Collector After: " << mappedBucket[3002]->quoteCollector.size() << "\n";
	std::cout << "Fourth Order (Buy @ 962): \n";
	std::cout << "Trader ID: " << mappedBucket[3002]->quoteCollector[3].id << "\n";
	std::cout << "Order ID: " << mappedBucket[3002]->quoteCollector[3].oid << "\n";
	std::cout << "Timestamp: " << mappedBucket[3002]->quoteCollector[3].step << "\n";
	std::cout << "Type: " << mappedBucket[3002]->quoteCollector[3].otype << "\n";
	std::cout << "Quantity: " << mappedBucket[3002]->quoteCollector[3].qty << "\n";
	std::cout << "Side: " << cSide1 << "\n";
	std::cout << "Price: " << mappedBucket[3002]->quoteCollector[3].price << "\n";

	mappedBucket[3002]->processSignal(tob, step1, 0.5, -100, engine, distUreal);
	cSide1 = mappedBucket[3002]->quoteCollector[4].side == Side::BUY ? 'B' : 'S';
	std::cout << "\n\nQuote Collector After: " << mappedBucket[3002]->quoteCollector.size() << "\n";
	std::cout << "Fifth Order (Sell @ 1020): \n";
	std::cout << "Trader ID: " << mappedBucket[3002]->quoteCollector[4].id << "\n";
	std::cout << "Order ID: " << mappedBucket[3002]->quoteCollector[4].oid << "\n";
	std::cout << "Timestamp: " << mappedBucket[3002]->quoteCollector[4].step << "\n";
	std::cout << "Type: " << mappedBucket[3002]->quoteCollector[4].otype << "\n";
	std::cout << "Quantity: " << mappedBucket[3002]->quoteCollector[4].qty << "\n";
	std::cout << "Side: " << cSide1 << "\n";
	std::cout << "Price: " << mappedBucket[3002]->quoteCollector[4].price << "\n";

	std::cout << "\nOrder Book:" << "\n";
	for (auto &x : mappedBucket[3002]->localBook)
		std::cout << "TraderId: " << x.second.id
		<< " Order Id: " << x.second.oid
		<< " Order Type: " << x.second.otype
		<< " Order Price: " << x.second.price
		<< " Order Qty: " << x.second.qty
		<< " Order Side: " << (x.second.side == Side::BUY ? 'B' : 'S')
		<< " Order Step: " << x.second.step << "\n";

	// Test bulkCancel with delta = 0.85
	mappedBucket[3002]->bulkCancel(45, engine, distUreal);
	std::cout << "\nCancel Collector should have two orders: 3&4" << "\n";
	for (auto &x : mappedBucket[3002]->cancelCollector)
		std::cout << "TraderId: " << x.id
		<< " Order Id: " << x.oid
		<< " Order Type: " << x.otype
		<< " Order Price: " << x.price
		<< " Order Qty: " << x.qty
		<< " Order Side: " << (x.side == Side::BUY ? 'B' : 'S')
		<< " Order Step: " << x.step << "\n";

	// Test confirm Cancel by removing #5 from localBook
	mappedBucket[3002]->confirmCancel(5);
	std::cout << "\nOrder Book should be missing #5:" << "\n";
	for (auto &x : mappedBucket[3002]->localBook)
		std::cout << "TraderId: " << x.second.id
		<< " Order Id: " << x.second.oid
		<< " Order Type: " << x.second.otype
		<< " Order Price: " << x.second.price
		<< " Order Qty: " << x.second.qty
		<< " Order Side: " << (x.second.side == Side::BUY ? 'B' : 'S')
		<< " Order Step: " << x.second.step << "\n";

	//Test confirmTrade by removing 30 shares, then the remaining 20
	TConfirm t1{ 3001, 4, 89, 30, Side::BUY, 962 };
	mappedBucket[3002]->confirmTrade(t1);
	std::cout << "\nOrder Book #4 should have quantity = 20:" << "\n";
	for (auto &x : mappedBucket[3002]->localBook)
		std::cout << "TraderId: " << x.second.id
		<< " Order Id: " << x.second.oid
		<< " Order Type: " << x.second.otype
		<< " Order Price: " << x.second.price
		<< " Order Qty: " << x.second.qty
		<< " Order Side: " << (x.second.side == Side::BUY ? 'B' : 'S')
		<< " Order Step: " << x.second.step << "\n";

	TConfirm t2{ 3001, 4, 92, 20, Side::BUY, 962 };
	mappedBucket[3002]->confirmTrade(t2);
	std::cout << "\nOrder Book should be missing #4:" << "\n";
	for (auto &x : mappedBucket[3002]->localBook)
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

	mappedBucket[3005] = std::make_shared<Provider5>(22, 3005, setMaxQ(50), 0.05, 5);

	// Test constructor
	std::cout << "Trader Type: " << mappedBucket[3005]->traderType << "\n";
	std::cout << "Max Quantity: " << mappedBucket[3005]->orderSize << "\n";
	std::cout << "Trader ID: " << mappedBucket[3005]->tId << "\n";
	std::cout << "Delta: " << mappedBucket[3005]->delta << "\n";
	std::cout << "Quote Collector Before: " << mappedBucket[3005]->quoteCollector.size() << "\n";

	// Test processSignal and chooseP (seed = 39)
	Step step1;
	TopOfBook tob;

	step1 = 27;
	tob = { step1, 995, 250, 1010, 300 };
	//	simpleTest(engine, distUreal);

	mappedBucket[3005]->processSignal(tob, step1, 0.5, -100, engine, distUreal);
	cSide1 = mappedBucket[3005]->quoteCollector[0].side == Side::BUY ? 'B' : 'S';
	std::cout << "\n\nQuote Collector After: " << mappedBucket[3005]->quoteCollector.size() << "\n";
	std::cout << "First Order (Sell @ 1020): \n";
	std::cout << "Trader ID: " << mappedBucket[3005]->quoteCollector[0].id << "\n";
	std::cout << "Order ID: " << mappedBucket[3005]->quoteCollector[0].oid << "\n";
	std::cout << "Timestamp: " << mappedBucket[3005]->quoteCollector[0].step << "\n";
	std::cout << "Type: " << mappedBucket[3005]->quoteCollector[0].otype << "\n";
	std::cout << "Quantity: " << mappedBucket[3005]->quoteCollector[0].qty << "\n";
	std::cout << "Side: " << cSide1 << "\n";
	std::cout << "Price: " << mappedBucket[3005]->quoteCollector[0].price << "\n";

	mappedBucket[3005]->processSignal(tob, step1, 0.5, -100, engine, distUreal);
	cSide1 = mappedBucket[3005]->quoteCollector[1].side == Side::BUY ? 'B' : 'S';
	std::cout << "\n\nQuote Collector After: " << mappedBucket[3005]->quoteCollector.size() << "\n";
	std::cout << "Second Order (Buy @ 955): \n";
	std::cout << "Trader ID: " << mappedBucket[3005]->quoteCollector[1].id << "\n";
	std::cout << "Order ID: " << mappedBucket[3005]->quoteCollector[1].oid << "\n";
	std::cout << "Timestamp: " << mappedBucket[3005]->quoteCollector[1].step << "\n";
	std::cout << "Type: " << mappedBucket[3005]->quoteCollector[1].otype << "\n";
	std::cout << "Quantity: " << mappedBucket[3005]->quoteCollector[1].qty << "\n";
	std::cout << "Side: " << cSide1 << "\n";
	std::cout << "Price: " << mappedBucket[3005]->quoteCollector[1].price << "\n";

	mappedBucket[3005]->processSignal(tob, step1, 0.5, -100, engine, distUreal);
	cSide1 = mappedBucket[3005]->quoteCollector[2].side == Side::BUY ? 'B' : 'S';
	std::cout << "\n\nQuote Collector After: " << mappedBucket[3005]->quoteCollector.size() << "\n";
	std::cout << "Third Order (Sell @ 1075): \n";
	std::cout << "Trader ID: " << mappedBucket[3005]->quoteCollector[2].id << "\n";
	std::cout << "Order ID: " << mappedBucket[3005]->quoteCollector[2].oid << "\n";
	std::cout << "Timestamp: " << mappedBucket[3005]->quoteCollector[2].step << "\n";
	std::cout << "Type: " << mappedBucket[3005]->quoteCollector[2].otype << "\n";
	std::cout << "Quantity: " << mappedBucket[3005]->quoteCollector[2].qty << "\n";
	std::cout << "Side: " << cSide1 << "\n";
	std::cout << "Price: " << mappedBucket[3005]->quoteCollector[2].price << "\n";

	mappedBucket[3005]->processSignal(tob, step1, 0.5, -100, engine, distUreal);
	cSide1 = mappedBucket[3005]->quoteCollector[3].side == Side::BUY ? 'B' : 'S';
	std::cout << "\n\nQuote Collector After: " << mappedBucket[3005]->quoteCollector.size() << "\n";
	std::cout << "Fourth Order (Buy @ 960): \n";
	std::cout << "Trader ID: " << mappedBucket[3005]->quoteCollector[3].id << "\n";
	std::cout << "Order ID: " << mappedBucket[3005]->quoteCollector[3].oid << "\n";
	std::cout << "Timestamp: " << mappedBucket[3005]->quoteCollector[3].step << "\n";
	std::cout << "Type: " << mappedBucket[3005]->quoteCollector[3].otype << "\n";
	std::cout << "Quantity: " << mappedBucket[3005]->quoteCollector[3].qty << "\n";
	std::cout << "Side: " << cSide1 << "\n";
	std::cout << "Price: " << mappedBucket[3005]->quoteCollector[3].price << "\n";

	mappedBucket[3005]->processSignal(tob, step1, 0.5, -100, engine, distUreal);
	cSide1 = mappedBucket[3005]->quoteCollector[4].side == Side::BUY ? 'B' : 'S';
	std::cout << "\n\nQuote Collector After: " << mappedBucket[3005]->quoteCollector.size() << "\n";
	std::cout << "Fifth Order (Sell @ 1020): \n";
	std::cout << "Trader ID: " << mappedBucket[3005]->quoteCollector[4].id << "\n";
	std::cout << "Order ID: " << mappedBucket[3005]->quoteCollector[4].oid << "\n";
	std::cout << "Timestamp: " << mappedBucket[3005]->quoteCollector[4].step << "\n";
	std::cout << "Type: " << mappedBucket[3005]->quoteCollector[4].otype << "\n";
	std::cout << "Quantity: " << mappedBucket[3005]->quoteCollector[4].qty << "\n";
	std::cout << "Side: " << cSide1 << "\n";
	std::cout << "Price: " << mappedBucket[3005]->quoteCollector[4].price << "\n";

	std::cout << "\nOrder Book:" << "\n";
	for (auto &x : mappedBucket[3005]->localBook)
		std::cout << "TraderId: " << x.second.id
		<< " Order Id: " << x.second.oid
		<< " Order Type: " << x.second.otype
		<< " Order Price: " << x.second.price
		<< " Order Qty: " << x.second.qty
		<< " Order Side: " << (x.second.side == Side::BUY ? 'B' : 'S')
		<< " Order Step: " << x.second.step << "\n";
	std::cout << std::endl;
}

void BucketTests::testMarketMaker()
{
	engine.seed(39);
	cSide cSide1;
	mappedBucket[7001] = std::make_shared<MarketMaker>(1, 7001, setMaxQ(50), 0.05, 60, 12);

	// Test constructor
	std::cout << "Trader Type: " << mappedBucket[7001]->traderType << "\n";
	std::cout << "Max Quantity: " << mappedBucket[7001]->orderSize << "\n";
	std::cout << "Trader ID: " << mappedBucket[7001]->tId << "\n";
	std::cout << "Delta: " << mappedBucket[7001]->delta << "\n";
	std::cout << "Quote Interval: " << mappedBucket[7001]->quoteRange << "\n";
	std::cout << "Number of Quotes: " << mappedBucket[7001]->numQuotes << "\n";
	std::cout << "Quote Collector Before: " << mappedBucket[7001]->quoteCollector.size() << "\n";

	// Test confirmTrade
	std::cout << "\n\nBefore Trade Confirm:" << "\n";
	std::cout << "Cash Flow Before: " << mappedBucket[7001]->cashFlow << "\n";
	std::cout << "Position Before: " << mappedBucket[7001]->position << "\n";
	TConfirm t1{ 7001, 4, 89, 30, Side::BUY, 962 };
	mappedBucket[7001]->confirmTrade(t1);
	std::cout << "\nAfter Trade Confirm 1:" << "\n";
	std::cout << "Cash Flow After 1: " << mappedBucket[7001]->cashFlow << "\n";
	std::cout << "Position After 1: " << mappedBucket[7001]->position << "\n";
	TConfirm t2{ 7001, 7, 95, 30, Side::SELL, 963 };
	mappedBucket[7001]->confirmTrade(t2);
	std::cout << "\nAfter Trade Confirm 2:" << "\n";
	std::cout << "Cash Flow After 2: " << mappedBucket[7001]->cashFlow << "\n";
	std::cout << "Position After 2: " << mappedBucket[7001]->position << "\n";

	// Test processSignal
	Step step1;
	TopOfBook tob;

	step1 = 27;
	tob = { step1, 995, 1, 1010, 1 };
	mappedBucket[7001]->processSignal(tob, step1, 0.5, -100, engine, distUreal);
	std::cout << "\n\nProcess signal: \n";
	for (auto& x : mappedBucket[7001]->quoteCollector)
	{
		cSide1 = x.side == Side::BUY ? 'B' : 'S';
		std::cout << cSide1 << ":" << x.price << "\n";
	}
	mappedBucket[7001]->quoteCollector.clear();
	std::cout << "Quote Collector After Clear: " << mappedBucket[7001]->quoteCollector.size() << "\n";

	step1 = 35;
	tob = { step1, 995, 1, 1010, 1 };
	mappedBucket[7001]->processSignal(tob, step1, 0.5, -100, engine, distUreal);
	std::cout << "\n\nProcess signal: \n";
	for (auto& x : mappedBucket[7001]->quoteCollector)
	{
		cSide1 = x.side == Side::BUY ? 'B' : 'S';
		std::cout << cSide1 << ":" << x.price << "\n";
	}
	mappedBucket[7001]->quoteCollector.clear();
	std::cout << "Quote Collector After Clear: " << mappedBucket[7001]->quoteCollector.size() << "\n";
	std::cout << std::endl;
}

void BucketTests::testMarketMaker5()
{
	engine.seed(39); 
	cSide cSide1;
	mappedBucket[7005] = std::make_shared<MarketMaker5>(1, 7005, setMaxQ(50), 0.05, 60, 12);

	// Test constructor
	std::cout << "Trader Type: " << mappedBucket[7005]->traderType << "\n";
	std::cout << "Max Quantity: " << mappedBucket[7005]->orderSize << "\n";
	std::cout << "Trader ID: " << mappedBucket[7005]->tId << "\n";
	std::cout << "Delta: " << mappedBucket[7005]->delta << "\n";
	std::cout << "Quote Interval: " << mappedBucket[7005]->quoteRange << "\n";
	std::cout << "Number of Quotes: " << mappedBucket[7005]->numQuotes << "\n";
	std::cout << "Quote Collector Before: " << mappedBucket[7005]->quoteCollector.size() << "\n";

	// Test confirmTrade
	std::cout << "\n\nBefore Trade Confirm:" << "\n";
	std::cout << "Cash Flow Before: " << mappedBucket[7005]->cashFlow << "\n";
	std::cout << "Position Before: " << mappedBucket[7005]->position << "\n";
	TConfirm t1{ 7001, 4, 89, 30, Side::BUY, 962 };
	mappedBucket[7005]->confirmTrade(t1);
	std::cout << "\nAfter Trade Confirm 1:" << "\n";
	std::cout << "Cash Flow After 1: " << mappedBucket[7005]->cashFlow << "\n";
	std::cout << "Position After 1: " << mappedBucket[7005]->position << "\n";
	TConfirm t2{ 7001, 7, 95, 30, Side::SELL, 963 };
	mappedBucket[7005]->confirmTrade(t2);
	std::cout << "\nAfter Trade Confirm 2:" << "\n";
	std::cout << "Cash Flow After 2: " << mappedBucket[7005]->cashFlow << "\n";
	std::cout << "Position After 2: " << mappedBucket[7005]->position << "\n";

	// Test processSignal
	Step step1;
	TopOfBook tob;

	step1 = 27;
	tob = { step1, 995, 1, 1010, 1 };
	mappedBucket[7005]->processSignal(tob, step1, 0.5, -100, engine, distUreal);
	std::cout << "\n\nProcess signal: \n";
	for (auto& x : mappedBucket[7005]->quoteCollector)
	{
		cSide1 = x.side == Side::BUY ? 'B' : 'S';
		std::cout << cSide1 << ":" << x.price << "\n";
	}
	mappedBucket[7005]->quoteCollector.clear();
	std::cout << "Quote Collector After Clear: " << mappedBucket[7005]->quoteCollector.size() << "\n";

	step1 = 35;
	tob = { step1, 995, 1, 1010, 1 };
	mappedBucket[7005]->processSignal(tob, step1, 0.5, -100, engine, distUreal);
	std::cout << "\n\nProcess signal: \n";
	for (auto& x : mappedBucket[7005]->quoteCollector)
	{
		cSide1 = x.side == Side::BUY ? 'B' : 'S';
		std::cout << cSide1 << ":" << x.price << "\n";
	}
	mappedBucket[7005]->quoteCollector.clear();
	std::cout << "Quote Collector After Clear: " << mappedBucket[7005]->quoteCollector.size() << "\n";

	std::cout << std::endl;
}

void BucketTests::testPJ()
{
	engine.seed(44);
	 
	TopOfBook tob;
	cSide cSide1;

	j1 = std::make_unique<PennyJumper>(1, 4000, 1, 1);
	std::cout << "Trader Type: " << j1->traderType << "\n";
	std::cout << "Max Quantity: " << j1->orderSize << "\n";
	std::cout << "Trader ID: " << j1->tId << "\n";
	std::cout << "MPI: " << j1->mpi << "\n";
	std::cout << "Quote Collector Before: " << j1->quoteCollector.size() << "\n";

	// seed == 17 generates first > 0.5 and second < 0.5
	engine.seed(17);

	// Spread > mpi
	std::cout << "\nQuote books should be empty" << "\n";
	std::cout << "Ask Quote Book empty: \n";
	std::cout << "Size: " << j1->askBook.size() << "\n";
	std::cout << "Bid Quote Book empty: \n";
	std::cout << "Size: " << j1->bidBook.size() << "\n";

	// PJ jumps bid and ask by 1
	tob = { 27, 999, 5, 1008, 5 };
	j1->processSignal(tob, 28, 0.5, engine, distUreal);
	j1->processSignal(tob, 29, 0.5, engine, distUreal);
	std::cout << "\nPJ takes the inside" << "\n";
	cSide1 = j1->askBook[0].side == Side::BUY ? 'B' : 'S';
	std::cout << "Ask Quote 1007: \n";
	std::cout << "Trader ID: " << j1->askBook[0].id << "\n";
	std::cout << "Order ID: " << j1->askBook[0].oid << "\n";
	std::cout << "Timestamp: " << j1->askBook[0].step << "\n";
	std::cout << "Type: " << j1->askBook[0].otype << "\n";
	std::cout << "Quantity: " << j1->askBook[0].qty << "\n";
	std::cout << "Side: " << cSide1 << "\n";
	std::cout << "Price: " << j1->askBook[0].price << "\n";
	cSide1 = j1->bidBook[0].side == Side::BUY ? 'B' : 'S';
	std::cout << "Bid Quote 1000: \n";
	std::cout << "Trader ID: " << j1->bidBook[0].id << "\n";
	std::cout << "Order ID: " << j1->bidBook[0].oid << "\n";
	std::cout << "Timestamp: " << j1->bidBook[0].step << "\n";
	std::cout << "Type: " << j1->bidBook[0].otype << "\n";
	std::cout << "Quantity: " << j1->bidBook[0].qty << "\n";
	std::cout << "Side: " << cSide1 << "\n";
	std::cout << "Price: " << j1->bidBook[0].price << "\n";

	// PJ behind the best prices: cancels then jumps bid and ask by 1
	engine.seed(17);
	tob = { 27, 1001, 5, 1006, 5 };
	j1->processSignal(tob, 28, 0.5, engine, distUreal);
	j1->processSignal(tob, 29, 0.5, engine, distUreal);

	std::cout << "\nPJ Cancels Old Quotes" << "\n";
	cSide1 = j1->cancelCollector[0].side == Side::BUY ? 'B' : 'S';
	std::cout << "Cancel Bid Quote 1000: \n";
	std::cout << "Trader ID: " << j1->cancelCollector[0].id << "\n";
	std::cout << "Order ID: " << j1->cancelCollector[0].oid << "\n";
	std::cout << "Timestamp: " << j1->cancelCollector[0].step << "\n";
	std::cout << "Type: " << j1->cancelCollector[0].otype << "\n";
	std::cout << "Quantity: " << j1->cancelCollector[0].qty << "\n";
	std::cout << "Side: " << cSide1 << "\n";
	std::cout << "Price: " << j1->cancelCollector[0].price << "\n";
	cSide1 = j1->cancelCollector[1].side == Side::BUY ? 'B' : 'S';
	std::cout << "Cancel Ask Quote 1007: \n";
	std::cout << "Trader ID: " << j1->cancelCollector[1].id << "\n";
	std::cout << "Order ID: " << j1->cancelCollector[1].oid << "\n";
	std::cout << "Timestamp: " << j1->cancelCollector[1].step << "\n";
	std::cout << "Type: " << j1->cancelCollector[1].otype << "\n";
	std::cout << "Quantity: " << j1->cancelCollector[1].qty << "\n";
	std::cout << "Side: " << cSide1 << "\n";
	std::cout << "Price: " << j1->cancelCollector[1].price << "\n";

	std::cout << "\nPJ takes the inside" << "\n";
	cSide1 = j1->askBook[0].side == Side::BUY ? 'B' : 'S';
	std::cout << "Ask Quote 1005: \n";
	std::cout << "Trader ID: " << j1->askBook[0].id << "\n";
	std::cout << "Order ID: " << j1->askBook[0].oid << "\n";
	std::cout << "Timestamp: " << j1->askBook[0].step << "\n";
	std::cout << "Type: " << j1->askBook[0].otype << "\n";
	std::cout << "Quantity: " << j1->askBook[0].qty << "\n";
	std::cout << "Side: " << cSide1 << "\n";
	std::cout << "Price: " << j1->askBook[0].price << "\n";
	cSide1 = j1->bidBook[0].side == Side::BUY ? 'B' : 'S';
	std::cout << "Bid Quote 1002: \n";
	std::cout << "Trader ID: " << j1->bidBook[0].id << "\n";
	std::cout << "Order ID: " << j1->bidBook[0].oid << "\n";
	std::cout << "Timestamp: " << j1->bidBook[0].step << "\n";
	std::cout << "Type: " << j1->bidBook[0].otype << "\n";
	std::cout << "Quantity: " << j1->bidBook[0].qty << "\n";
	std::cout << "Side: " << cSide1 << "\n";
	std::cout << "Price: " << j1->bidBook[0].price << "\n";
	j1->cancelCollector.clear();

	// PJ alone at the inside: nothing happens
	engine.seed(17);
	tob = { 27, 1002, 1, 1005, 1 };
	j1->processSignal(tob, 28, 0.5, engine, distUreal);
	j1->processSignal(tob, 29, 0.5, engine, distUreal);

	std::cout << "\nPJ cancelCollector is empty" << "\n";
	std::cout << j1->cancelCollector.size();

	std::cout << "\nPJ quotes unchanged" << "\n";
	cSide1 = j1->askBook[0].side == Side::BUY ? 'B' : 'S';
	std::cout << "Ask Quote 1005: \n";
	std::cout << "Trader ID: " << j1->askBook[0].id << "\n";
	std::cout << "Order ID: " << j1->askBook[0].oid << "\n";
	std::cout << "Timestamp: " << j1->askBook[0].step << "\n";
	std::cout << "Type: " << j1->askBook[0].otype << "\n";
	std::cout << "Quantity: " << j1->askBook[0].qty << "\n";
	std::cout << "Side: " << cSide1 << "\n";
	std::cout << "Price: " << j1->askBook[0].price << "\n";
	cSide1 = j1->bidBook[0].side == Side::BUY ? 'B' : 'S';
	std::cout << "Bid Quote 1002: \n";
	std::cout << "Trader ID: " << j1->bidBook[0].id << "\n";
	std::cout << "Order ID: " << j1->bidBook[0].oid << "\n";
	std::cout << "Timestamp: " << j1->bidBook[0].step << "\n";
	std::cout << "Type: " << j1->bidBook[0].otype << "\n";
	std::cout << "Quantity: " << j1->bidBook[0].qty << "\n";
	std::cout << "Side: " << cSide1 << "\n";
	std::cout << "Price: " << j1->bidBook[0].price << "\n";

	// PJ not alone at inside: cancels then jumps bid and ask by 1
	engine.seed(17);
	tob = { 27, 1002, 20, 1005, 20 };
	j1->processSignal(tob, 28, 0.5, engine, distUreal);
	j1->processSignal(tob, 29, 0.5, engine, distUreal);

	std::cout << "\nPJ Cancels Old Quotes" << "\n";
	cSide1 = j1->cancelCollector[0].side == Side::BUY ? 'B' : 'S';
	std::cout << "Cancel Bid Quote 1002: \n";
	std::cout << "Trader ID: " << j1->cancelCollector[0].id << "\n";
	std::cout << "Order ID: " << j1->cancelCollector[0].oid << "\n";
	std::cout << "Timestamp: " << j1->cancelCollector[0].step << "\n";
	std::cout << "Type: " << j1->cancelCollector[0].otype << "\n";
	std::cout << "Quantity: " << j1->cancelCollector[0].qty << "\n";
	std::cout << "Side: " << cSide1 << "\n";
	std::cout << "Price: " << j1->cancelCollector[0].price << "\n";
	cSide1 = j1->cancelCollector[1].side == Side::BUY ? 'B' : 'S';
	std::cout << "Cancel Ask Quote 1005: \n";
	std::cout << "Trader ID: " << j1->cancelCollector[1].id << "\n";
	std::cout << "Order ID: " << j1->cancelCollector[1].oid << "\n";
	std::cout << "Timestamp: " << j1->cancelCollector[1].step << "\n";
	std::cout << "Type: " << j1->cancelCollector[1].otype << "\n";
	std::cout << "Quantity: " << j1->cancelCollector[1].qty << "\n";
	std::cout << "Side: " << cSide1 << "\n";
	std::cout << "Price: " << j1->cancelCollector[1].price << "\n";

	std::cout << "\nPJ takes the inside" << "\n";
	cSide1 = j1->askBook[0].side == Side::BUY ? 'B' : 'S';
	std::cout << "Ask Quote 1004: \n";
	std::cout << "Trader ID: " << j1->askBook[0].id << "\n";
	std::cout << "Order ID: " << j1->askBook[0].oid << "\n";
	std::cout << "Timestamp: " << j1->askBook[0].step << "\n";
	std::cout << "Type: " << j1->askBook[0].otype << "\n";
	std::cout << "Quantity: " << j1->askBook[0].qty << "\n";
	std::cout << "Side: " << cSide1 << "\n";
	std::cout << "Price: " << j1->askBook[0].price << "\n";
	cSide1 = j1->bidBook[0].side == Side::BUY ? 'B' : 'S';
	std::cout << "Bid Quote 1003: \n";
	std::cout << "Trader ID: " << j1->bidBook[0].id << "\n";
	std::cout << "Order ID: " << j1->bidBook[0].oid << "\n";
	std::cout << "Timestamp: " << j1->bidBook[0].step << "\n";
	std::cout << "Type: " << j1->bidBook[0].otype << "\n";
	std::cout << "Quantity: " << j1->bidBook[0].qty << "\n";
	std::cout << "Side: " << cSide1 << "\n";
	std::cout << "Price: " << j1->bidBook[0].price << "\n";
	j1->cancelCollector.clear();

	// Spread at MPI, PJ alone at inside: nothing happens
	engine.seed(17);
	tob = { 27, 1003, 1, 1004, 1 };
	j1->processSignal(tob, 28, 0.5, engine, distUreal);
	j1->processSignal(tob, 29, 0.5, engine, distUreal);

	std::cout << "\nPJ cancelCollector is empty" << "\n";
	std::cout << j1->cancelCollector.size();

	std::cout << "\nPJ at the inside; spread == 1" << "\n";
	cSide1 = j1->askBook[0].side == Side::BUY ? 'B' : 'S';
	std::cout << "Ask Quote 1004: \n";
	std::cout << "Trader ID: " << j1->askBook[0].id << "\n";
	std::cout << "Order ID: " << j1->askBook[0].oid << "\n";
	std::cout << "Timestamp: " << j1->askBook[0].step << "\n";
	std::cout << "Type: " << j1->askBook[0].otype << "\n";
	std::cout << "Quantity: " << j1->askBook[0].qty << "\n";
	std::cout << "Side: " << cSide1 << "\n";
	std::cout << "Price: " << j1->askBook[0].price << "\n";
	cSide1 = j1->bidBook[0].side == Side::BUY ? 'B' : 'S';
	std::cout << "Bid Quote 1003: \n";
	std::cout << "Trader ID: " << j1->bidBook[0].id << "\n";
	std::cout << "Order ID: " << j1->bidBook[0].oid << "\n";
	std::cout << "Timestamp: " << j1->bidBook[0].step << "\n";
	std::cout << "Type: " << j1->bidBook[0].otype << "\n";
	std::cout << "Quantity: " << j1->bidBook[0].qty << "\n";
	std::cout << "Side: " << cSide1 << "\n";
	std::cout << "Price: " << j1->bidBook[0].price << "\n";

	// Spread at MPI, PJ not at inside: PJ cancels
	engine.seed(17);
	j2 = std::make_unique<PennyJumper>(1, 4000, 1, 1);
	tob = { 27, 1000, 10, 1010, 10 };
	j2->processSignal(tob, 28, 0.5, engine, distUreal);
	j2->processSignal(tob, 29, 0.5, engine, distUreal);

	std::cout << "\nPJ spread == 8" << "\n";
	cSide1 = j2->askBook[0].side == Side::BUY ? 'B' : 'S';
	std::cout << "Ask Quote 1009: \n";
	std::cout << "Trader ID: " << j2->askBook[0].id << "\n";
	std::cout << "Order ID: " << j2->askBook[0].oid << "\n";
	std::cout << "Timestamp: " << j2->askBook[0].step << "\n";
	std::cout << "Type: " << j2->askBook[0].otype << "\n";
	std::cout << "Quantity: " << j2->askBook[0].qty << "\n";
	std::cout << "Side: " << cSide1 << "\n";
	std::cout << "Price: " << j2->askBook[0].price << "\n";
	cSide1 = j2->bidBook[0].side == Side::BUY ? 'B' : 'S';
	std::cout << "Bid Quote 1001: \n";
	std::cout << "Trader ID: " << j2->bidBook[0].id << "\n";
	std::cout << "Order ID: " << j2->bidBook[0].oid << "\n";
	std::cout << "Timestamp: " << j2->bidBook[0].step << "\n";
	std::cout << "Type: " << j2->bidBook[0].otype << "\n";
	std::cout << "Quantity: " << j2->bidBook[0].qty << "\n";
	std::cout << "Side: " << cSide1 << "\n";
	std::cout << "Price: " << j2->bidBook[0].price << "\n";

	engine.seed(17);
	tob = { 27, 1005, 10, 1006, 10 };
	j2->processSignal(tob, 28, 0.5, engine, distUreal);
	j2->processSignal(tob, 29, 0.5, engine, distUreal);

	std::cout << "\nQuote books should be empty" << "\n";
	std::cout << "Ask Quote Book empty: \n";
	std::cout << "Size: " << j2->askBook.size() << "\n";
	std::cout << "Bid Quote Book empty: \n";
	std::cout << "Size: " << j2->bidBook.size() << "\n";
	std::cout << std::endl;
}

void BucketTests::testShuffle()
{
	mappedBucket[1] = std::make_shared<ZITrader>(7, 1, setMaxQ(50), 1);
	mappedBucket[1001] = std::make_shared<Taker>(11, 1001, setMaxQ(50), 1);
	mappedBucket[2001] = std::make_shared<Informed>(2001, 1, Side::SELL, 1, 100, engine, distUint);
	mappedBucket[3001] = std::make_shared<Provider>(17, 3001, setMaxQ(50), 0.85, 1);
	mappedBucket[3005] = std::make_shared<Provider5>(22, 3005, setMaxQ(50), 0.05, 5);
	mappedBucket[7001] = std::make_shared<MarketMaker>(1, 7001, setMaxQ(50), 0.05, 60, 12);
	mappedBucket[7005] = std::make_shared<MarketMaker5>(1, 7005, setMaxQ(50), 0.05, 60, 12);

	std::vector<traderId> temp{ 1, 1001, 2001, 3001, 3005, 7001, 7005 };


	std::cout << "Order should be ZI, Taker, Informed, P1, P5, MM1, MM5" << "\n";
	for (auto &x : temp)
		std::cout << "Trader Type: " << mappedBucket[x]->traderType << "; Trader ID: " << mappedBucket[x]->tId << "\n";

	shuffle(temp.begin(), temp.end(), engine);

	std::cout << "Shuffled\n";
	for (auto &x : temp)
		std::cout << "Trader Type: " << mappedBucket[x]->traderType << "; Trader ID: " << mappedBucket[x]->tId << "\n";

	mappedBucket[2] = std::make_shared<ZITrader>(7, 2, setMaxQ(50), 1);
	mappedBucket[1002] = std::make_shared<Taker>(11, 1002, setMaxQ(50), 1);
	mappedBucket[2002] = std::make_shared<Informed>(2002, 1, Side::SELL, 1, 100, engine, distUint);
	mappedBucket[3002] = std::make_shared<Provider>(17, 3002, setMaxQ(50), 0.85, 1);
	mappedBucket[3006] = std::make_shared<Provider5>(22, 3006, setMaxQ(50), 0.05, 5);
	mappedBucket[7002] = std::make_shared<MarketMaker>(1, 7002, setMaxQ(50), 0.05, 60, 12);
	mappedBucket[7006] = std::make_shared<MarketMaker5>(1, 7006, setMaxQ(50), 0.05, 60, 12);

	temp.push_back(2);
	temp.push_back(1002);
	temp.push_back(2002);
	temp.push_back(3002);
	temp.push_back(3006);
	temp.push_back(7002);
	temp.push_back(7006);

	shuffle(temp.begin(), temp.end(), engine);

	std::cout << "Shuffled\n";
	for (auto &x : temp)
		std::cout << "Trader Type: " << mappedBucket[x]->traderType << "; Trader ID: " << mappedBucket[x]->tId << "\n";

	std::cout << std::endl;
}