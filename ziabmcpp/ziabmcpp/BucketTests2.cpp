// BucketTests2.cpp
// BucketTests2 class

#include "stdafx.h"

#include <iostream>

#include "BucketTests2.h"


BucketTests2::BucketTests2(std::vector<int> &dVec, std::uniform_int_distribution<> &dUint, std::mt19937 &eng) :
	defaultVec(dVec), distUint(dUint), engine(eng)
{
	std::uniform_real_distribution<> distUreal(0, 1);
}

int BucketTests2::setMaxQ(int maxq)
{
	std::vector<int> actualVec(0);
	std::copy_if(defaultVec.begin(), defaultVec.end(), std::back_inserter(actualVec), [&maxq](int i) { return i <= maxq; });
	std::uniform_int_distribution<int> distUintV(0, actualVec.size() - 1);
	return actualVec[distUintV(engine)];
}

void BucketTests2::testZITrader()
{
	Step step1;
	Side side1;
	Prc price1;
	cSide cSide1;

	allTraders.emplace_back(std::make_shared<ZITrader>(7, 1, setMaxQ(50), 1));

	std::cout << "Trader Type: " << allTraders[0]->traderType << "\n";
	std::cout << "Arrival Interval: " << allTraders[0]->arrInt << "\n";
	std::cout << "Max Quantity: " << allTraders[0]->orderSize << "\n";
	std::cout << "Trader ID: " << allTraders[0]->tId << "\n";
	std::cout << "MPI: " << allTraders[0]->mpi << "\n";
	std::cout << "Quote Collector Before: " << allTraders[0]->quoteCollector.size() << "\n";


	step1 = 23;
	side1 = Side::SELL;
	price1 = 1099;

	Order q1 = allTraders[0]->makeAddQuote(step1, side1, price1);
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

	Order q2 = allTraders[0]->makeAddQuote(step1, side1, price1);
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

void BucketTests2::testTaker()
{
	allTraders.emplace_back(std::make_shared<Taker>(11, 1001, setMaxQ(50), 1));

	std::cout << "Trader Type: " << allTraders[0]->traderType << "\n";
	std::cout << "Arrival Interval: " << allTraders[0]->arrInt << "\n";
	std::cout << "Max Quantity: " << allTraders[0]->orderSize << "\n";
	std::cout << "Trader ID: " << allTraders[0]->tId << "\n";
	std::cout << "MPI: " << allTraders[0]->mpi << "\n";
	std::cout << "Quote Collector Before: " << allTraders[0]->quoteCollector.size() << "\n";

	Step step1 = 27;
	double qTake = 0.5;

	allTraders[0]->processSignal(step1, qTake, engine, distUreal);
	cSide cSide3 = allTraders[0]->quoteCollector[0].side == Side::BUY ? 'B' : 'S';
	std::cout << "\nQuote Collector After: " << allTraders[0]->quoteCollector.size() << "\n";
	std::cout << "First Order: \n";
	std::cout << "Trader ID: " << allTraders[0]->quoteCollector[0].id << "\n";
	std::cout << "Order ID: " << allTraders[0]->quoteCollector[0].oid << "\n";
	std::cout << "Timestamp: " << allTraders[0]->quoteCollector[0].step << "\n";
	std::cout << "Type: " << allTraders[0]->quoteCollector[0].otype << "\n";
	std::cout << "Quantity: " << allTraders[0]->quoteCollector[0].qty << "\n";
	std::cout << "Side: " << cSide3 << "\n";
	std::cout << "Price: " << allTraders[0]->quoteCollector[0].price << "\n";
	std::cout << std::endl;
}

void BucketTests2::testInformed()
{
	allTraders.emplace_back(std::make_shared<Informed>(2001, 1, Side::SELL, 1, 100, engine, distUint));

	cSide cSide1;
	Step step1;
	Qty maxQ;
	unsigned runL, numT, numChoices;

	std::cout << "Trader Type: " << allTraders[0]->traderType << "\n";
	std::cout << "Max Quantity: " << allTraders[0]->orderSize << "\n";
	std::cout << "Trader ID: " << allTraders[0]->tId << "\n";

	int counter = 0;
	std::cout << "\n\nArrival steps: \n";
	for (auto &x : allTraders[0]->steps)
		std::cout << "Choice " << ++counter << ": " << x << "\n";

	std::cout << "\n\nQuote Collector Before: " << allTraders[0]->quoteCollector.size() << "\n";

	step1 = allTraders[0]->arrInt;

	std::cout << "First step from arrival interval = " << allTraders[0]->arrInt << "\n";

	allTraders[0]->processSignal(step1);
	cSide1 = allTraders[0]->quoteCollector[0].side == Side::BUY ? 'B' : 'S';

	std::cout << "Second step from arrival interval = " << allTraders[0]->arrInt << "\n";

	std::cout << "Quote Collector After: " << allTraders[0]->quoteCollector.size() << "\n";
	std::cout << "First Order: \n";
	std::cout << "Trader ID: " << allTraders[0]->quoteCollector[0].id << "\n";
	std::cout << "Order ID: " << allTraders[0]->quoteCollector[0].oid << "\n";
	std::cout << "Timestamp: " << allTraders[0]->quoteCollector[0].step << "\n";
	std::cout << "Type: " << allTraders[0]->quoteCollector[0].otype << "\n";
	std::cout << "Quantity: " << allTraders[0]->quoteCollector[0].qty << "\n";
	std::cout << "Side: " << cSide1 << "\n";
	std::cout << "Price: " << allTraders[0]->quoteCollector[0].price << "\n";

	maxQ = 5;
	runL = 3;
	numT = 100;
	numChoices = (numT / (runL*maxQ)) + 1;
	allTraders.emplace_back(std::make_shared<Informed>(2002, 1, Side::SELL, 1, 100, engine, distUint));

	std::cout << "\n\nTrader Type: " << allTraders[1]->traderType << "\n";
	std::cout << "Max Quantity: " << allTraders[1]->orderSize << "\n";
	std::cout << "Trader ID: " << allTraders[1]->tId << "\n";
	std::cout << "Quote Collector Before: " << allTraders[1]->quoteCollector.size() << "\n";

	counter = 0;
	std::cout << "\n\nArrival steps: \n";
	for (auto &x : allTraders[1]->steps)
		std::cout << "Choice " << ++counter << ": " << x << "\n";

	step1 = allTraders[1]->arrInt;

	std::cout << "First step from arrival interval = " << allTraders[1]->arrInt << "\n";

	allTraders[1]->processSignal(step1);
	cSide1 = allTraders[1]->quoteCollector[0].side == Side::BUY ? 'B' : 'S';

	std::cout << "Second step from arrival interval = " << allTraders[1]->arrInt << "\n";

	std::cout << "\n\nQuote Collector After: " << allTraders[1]->quoteCollector.size() << "\n";
	std::cout << "First Order: \n";
	std::cout << "Trader ID: " << allTraders[1]->quoteCollector[0].id << "\n";
	std::cout << "Order ID: " << allTraders[1]->quoteCollector[0].oid << "\n";
	std::cout << "Timestamp: " << allTraders[1]->quoteCollector[0].step << "\n";
	std::cout << "Type: " << allTraders[1]->quoteCollector[0].otype << "\n";
	std::cout << "Quantity: " << allTraders[1]->quoteCollector[0].qty << "\n";
	std::cout << "Side: " << cSide1 << "\n";
	std::cout << "Price: " << allTraders[1]->quoteCollector[0].price << "\n";
	std::cout << std::endl;
}

void BucketTests2::testProvider()
{
	allTraders.emplace_back(std::make_shared<Provider>(17, 3001, setMaxQ(50), 0.85, 1));

	cSide cSide1;

	// Test constructor
	std::cout << "Trader Type: " << allTraders[0]->traderType << "\n";
	std::cout << "Max Quantity: " << allTraders[0]->orderSize << "\n";
	std::cout << "Trader ID: " << allTraders[0]->tId << "\n";
	std::cout << "Delta: " << allTraders[0]->delta << "\n";
	std::cout << "MPI: " << allTraders[0]->mpi << "\n";
	std::cout << "Quote Collector Before: " << allTraders[0]->quoteCollector.size() << "\n";

	// Test makeCancelQuote
	Order o3{ 3001, 2, 3, 'A', 100, Side::SELL, 1005 };
	Order c1 = allTraders[0]->makeCancelQuote(o3, 132);
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

	allTraders.emplace_back(std::make_shared<Provider>(17, 3002, setMaxQ(50), 0.85, 1));

	step1 = 27;
	tob = { step1, 999, 250, 1008, 300 };

	allTraders[1]->processSignal(tob, step1, 0.5, -100, engine, distUreal);
	cSide1 = allTraders[1]->quoteCollector[0].side == Side::BUY ? 'B' : 'S';
	std::cout << "\n\nQuote Collector After: " << allTraders[1]->quoteCollector.size() << "\n";
	std::cout << "First Order (Sell @ 1019): \n";
	std::cout << "Trader ID: " << allTraders[1]->quoteCollector[0].id << "\n";
	std::cout << "Order ID: " << allTraders[1]->quoteCollector[0].oid << "\n";
	std::cout << "Timestamp: " << allTraders[1]->quoteCollector[0].step << "\n";
	std::cout << "Type: " << allTraders[1]->quoteCollector[0].otype << "\n";
	std::cout << "Quantity: " << allTraders[1]->quoteCollector[0].qty << "\n";
	std::cout << "Side: " << cSide1 << "\n";
	std::cout << "Price: " << allTraders[1]->quoteCollector[0].price << "\n";

	allTraders[1]->processSignal(tob, step1, 0.5, -100, engine, distUreal);
	cSide1 = allTraders[1]->quoteCollector[1].side == Side::BUY ? 'B' : 'S';
	std::cout << "\n\nQuote Collector After: " << allTraders[1]->quoteCollector.size() << "\n";
	std::cout << "Second Order (Buy @ 957): \n";
	std::cout << "Trader ID: " << allTraders[1]->quoteCollector[1].id << "\n";
	std::cout << "Order ID: " << allTraders[1]->quoteCollector[1].oid << "\n";
	std::cout << "Timestamp: " << allTraders[1]->quoteCollector[1].step << "\n";
	std::cout << "Type: " << allTraders[1]->quoteCollector[1].otype << "\n";
	std::cout << "Quantity: " << allTraders[1]->quoteCollector[1].qty << "\n";
	std::cout << "Side: " << cSide1 << "\n";
	std::cout << "Price: " << allTraders[1]->quoteCollector[1].price << "\n";

	allTraders[1]->processSignal(tob, step1, 0.5, -100, engine, distUreal);
	cSide1 = allTraders[1]->quoteCollector[2].side == Side::BUY ? 'B' : 'S';
	std::cout << "\n\nQuote Collector After: " << allTraders[1]->quoteCollector.size() << "\n";
	std::cout << "Third Order (Sell @ 1076): \n";
	std::cout << "Trader ID: " << allTraders[1]->quoteCollector[2].id << "\n";
	std::cout << "Order ID: " << allTraders[1]->quoteCollector[2].oid << "\n";
	std::cout << "Timestamp: " << allTraders[1]->quoteCollector[2].step << "\n";
	std::cout << "Type: " << allTraders[1]->quoteCollector[2].otype << "\n";
	std::cout << "Quantity: " << allTraders[1]->quoteCollector[2].qty << "\n";
	std::cout << "Side: " << cSide1 << "\n";
	std::cout << "Price: " << allTraders[1]->quoteCollector[2].price << "\n";

	allTraders[1]->processSignal(tob, step1, 0.5, -100, engine, distUreal);
	cSide1 = allTraders[1]->quoteCollector[3].side == Side::BUY ? 'B' : 'S';
	std::cout << "\n\nQuote Collector After: " << allTraders[1]->quoteCollector.size() << "\n";
	std::cout << "Fourth Order (Buy @ 962): \n";
	std::cout << "Trader ID: " << allTraders[1]->quoteCollector[3].id << "\n";
	std::cout << "Order ID: " << allTraders[1]->quoteCollector[3].oid << "\n";
	std::cout << "Timestamp: " << allTraders[1]->quoteCollector[3].step << "\n";
	std::cout << "Type: " << allTraders[1]->quoteCollector[3].otype << "\n";
	std::cout << "Quantity: " << allTraders[1]->quoteCollector[3].qty << "\n";
	std::cout << "Side: " << cSide1 << "\n";
	std::cout << "Price: " << allTraders[1]->quoteCollector[3].price << "\n";

	allTraders[1]->processSignal(tob, step1, 0.5, -100, engine, distUreal);
	cSide1 = allTraders[1]->quoteCollector[4].side == Side::BUY ? 'B' : 'S';
	std::cout << "\n\nQuote Collector After: " << allTraders[1]->quoteCollector.size() << "\n";
	std::cout << "Fifth Order (Sell @ 1020): \n";
	std::cout << "Trader ID: " << allTraders[1]->quoteCollector[4].id << "\n";
	std::cout << "Order ID: " << allTraders[1]->quoteCollector[4].oid << "\n";
	std::cout << "Timestamp: " << allTraders[1]->quoteCollector[4].step << "\n";
	std::cout << "Type: " << allTraders[1]->quoteCollector[4].otype << "\n";
	std::cout << "Quantity: " << allTraders[1]->quoteCollector[4].qty << "\n";
	std::cout << "Side: " << cSide1 << "\n";
	std::cout << "Price: " << allTraders[1]->quoteCollector[4].price << "\n";

	std::cout << "\nOrder Book:" << "\n";
	for (auto &x : allTraders[1]->localBook)
		std::cout << "TraderId: " << x.second.id
		<< " Order Id: " << x.second.oid
		<< " Order Type: " << x.second.otype
		<< " Order Price: " << x.second.price
		<< " Order Qty: " << x.second.qty
		<< " Order Side: " << (x.second.side == Side::BUY ? 'B' : 'S')
		<< " Order Step: " << x.second.step << "\n";

	// Test bulkCancel with delta = 0.85
	allTraders[1]->bulkCancel(45, engine, distUreal);
	std::cout << "\nCancel Collector should have two orders: 3&4" << "\n";
	for (auto &x : allTraders[1]->cancelCollector)
		std::cout << "TraderId: " << x.id
		<< " Order Id: " << x.oid
		<< " Order Type: " << x.otype
		<< " Order Price: " << x.price
		<< " Order Qty: " << x.qty
		<< " Order Side: " << (x.side == Side::BUY ? 'B' : 'S')
		<< " Order Step: " << x.step << "\n";

	// Test confirm Cancel by removing #5 from localBook
	allTraders[1]->confirmCancel(5);
	std::cout << "\nOrder Book should be missing #5:" << "\n";
	for (auto &x : allTraders[1]->localBook)
		std::cout << "TraderId: " << x.second.id
		<< " Order Id: " << x.second.oid
		<< " Order Type: " << x.second.otype
		<< " Order Price: " << x.second.price
		<< " Order Qty: " << x.second.qty
		<< " Order Side: " << (x.second.side == Side::BUY ? 'B' : 'S')
		<< " Order Step: " << x.second.step << "\n";

	//Test confirmTrade by removing 30 shares, then the remaining 20
	TConfirm t1{ 3001, 4, 89, 30, Side::BUY, 962 };
	allTraders[1]->confirmTrade(t1);
	std::cout << "\nOrder Book #4 should have quantity = 20:" << "\n";
	for (auto &x : allTraders[1]->localBook)
		std::cout << "TraderId: " << x.second.id
		<< " Order Id: " << x.second.oid
		<< " Order Type: " << x.second.otype
		<< " Order Price: " << x.second.price
		<< " Order Qty: " << x.second.qty
		<< " Order Side: " << (x.second.side == Side::BUY ? 'B' : 'S')
		<< " Order Step: " << x.second.step << "\n";

	TConfirm t2{ 3001, 4, 92, 20, Side::BUY, 962 };
	allTraders[1]->confirmTrade(t2);
	std::cout << "\nOrder Book should be missing #4:" << "\n";
	for (auto &x : allTraders[1]->localBook)
		std::cout << "TraderId: " << x.second.id
		<< " Order Id: " << x.second.oid
		<< " Order Type: " << x.second.otype
		<< " Order Price: " << x.second.price
		<< " Order Qty: " << x.second.qty
		<< " Order Side: " << (x.second.side == Side::BUY ? 'B' : 'S')
		<< " Order Step: " << x.second.step << "\n";
	std::cout << std::endl;
}

void BucketTests2::testProvider5()
{
	engine.seed(39);
	cSide cSide1;

	allTraders.emplace_back(std::make_shared<Provider5>(22, 3005, setMaxQ(50), 0.05, 5));

	// Test constructor
	std::cout << "Trader Type: " << allTraders[0]->traderType << "\n";
	std::cout << "Max Quantity: " << allTraders[0]->orderSize << "\n";
	std::cout << "Trader ID: " << allTraders[0]->tId << "\n";
	std::cout << "Delta: " << allTraders[0]->delta << "\n";
	std::cout << "Quote Collector Before: " << allTraders[0]->quoteCollector.size() << "\n";

	// Test processSignal and chooseP (seed = 39)
	Step step1;
	TopOfBook tob;

	step1 = 27;
	tob = { step1, 995, 250, 1010, 300 };
	//	simpleTest(engine, distUreal);

	allTraders[0]->processSignal(tob, step1, 0.5, -100, engine, distUreal);
	cSide1 = allTraders[0]->quoteCollector[0].side == Side::BUY ? 'B' : 'S';
	std::cout << "\n\nQuote Collector After: " << allTraders[0]->quoteCollector.size() << "\n";
	std::cout << "First Order (Sell @ 1020): \n";
	std::cout << "Trader ID: " << allTraders[0]->quoteCollector[0].id << "\n";
	std::cout << "Order ID: " << allTraders[0]->quoteCollector[0].oid << "\n";
	std::cout << "Timestamp: " << allTraders[0]->quoteCollector[0].step << "\n";
	std::cout << "Type: " << allTraders[0]->quoteCollector[0].otype << "\n";
	std::cout << "Quantity: " << allTraders[0]->quoteCollector[0].qty << "\n";
	std::cout << "Side: " << cSide1 << "\n";
	std::cout << "Price: " << allTraders[0]->quoteCollector[0].price << "\n";

	allTraders[0]->processSignal(tob, step1, 0.5, -100, engine, distUreal);
	cSide1 = allTraders[0]->quoteCollector[1].side == Side::BUY ? 'B' : 'S';
	std::cout << "\n\nQuote Collector After: " << allTraders[0]->quoteCollector.size() << "\n";
	std::cout << "Second Order (Buy @ 955): \n";
	std::cout << "Trader ID: " << allTraders[0]->quoteCollector[1].id << "\n";
	std::cout << "Order ID: " << allTraders[0]->quoteCollector[1].oid << "\n";
	std::cout << "Timestamp: " << allTraders[0]->quoteCollector[1].step << "\n";
	std::cout << "Type: " << allTraders[0]->quoteCollector[1].otype << "\n";
	std::cout << "Quantity: " << allTraders[0]->quoteCollector[1].qty << "\n";
	std::cout << "Side: " << cSide1 << "\n";
	std::cout << "Price: " << allTraders[0]->quoteCollector[1].price << "\n";

	allTraders[0]->processSignal(tob, step1, 0.5, -100, engine, distUreal);
	cSide1 = allTraders[0]->quoteCollector[2].side == Side::BUY ? 'B' : 'S';
	std::cout << "\n\nQuote Collector After: " << allTraders[0]->quoteCollector.size() << "\n";
	std::cout << "Third Order (Sell @ 1075): \n";
	std::cout << "Trader ID: " << allTraders[0]->quoteCollector[2].id << "\n";
	std::cout << "Order ID: " << allTraders[0]->quoteCollector[2].oid << "\n";
	std::cout << "Timestamp: " << allTraders[0]->quoteCollector[2].step << "\n";
	std::cout << "Type: " << allTraders[0]->quoteCollector[2].otype << "\n";
	std::cout << "Quantity: " << allTraders[0]->quoteCollector[2].qty << "\n";
	std::cout << "Side: " << cSide1 << "\n";
	std::cout << "Price: " << allTraders[0]->quoteCollector[2].price << "\n";

	allTraders[0]->processSignal(tob, step1, 0.5, -100, engine, distUreal);
	cSide1 = allTraders[0]->quoteCollector[3].side == Side::BUY ? 'B' : 'S';
	std::cout << "\n\nQuote Collector After: " << allTraders[0]->quoteCollector.size() << "\n";
	std::cout << "Fourth Order (Buy @ 960): \n";
	std::cout << "Trader ID: " << allTraders[0]->quoteCollector[3].id << "\n";
	std::cout << "Order ID: " << allTraders[0]->quoteCollector[3].oid << "\n";
	std::cout << "Timestamp: " << allTraders[0]->quoteCollector[3].step << "\n";
	std::cout << "Type: " << allTraders[0]->quoteCollector[3].otype << "\n";
	std::cout << "Quantity: " << allTraders[0]->quoteCollector[3].qty << "\n";
	std::cout << "Side: " << cSide1 << "\n";
	std::cout << "Price: " << allTraders[0]->quoteCollector[3].price << "\n";

	allTraders[0]->processSignal(tob, step1, 0.5, -100, engine, distUreal);
	cSide1 = allTraders[0]->quoteCollector[4].side == Side::BUY ? 'B' : 'S';
	std::cout << "\n\nQuote Collector After: " << allTraders[0]->quoteCollector.size() << "\n";
	std::cout << "Fifth Order (Sell @ 1020): \n";
	std::cout << "Trader ID: " << allTraders[0]->quoteCollector[4].id << "\n";
	std::cout << "Order ID: " << allTraders[0]->quoteCollector[4].oid << "\n";
	std::cout << "Timestamp: " << allTraders[0]->quoteCollector[4].step << "\n";
	std::cout << "Type: " << allTraders[0]->quoteCollector[4].otype << "\n";
	std::cout << "Quantity: " << allTraders[0]->quoteCollector[4].qty << "\n";
	std::cout << "Side: " << cSide1 << "\n";
	std::cout << "Price: " << allTraders[0]->quoteCollector[4].price << "\n";

	std::cout << "\nOrder Book:" << "\n";
	for (auto &x : allTraders[0]->localBook)
		std::cout << "TraderId: " << x.second.id
		<< " Order Id: " << x.second.oid
		<< " Order Type: " << x.second.otype
		<< " Order Price: " << x.second.price
		<< " Order Qty: " << x.second.qty
		<< " Order Side: " << (x.second.side == Side::BUY ? 'B' : 'S')
		<< " Order Step: " << x.second.step << "\n";
	std::cout << std::endl;
}

void BucketTests2::testMarketMaker()
{
	engine.seed(39);
	cSide cSide1;
	allTraders.emplace_back(std::make_shared<MarketMaker>(1, 7001, setMaxQ(50), 0.05, 60, 12));

	// Test constructor
	std::cout << "Trader Type: " << allTraders[0]->traderType << "\n";
	std::cout << "Max Quantity: " << allTraders[0]->orderSize << "\n";
	std::cout << "Trader ID: " << allTraders[0]->tId << "\n";
	std::cout << "Delta: " << allTraders[0]->delta << "\n";
	std::cout << "Quote Interval: " << allTraders[0]->quoteRange << "\n";
	std::cout << "Number of Quotes: " << allTraders[0]->numQuotes << "\n";
	std::cout << "Quote Collector Before: " << allTraders[0]->quoteCollector.size() << "\n";

	// Test confirmTrade
	std::cout << "\n\nBefore Trade Confirm:" << "\n";
	std::cout << "Cash Flow Before: " << allTraders[0]->cashFlow << "\n";
	std::cout << "Position Before: " << allTraders[0]->position << "\n";
	TConfirm t1{ 7001, 4, 89, 30, Side::BUY, 962 };
	allTraders[0]->confirmTrade(t1);
	std::cout << "\nAfter Trade Confirm 1:" << "\n";
	std::cout << "Cash Flow After 1: " << allTraders[0]->cashFlow << "\n";
	std::cout << "Position After 1: " << allTraders[0]->position << "\n";
	TConfirm t2{ 7001, 7, 95, 30, Side::SELL, 963 };
	allTraders[0]->confirmTrade(t2);
	std::cout << "\nAfter Trade Confirm 2:" << "\n";
	std::cout << "Cash Flow After 2: " << allTraders[0]->cashFlow << "\n";
	std::cout << "Position After 2: " << allTraders[0]->position << "\n";

	// Test processSignal
	Step step1;
	TopOfBook tob;

	step1 = 27;
	tob = { step1, 995, 1, 1010, 1 };
	allTraders[0]->processSignal(tob, step1, 0.5, -100, engine, distUreal);
	std::cout << "\n\nProcess signal: \n";
	for (auto& x : allTraders[0]->quoteCollector)
	{
		cSide1 = x.side == Side::BUY ? 'B' : 'S';
		std::cout << cSide1 << ":" << x.price << "\n";
	}
	allTraders[0]->quoteCollector.clear();
	std::cout << "Quote Collector After Clear: " << allTraders[0]->quoteCollector.size() << "\n";

	step1 = 35;
	tob = { step1, 995, 1, 1010, 1 };
	allTraders[0]->processSignal(tob, step1, 0.5, -100, engine, distUreal);
	std::cout << "\n\nProcess signal: \n";
	for (auto& x : allTraders[0]->quoteCollector)
	{
		cSide1 = x.side == Side::BUY ? 'B' : 'S';
		std::cout << cSide1 << ":" << x.price << "\n";
	}
	allTraders[0]->quoteCollector.clear();
	std::cout << "Quote Collector After Clear: " << allTraders[0]->quoteCollector.size() << "\n";
	std::cout << std::endl;
}

void BucketTests2::testMarketMaker5()
{
	engine.seed(39);
	cSide cSide1;
	allTraders.emplace_back(std::make_shared<MarketMaker5>(1, 7005, setMaxQ(50), 0.05, 60, 12));

	// Test constructor
	std::cout << "Trader Type: " << allTraders[0]->traderType << "\n";
	std::cout << "Max Quantity: " << allTraders[0]->orderSize << "\n";
	std::cout << "Trader ID: " << allTraders[0]->tId << "\n";
	std::cout << "Delta: " << allTraders[0]->delta << "\n";
	std::cout << "Quote Interval: " << allTraders[0]->quoteRange << "\n";
	std::cout << "Number of Quotes: " << allTraders[0]->numQuotes << "\n";
	std::cout << "Quote Collector Before: " << allTraders[0]->quoteCollector.size() << "\n";

	// Test confirmTrade
	std::cout << "\n\nBefore Trade Confirm:" << "\n";
	std::cout << "Cash Flow Before: " << allTraders[0]->cashFlow << "\n";
	std::cout << "Position Before: " << allTraders[0]->position << "\n";
	TConfirm t1{ 7001, 4, 89, 30, Side::BUY, 962 };
	allTraders[0]->confirmTrade(t1);
	std::cout << "\nAfter Trade Confirm 1:" << "\n";
	std::cout << "Cash Flow After 1: " << allTraders[0]->cashFlow << "\n";
	std::cout << "Position After 1: " << allTraders[0]->position << "\n";
	TConfirm t2{ 7001, 7, 95, 30, Side::SELL, 963 };
	allTraders[0]->confirmTrade(t2);
	std::cout << "\nAfter Trade Confirm 2:" << "\n";
	std::cout << "Cash Flow After 2: " << allTraders[0]->cashFlow << "\n";
	std::cout << "Position After 2: " << allTraders[0]->position << "\n";

	// Test processSignal
	Step step1;
	TopOfBook tob;

	step1 = 27;
	tob = { step1, 995, 1, 1010, 1 };
	allTraders[0]->processSignal(tob, step1, 0.5, -100, engine, distUreal);
	std::cout << "\n\nProcess signal: \n";
	for (auto& x : allTraders[0]->quoteCollector)
	{
		cSide1 = x.side == Side::BUY ? 'B' : 'S';
		std::cout << cSide1 << ":" << x.price << "\n";
	}
	allTraders[0]->quoteCollector.clear();
	std::cout << "Quote Collector After Clear: " << allTraders[0]->quoteCollector.size() << "\n";

	step1 = 35;
	tob = { step1, 995, 1, 1010, 1 };
	allTraders[0]->processSignal(tob, step1, 0.5, -100, engine, distUreal);
	std::cout << "\n\nProcess signal: \n";
	for (auto& x : allTraders[0]->quoteCollector)
	{
		cSide1 = x.side == Side::BUY ? 'B' : 'S';
		std::cout << cSide1 << ":" << x.price << "\n";
	}
	allTraders[0]->quoteCollector.clear();
	std::cout << "Quote Collector After Clear: " << allTraders[0]->quoteCollector.size() << "\n";

	std::cout << std::endl;
}

void BucketTests2::testPJ()
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

void BucketTests2::testShuffle()
{
	allTraders.emplace_back(std::make_shared<ZITrader>(7, 1, setMaxQ(50), 1));
	allTraders.emplace_back(std::make_shared<Taker>(11, 1001, setMaxQ(50), 1));
	allTraders.emplace_back(std::make_shared<Informed>(2001, 1, Side::SELL, 1, 100, engine, distUint));
	allTraders.emplace_back(std::make_shared<Provider>(17, 3001, setMaxQ(50), 0.85, 1));
	allTraders.emplace_back(std::make_shared<Provider5>(22, 3005, setMaxQ(50), 0.05, 5));
	allTraders.emplace_back(std::make_shared<MarketMaker>(1, 7001, setMaxQ(50), 0.05, 60, 12));
	allTraders.emplace_back(std::make_shared<MarketMaker5>(1, 7005, setMaxQ(50), 0.05, 60, 12));

	std::cout << "Order should be ZI, Taker, Informed, P1, P5, MM1, MM5" << "\n";
	for (auto &x : allTraders)
		std::cout << "Trader Type: " << x->traderType << "; Trader ID: " << x->tId << "\n";

	shuffle(allTraders.begin(), allTraders.end(), engine);

	std::cout << "Shuffled\n";
	for (auto &x : allTraders)
		std::cout << "Trader Type: " << x->traderType << "; Trader ID: " << x->tId << "\n";

	allTraders.emplace_back(std::make_shared<ZITrader>(7, 2, setMaxQ(50), 1));
	allTraders.emplace_back(std::make_shared<Taker>(11, 1002, setMaxQ(50), 1));
	allTraders.emplace_back(std::make_shared<Informed>(2002, 1, Side::SELL, 1, 100, engine, distUint));
	allTraders.emplace_back(std::make_shared<Provider>(17, 3002, setMaxQ(50), 0.85, 1));
	allTraders.emplace_back(std::make_shared<Provider5>(22, 3006, setMaxQ(50), 0.05, 5));
	allTraders.emplace_back(std::make_shared<MarketMaker>(1, 7002, setMaxQ(50), 0.05, 60, 12));
	allTraders.emplace_back(std::make_shared<MarketMaker5>(1, 7006, setMaxQ(50), 0.05, 60, 12));

	shuffle(allTraders.begin(), allTraders.end(), engine);

	std::cout << "Shuffled\n";
	for (auto &x : allTraders)
		std::cout << "Trader Type: " << x->traderType << "; Trader ID: " << x->tId << "\n";

	std::cout << std::endl;
}