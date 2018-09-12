// TraderTests.cpp
// TraderTests class

#include "stdafx.h"

#include <iostream>

#include "TraderTests.h"

TraderTests::TraderTests(std::vector<int> &dVec, std::uniform_int_distribution<> &dUint, std::mt19937 &eng) : 
	defaultVec(dVec), distUint(dUint), engine(eng)
{	
	std::uniform_real_distribution<> distUreal(0, 1);
}

int TraderTests::setMaxQ(int maxq)
{
	std::vector<int> actualVec(0);
	std::copy_if(defaultVec.begin(), defaultVec.end(), std::back_inserter(actualVec), [&maxq](int i) { return i <= maxq; });
	std::uniform_int_distribution<int> distUintV(0, actualVec.size() - 1);
	return actualVec[distUintV(engine)];
}

void TraderTests::testProvider()
{
	cSide cSide1;
	Provider p1(17, 1000, setMaxQ(50), 0.85, 5);

	// Test constructor
	std::cout << "Trader Type: " << p1.traderType << "\n";
	std::cout << "Max Quantity: " << p1.orderSize << "\n";
	std::cout << "Trader ID: " << p1.tId << "\n";
	std::cout << "Delta: " << p1.delta << "\n";
	std::cout << "MPI: " << p1.mpi << "\n";
	std::cout << "Local Book Before: " << p1.localBook.size() << "\n";

	// Test makeCancelQuote
	Order o0{ 1000, 2, 3, 'A', 100, Side::SELL, 1005 };
	Order c1 = p1.makeCancelQuote(o0, 132);
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
	Step step1;
	TopOfBook tob;

	step1 = 27;
	tob = { step1, 999, 250, 1008, 300 };
	std::cout << "\n\nTest processSignal: \n";
	Order o1 = p1.processSignal(tob, step1, 0.5, -100, engine, distUreal);
	cSide1 = o1.side == Side::BUY ? 'B' : 'S';
	std::cout << "First Order (Sell @ 1028): \n";
	std::cout << "Trader ID: " << o1.id << "\n";
	std::cout << "Order ID: " << o1.oid << "\n";
	std::cout << "Timestamp: " << o1.step << "\n";
	std::cout << "Type: " << o1.otype << "\n";
	std::cout << "Quantity: " << o1.qty << "\n";
	std::cout << "Side: " << cSide1 << "\n";
	std::cout << "Price: " << o1.price << "\n";

	Order o2 = p1.processSignal(tob, step1, 0.5, -100, engine, distUreal);
	cSide1 = o2.side == Side::BUY ? 'B' : 'S';
	std::cout << "Second Order (Buy @ 957): \n";
	std::cout << "Trader ID: " << o2.id << "\n";
	std::cout << "Order ID: " << o2.oid << "\n";
	std::cout << "Timestamp: " << o2.step << "\n";
	std::cout << "Type: " << o2.otype << "\n";
	std::cout << "Quantity: " << o2.qty << "\n";
	std::cout << "Side: " << cSide1 << "\n";
	std::cout << "Price: " << o2.price << "\n";

	Order o3 = p1.processSignal(tob, step1, 0.5, -100, engine, distUreal);
	cSide1 = o3.side == Side::BUY ? 'B' : 'S';
	std::cout << "Third Order (Sell @ 1085): \n";
	std::cout << "Trader ID: " << o3.id << "\n";
	std::cout << "Order ID: " << o3.oid << "\n";
	std::cout << "Timestamp: " << o3.step << "\n";
	std::cout << "Type: " << o3.otype << "\n";
	std::cout << "Quantity: " << o3.qty << "\n";
	std::cout << "Side: " << cSide1 << "\n";
	std::cout << "Price: " << o3.price << "\n";

	Order o4 = p1.processSignal(tob, step1, 0.5, -100, engine, distUreal);
	cSide1 = o4.side == Side::BUY ? 'B' : 'S';
	std::cout << "Fourth Order (Buy @ 962): \n";
	std::cout << "Trader ID: " << o4.id << "\n";
	std::cout << "Order ID: " << o4.oid << "\n";
	std::cout << "Timestamp: " << o4.step << "\n";
	std::cout << "Type: " << o4.otype << "\n";
	std::cout << "Quantity: " << o4.qty << "\n";
	std::cout << "Side: " << cSide1 << "\n";
	std::cout << "Price: " << o4.price << "\n";

	Order o5 = p1.processSignal(tob, step1, 0.5, -100, engine, distUreal);
	cSide1 = o5.side == Side::BUY ? 'B' : 'S';
	std::cout << "Fifth Order (Sell @ 1029): \n";
	std::cout << "Trader ID: " << o5.id << "\n";
	std::cout << "Order ID: " << o5.oid << "\n";
	std::cout << "Timestamp: " << o5.step << "\n";
	std::cout << "Type: " << o5.otype << "\n";
	std::cout << "Quantity: " << o5.qty << "\n";
	std::cout << "Side: " << cSide1 << "\n";
	std::cout << "Price: " << o5.price << "\n";

	std::cout << "\nOrder Book:" << "\n";
	for (auto &x : p1.localBook)
		std::cout << "TraderId: " << x.second.id
		<< " Order Id: " << x.second.oid
		<< " Order Type: " << x.second.otype
		<< " Order Price: " << x.second.price
		<< " Order Qty: " << x.second.qty
		<< " Order Side: " << (x.second.side == Side::BUY ? 'B' : 'S')
		<< " Order Step: " << x.second.step << "\n";

	// Test bulkCancel with delta = 0.85
	p1.bulkCancel(45, engine, distUreal);
	std::cout << "\nCancel Collector should have two orders: 3&4" << "\n";
	for (auto &x : p1.cancelCollector)
		std::cout << "TraderId: " << x.id
		<< " Order Id: " << x.oid
		<< " Order Type: " << x.otype
		<< " Order Price: " << x.price
		<< " Order Qty: " << x.qty
		<< " Order Side: " << (x.side == Side::BUY ? 'B' : 'S')
		<< " Order Step: " << x.step << "\n";
	std::cout << "\nOrder Book should be missing 3&4:" << "\n";
	for (auto &x : p1.localBook)
		std::cout << "TraderId: " << x.second.id
		<< " Order Id: " << x.second.oid
		<< " Order Type: " << x.second.otype
		<< " Order Price: " << x.second.price
		<< " Order Qty: " << x.second.qty
		<< " Order Side: " << (x.second.side == Side::BUY ? 'B' : 'S')
		<< " Order Step: " << x.second.step << "\n";

	//Test confirmTrade by removing 30 shares, then the remaining 20
	TConfirm t1{ 1000, 1, 89, 30, Side::SELL, 1028 };
	p1.confirmTrade(t1);
	std::cout << "\nOrder Book #1 should have quantity = 20:" << "\n";
	for (auto &x : p1.localBook)
		std::cout << "TraderId: " << x.second.id
		<< " Order Id: " << x.second.oid
		<< " Order Type: " << x.second.otype
		<< " Order Price: " << x.second.price
		<< " Order Qty: " << x.second.qty
		<< " Order Side: " << (x.second.side == Side::BUY ? 'B' : 'S')
		<< " Order Step: " << x.second.step << "\n";

	TConfirm t2{ 1000, 1, 92, 20, Side::SELL, 1028 };
	p1.confirmTrade(t2);
	std::cout << "\nOrder Book should be missing #1:" << "\n";
	for (auto &x : p1.localBook)
		std::cout << "TraderId: " << x.second.id
		<< " Order Id: " << x.second.oid
		<< " Order Type: " << x.second.otype
		<< " Order Price: " << x.second.price
		<< " Order Qty: " << x.second.qty
		<< " Order Side: " << (x.second.side == Side::BUY ? 'B' : 'S')
		<< " Order Step: " << x.second.step << "\n";

	std::cout << std::endl;
}

void TraderTests::testProvider5()
{
	cSide cSide1;
	Provider5 p1(17, 1000, setMaxQ(50), 0.85, 5);

	// Test constructor
	std::cout << "Trader Type: " << p1.traderType << "\n";
	std::cout << "Max Quantity: " << p1.orderSize << "\n";
	std::cout << "Trader ID: " << p1.tId << "\n";
	std::cout << "Delta: " << p1.delta << "\n";
	std::cout << "MPI: " << p1.mpi << "\n";
	std::cout << "Local Book Before: " << p1.localBook.size() << "\n";

	// Test makeCancelQuote
	Order o0{ 1000, 2, 3, 'A', 100, Side::SELL, 1005 };
	Order c1 = p1.makeCancelQuote(o0, 132);
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
	Step step1;
	TopOfBook tob;

	step1 = 27;
	tob = { step1, 995, 250, 1010, 300 };
	std::cout << "\n\nTest processSignal: \n";
	Order o1 = p1.processSignal(tob, step1, 0.5, -100, engine, distUreal);
	cSide1 = o1.side == Side::BUY ? 'B' : 'S';
	std::cout << "First Order (Sell @ 1035): \n";
	std::cout << "Trader ID: " << o1.id << "\n";
	std::cout << "Order ID: " << o1.oid << "\n";
	std::cout << "Timestamp: " << o1.step << "\n";
	std::cout << "Type: " << o1.otype << "\n";
	std::cout << "Quantity: " << o1.qty << "\n";
	std::cout << "Side: " << cSide1 << "\n";
	std::cout << "Price: " << o1.price << "\n";

	Order o2 = p1.processSignal(tob, step1, 0.5, -100, engine, distUreal);
	cSide1 = o2.side == Side::BUY ? 'B' : 'S';
	std::cout << "Second Order (Buy @ 955): \n";
	std::cout << "Trader ID: " << o2.id << "\n";
	std::cout << "Order ID: " << o2.oid << "\n";
	std::cout << "Timestamp: " << o2.step << "\n";
	std::cout << "Type: " << o2.otype << "\n";
	std::cout << "Quantity: " << o2.qty << "\n";
	std::cout << "Side: " << cSide1 << "\n";
	std::cout << "Price: " << o2.price << "\n";

	Order o3 = p1.processSignal(tob, step1, 0.5, -100, engine, distUreal);
	cSide1 = o3.side == Side::BUY ? 'B' : 'S';
	std::cout << "Third Order (Sell @ 1090): \n";
	std::cout << "Trader ID: " << o3.id << "\n";
	std::cout << "Order ID: " << o3.oid << "\n";
	std::cout << "Timestamp: " << o3.step << "\n";
	std::cout << "Type: " << o3.otype << "\n";
	std::cout << "Quantity: " << o3.qty << "\n";
	std::cout << "Side: " << cSide1 << "\n";
	std::cout << "Price: " << o3.price << "\n";

	Order o4 = p1.processSignal(tob, step1, 0.5, -100, engine, distUreal);
	cSide1 = o4.side == Side::BUY ? 'B' : 'S';
	std::cout << "Fourth Order (Buy @ 960): \n";
	std::cout << "Trader ID: " << o4.id << "\n";
	std::cout << "Order ID: " << o4.oid << "\n";
	std::cout << "Timestamp: " << o4.step << "\n";
	std::cout << "Type: " << o4.otype << "\n";
	std::cout << "Quantity: " << o4.qty << "\n";
	std::cout << "Side: " << cSide1 << "\n";
	std::cout << "Price: " << o4.price << "\n";

	Order o5 = p1.processSignal(tob, step1, 0.5, -100, engine, distUreal);
	cSide1 = o5.side == Side::BUY ? 'B' : 'S';
	std::cout << "Fifth Order (Sell @ 1035): \n";
	std::cout << "Trader ID: " << o5.id << "\n";
	std::cout << "Order ID: " << o5.oid << "\n";
	std::cout << "Timestamp: " << o5.step << "\n";
	std::cout << "Type: " << o5.otype << "\n";
	std::cout << "Quantity: " << o5.qty << "\n";
	std::cout << "Side: " << cSide1 << "\n";
	std::cout << "Price: " << o5.price << "\n";

	std::cout << "\nOrder Book:" << "\n";
	for (auto &x : p1.localBook)
		std::cout << "TraderId: " << x.second.id
		<< " Order Id: " << x.second.oid
		<< " Order Type: " << x.second.otype
		<< " Order Price: " << x.second.price
		<< " Order Qty: " << x.second.qty
		<< " Order Side: " << (x.second.side == Side::BUY ? 'B' : 'S')
		<< " Order Step: " << x.second.step << "\n";

	// Test bulkCancel with delta = 0.85
	p1.bulkCancel(45, engine, distUreal);
	std::cout << "\nCancel Collector should have two orders: 3&4" << "\n";
	for (auto &x : p1.cancelCollector)
		std::cout << "TraderId: " << x.id
		<< " Order Id: " << x.oid
		<< " Order Type: " << x.otype
		<< " Order Price: " << x.price
		<< " Order Qty: " << x.qty
		<< " Order Side: " << (x.side == Side::BUY ? 'B' : 'S')
		<< " Order Step: " << x.step << "\n";
	std::cout << "\nOrder Book should be missing 3&4:" << "\n";
	for (auto &x : p1.localBook)
		std::cout << "TraderId: " << x.second.id
		<< " Order Id: " << x.second.oid
		<< " Order Type: " << x.second.otype
		<< " Order Price: " << x.second.price
		<< " Order Qty: " << x.second.qty
		<< " Order Side: " << (x.second.side == Side::BUY ? 'B' : 'S')
		<< " Order Step: " << x.second.step << "\n";

	//Test confirmTrade by removing 30 shares, then the remaining 20
	TConfirm t1{ 1000, 1, 89, 30, Side::SELL, 1028 };
	p1.confirmTrade(t1);
	std::cout << "\nOrder Book #1 should have quantity = 20:" << "\n";
	for (auto &x : p1.localBook)
		std::cout << "TraderId: " << x.second.id
		<< " Order Id: " << x.second.oid
		<< " Order Type: " << x.second.otype
		<< " Order Price: " << x.second.price
		<< " Order Qty: " << x.second.qty
		<< " Order Side: " << (x.second.side == Side::BUY ? 'B' : 'S')
		<< " Order Step: " << x.second.step << "\n";

	TConfirm t2{ 1000, 1, 92, 20, Side::SELL, 1028 };
	p1.confirmTrade(t2);
	std::cout << "\nOrder Book should be missing #1:" << "\n";
	for (auto &x : p1.localBook)
		std::cout << "TraderId: " << x.second.id
		<< " Order Id: " << x.second.oid
		<< " Order Type: " << x.second.otype
		<< " Order Price: " << x.second.price
		<< " Order Qty: " << x.second.qty
		<< " Order Side: " << (x.second.side == Side::BUY ? 'B' : 'S')
		<< " Order Step: " << x.second.step << "\n";

	std::cout << std::endl;
}

void TraderTests::testMarketMaker()
{
	cSide cSide1;
	MarketMaker m1(1, 3001, setMaxQ(50), 0.05, 60, 12);

	// Test constructor
	std::cout << "Trader Type: " << m1.traderType << "\n";
	std::cout << "Max Quantity: " << m1.orderSize << "\n";
	std::cout << "Trader ID: " << m1.tId << "\n";
	std::cout << "Delta: " << m1.delta << "\n";
	std::cout << "Quote Interval: " << m1.quoteRange << "\n";
	std::cout << "Number of Quotes: " << m1.numQuotes << "\n";
	std::cout << "Quote Collector Before: " << m1.quoteCollector.size() << "\n";

	// Test confirmTrade
	std::cout << "\n\nBefore Trade Confirm:" << "\n";
	std::cout << "Cash Flow Before: " << m1.cashFlow << "\n";
	std::cout << "Position Before: " << m1.position << "\n";
	TConfirm t1{ 7001, 4, 89, 30, Side::BUY, 962 };
	m1.confirmTrade(t1);
	std::cout << "\nAfter Trade Confirm 1:" << "\n";
	std::cout << "Cash Flow After 1: " << m1.cashFlow << "\n";
	std::cout << "Position After 1: " << m1.position << "\n";
	TConfirm t2{ 7001, 7, 95, 30, Side::SELL, 963 };
	m1.confirmTrade(t2);
	std::cout << "\nAfter Trade Confirm 2:" << "\n";
	std::cout << "Cash Flow After 2: " << m1.cashFlow << "\n";
	std::cout << "Position After 2: " << m1.position << "\n";

	// Test processSignal
	Step step1;
	TopOfBook tob;

	step1 = 27;
	tob = { step1, 995, 1, 1010, 1 };
	m1.localBook.clear();
	m1.processSignal(tob, step1, 0.5, -100, engine, distUreal);
	std::cout << "\n\nProcess signal: \n";
	std::cout << "Quote Collector: \n";
	for (auto& x : m1.quoteCollector)
	{
		cSide1 = x.side == Side::BUY ? 'B' : 'S';
		std::cout << cSide1 << ":" << x.price << "\n";
	}
	m1.quoteCollector.clear();
	std::cout << "Quote Collector After Clear: " << m1.quoteCollector.size() << "\n";
	std::cout << "Local Book: \n";
	for (auto& x : m1.localBook)
	{
		cSide1 = x.second.side == Side::BUY ? 'B' : 'S';
		std::cout << cSide1 << " : " << x.first << " : " << x.second.oid << "\n";
	}

	step1 = 35;
	tob = { step1, 995, 1, 1010, 1 };
	m1.processSignal(tob, step1, 0.5, -100, engine, distUreal);
	std::cout << "\n\nProcess signal: \n";
	std::cout << "Quote Collector: \n";
	for (auto& x : m1.quoteCollector)
	{
		cSide1 = x.side == Side::BUY ? 'B' : 'S';
		std::cout << cSide1 << ":" << x.price << "\n";
	}
	m1.quoteCollector.clear();
	std::cout << "Quote Collector After Clear: " << m1.quoteCollector.size() << "\n";
	std::cout << "Local Book: \n";
	for (auto& x : m1.localBook)
	{
		cSide1 = x.second.side == Side::BUY ? 'B' : 'S';
		std::cout << cSide1 << " : " << x.first << " : " << x.second.oid << "\n";
	}

	std::cout << std::endl;
}

void TraderTests::testMarketMaker5()
{
	cSide cSide1;
	MarketMaker5 m1(1, 3001, setMaxQ(50), 0.05, 60, 12);

	// Test constructor
	std::cout << "Trader Type: " << m1.traderType << "\n";
	std::cout << "Max Quantity: " << m1.orderSize << "\n";
	std::cout << "Trader ID: " << m1.tId << "\n";
	std::cout << "Delta: " << m1.delta << "\n";
	std::cout << "Quote Interval: " << m1.quoteRange << "\n";
	std::cout << "Number of Quotes: " << m1.numQuotes << "\n";
	std::cout << "Quote Collector Before: " << m1.quoteCollector.size() << "\n";

	// Test confirmTrade
	std::cout << "\n\nBefore Trade Confirm:" << "\n";
	std::cout << "Cash Flow Before: " << m1.cashFlow << "\n";
	std::cout << "Position Before: " << m1.position << "\n";
	TConfirm t1{ 7001, 4, 89, 30, Side::BUY, 962 };
	m1.confirmTrade(t1);
	std::cout << "\nAfter Trade Confirm 1:" << "\n";
	std::cout << "Cash Flow After 1: " << m1.cashFlow << "\n";
	std::cout << "Position After 1: " << m1.position << "\n";
	TConfirm t2{ 7001, 7, 95, 30, Side::SELL, 963 };
	m1.confirmTrade(t2);
	std::cout << "\nAfter Trade Confirm 2:" << "\n";
	std::cout << "Cash Flow After 2: " << m1.cashFlow << "\n";
	std::cout << "Position After 2: " << m1.position << "\n";

	// Test processSignal
	Step step1;
	TopOfBook tob;

	step1 = 27;
	tob = { step1, 995, 1, 1010, 1 };
	m1.localBook.clear();
	m1.processSignal(tob, step1, 0.5, -100, engine, distUreal);
	std::cout << "\n\nProcess signal: \n";
	std::cout << "Quote Collector: \n";
	for (auto& x : m1.quoteCollector)
	{
		cSide1 = x.side == Side::BUY ? 'B' : 'S';
		std::cout << cSide1 << ":" << x.price << "\n";
	}
	m1.quoteCollector.clear();
	std::cout << "Quote Collector After Clear: " << m1.quoteCollector.size() << "\n";
	std::cout << "Local Book: \n";
	for (auto& x : m1.localBook)
	{
		cSide1 = x.second.side == Side::BUY ? 'B' : 'S';
		std::cout << cSide1 << " : " << x.first << " : " << x.second.oid << "\n";
	}

	step1 = 35;
	tob = { step1, 995, 1, 1010, 1 };
	m1.processSignal(tob, step1, 0.5, -100, engine, distUreal);
	std::cout << "\n\nProcess signal: \n";
	std::cout << "Quote Collector: \n";
	for (auto& x : m1.quoteCollector)
	{
		cSide1 = x.side == Side::BUY ? 'B' : 'S';
		std::cout << cSide1 << ":" << x.price << "\n";
	}
	m1.quoteCollector.clear();
	std::cout << "Quote Collector After Clear: " << m1.quoteCollector.size() << "\n";
	std::cout << "Local Book: \n";
	for (auto& x : m1.localBook)
	{
		cSide1 = x.second.side == Side::BUY ? 'B' : 'S';
		std::cout << cSide1 << " : " << x.first << " : " << x.second.oid << "\n";
	}

	std::cout << std::endl;
}

/*
void TraderTests::testZITrader()
{
	ZITrader z1(7, 1, setMaxQ(50), 1);
	std::cout << "Trader Type: " << z1.traderType << "\n";
	std::cout << "Arrival Interval: " << z1.arrInt << "\n";
	std::cout << "Max Quantity: " << z1.orderSize << "\n";
	std::cout << "Trader ID: " << z1.tId << "\n";
	std::cout << "MPI: " << z1.mpi << "\n";
	std::cout << "Quote Collector Before: " << z1.quoteCollector.size() << "\n";
	std::cout << std::endl;

	Step step1 = 23;
	Side side1 = Side::SELL;
	Prc price1 = 1099;

	Order q1 = z1.makeAddQuote(step1, side1, price1);
	cSide cSide1 = q1.side == Side::BUY ? 'B' : 'S';
	std::cout << "First Order: \n";
	std::cout << "Trader ID: " << q1.id << "\n";
	std::cout << "Order ID: " << q1.oid << "\n";
	std::cout << "Timestamp: " << q1.step << "\n";
	std::cout << "Type: " << q1.otype << "\n";
	std::cout << "Quantity: " << q1.qty << "\n";
	std::cout << "Side: " << cSide1 << "\n";
	std::cout << "Price: " << q1.price << "\n";
	std::cout << std::endl;

	Step step2 = 27;
	Side side2 = Side::BUY;
	Prc price2 = 888;

	Order q2 = z1.makeAddQuote(step2, side2, price2);
	cSide cSide2 = q2.side == Side::BUY ? 'B' : 'S';
	std::cout << "Second Order: \n";
	std::cout << "Trader ID: " << q2.id << "\n";
	std::cout << "Order ID: " << q2.oid << "\n";
	std::cout << "Timestamp: " << q2.step << "\n";
	std::cout << "Type: " << q2.otype << "\n";
	std::cout << "Quantity: " << q2.qty << "\n";
	std::cout << "Side: " << cSide2 << "\n";
	std::cout << "Price: " << q2.price << "\n";
	std::cout << std::endl;

	ZITrader z2(11, 2, setMaxQ(50), 1);
	std::cout << "Trader Type: " << z2.traderType << "\n";
	std::cout << "Arrival Interval: " << z2.arrInt << "\n";
	std::cout << "Max Quantity: " << z2.orderSize << "\n";
	std::cout << "Trader ID: " << z2.tId << "\n";
	std::cout << "MPI: " << z2.mpi << "\n";
	std::cout << "Quote Collector Before: " << z2.quoteCollector.size() << "\n";
	std::cout << std::endl;
}

void TraderTests::testTaker()
{
	Taker t1(9, 1, setMaxQ(50), 1);
	std::cout << "Trader Type: " << t1.traderType << "\n";
	std::cout << "Arrival Interval: " << t1.arrInt << "\n";
	std::cout << "Max Quantity: " << t1.orderSize << "\n";
	std::cout << "Trader ID: " << t1.tId << "\n";
	std::cout << "MPI: " << t1.mpi << "\n";
	std::cout << "Quote Collector Before: " << t1.quoteCollector.size() << "\n";
	std::cout << std::endl;

	Step step1 = 27;
	double qTake = 0.5;

	t1.processSignal(step1, qTake, engine, distUreal);
	cSide cSide3 = t1.quoteCollector[0].side == Side::BUY ? 'B' : 'S';
	std::cout << "Quote Collector After: " << t1.quoteCollector.size() << "\n";
	std::cout << "First Order: \n";
	std::cout << "Trader ID: " << t1.quoteCollector[0].id << "\n";
	std::cout << "Order ID: " << t1.quoteCollector[0].oid << "\n";
	std::cout << "Timestamp: " << t1.quoteCollector[0].step << "\n";
	std::cout << "Type: " << t1.quoteCollector[0].otype << "\n";
	std::cout << "Quantity: " << t1.quoteCollector[0].qty << "\n";
	std::cout << "Side: " << cSide3 << "\n";
	std::cout << "Price: " << t1.quoteCollector[0].price << "\n";
	std::cout << std::endl;

	Taker t2(11, 2, setMaxQ(50), 1);
	Taker t3(17, 27, setMaxQ(50), 1);
	std::cout << "Trader Type: " << t2.traderType << "\n";
	std::cout << "Arrival Interval: " << t2.arrInt << "\n";
	std::cout << "Max Quantity: " << t2.orderSize << "\n";
	std::cout << "Trader ID: " << t2.tId << "\n";
	std::cout << "MPI: " << t2.mpi << "\n";
	std::cout << "Quote Collector Before: " << t2.quoteCollector.size() << "\n";
	std::cout << std::endl;
}

void TraderTests::testInformed()
{
	cSide cSide1;
	Step step1;
	Qty maxQ = 1;
	unsigned runL, numT, numChoices;
	runL = 1;
	numT = 100;
	numChoices = (numT / (runL*maxQ)) + 1;
	Informed i1(1, maxQ, Side::BUY, runL, numChoices, engine, distUint);

	std::cout << "Trader Type: " << i1.traderType << "\n";
	std::cout << "Max Quantity: " << i1.orderSize << "\n";
	std::cout << "Trader ID: " << i1.tId << "\n";

	int counter = 0;
	std::cout << "\n\nArrival steps: \n";
	for (auto &x : i1.steps)
		std::cout << "Choice " << ++counter << ": " << x << "\n";

	std::cout << "\n\nQuote Collector Before: " << i1.quoteCollector.size() << "\n";

	step1 = i1.arrInt;

	std::cout << "First step from arrival interval = " << i1.arrInt << "\n";

	i1.processSignal(step1);
	cSide1 = i1.quoteCollector[0].side == Side::BUY ? 'B' : 'S';

	std::cout << "Second step from arrival interval = " << i1.arrInt << "\n";

	std::cout << "Quote Collector After: " << i1.quoteCollector.size() << "\n";
	std::cout << "First Order: \n";
	std::cout << "Trader ID: " << i1.quoteCollector[0].id << "\n";
	std::cout << "Order ID: " << i1.quoteCollector[0].oid << "\n";
	std::cout << "Timestamp: " << i1.quoteCollector[0].step << "\n";
	std::cout << "Type: " << i1.quoteCollector[0].otype << "\n";
	std::cout << "Quantity: " << i1.quoteCollector[0].qty << "\n";
	std::cout << "Side: " << cSide1 << "\n";
	std::cout << "Price: " << i1.quoteCollector[0].price << "\n";

	maxQ = 5;
	runL = 3;
	numT = 100;
	numChoices = (numT / (runL*maxQ)) + 1;
	Informed i2(2, maxQ, Side::SELL, runL, numChoices, engine, distUint);

	std::cout << "\n\nTrader Type: " << i2.traderType << "\n";
	std::cout << "Max Quantity: " << i2.orderSize << "\n";
	std::cout << "Trader ID: " << i2.tId << "\n";
	std::cout << "Quote Collector Before: " << i2.quoteCollector.size() << "\n";

	counter = 0;
	std::cout << "\n\nArrival steps: \n";
	for (auto &x : i2.steps)
		std::cout << "Choice " << ++counter << ": " << x << "\n";

	step1 = i2.arrInt;

	std::cout << "First step from arrival interval = " << i2.arrInt << "\n";

	i2.processSignal(step1);
	cSide1 = i2.quoteCollector[0].side == Side::BUY ? 'B' : 'S';

	std::cout << "Second step from arrival interval = " << i2.arrInt << "\n";

	std::cout << "\n\nQuote Collector After: " << i2.quoteCollector.size() << "\n";
	std::cout << "First Order: \n";
	std::cout << "Trader ID: " << i2.quoteCollector[0].id << "\n";
	std::cout << "Order ID: " << i2.quoteCollector[0].oid << "\n";
	std::cout << "Timestamp: " << i2.quoteCollector[0].step << "\n";
	std::cout << "Type: " << i2.quoteCollector[0].otype << "\n";
	std::cout << "Quantity: " << i2.quoteCollector[0].qty << "\n";
	std::cout << "Side: " << cSide1 << "\n";
	std::cout << "Price: " << i2.quoteCollector[0].price << "\n";

	std::cout << std::endl;
}



void TraderTests::testMarketMaker5()
{
	cSide cSide1;
	MarketMaker5 m1(1, 7001, setMaxQ(50), 0.05, 60, 12);

	// Test constructor
	std::cout << "Trader Type: " << m1.traderType << "\n";
	std::cout << "Max Quantity: " << m1.orderSize << "\n";
	std::cout << "Trader ID: " << m1.tId << "\n";
	std::cout << "Delta: " << m1.delta << "\n";
	std::cout << "Quote Interval: " << m1.quoteRange << "\n";
	std::cout << "Number of Quotes: " << m1.numQuotes << "\n";
	std::cout << "Quote Collector Before: " << m1.quoteCollector.size() << "\n";

	// Test confirmTrade
	std::cout << "\n\nBefore Trade Confirm:" << "\n";
	std::cout << "Cash Flow Before: " << m1.cashFlow << "\n";
	std::cout << "Position Before: " << m1.position << "\n";
	TConfirm t1{ 7001, 4, 89, 30, Side::BUY, 962 };
	m1.confirmTrade(t1);
	std::cout << "\nAfter Trade Confirm 1:" << "\n";
	std::cout << "Cash Flow After 1: " << m1.cashFlow << "\n";
	std::cout << "Position After 1: " << m1.position << "\n";
	TConfirm t2{ 7001, 7, 95, 30, Side::SELL, 963 };
	m1.confirmTrade(t2);
	std::cout << "\nAfter Trade Confirm 2:" << "\n";
	std::cout << "Cash Flow After 2: " << m1.cashFlow << "\n";
	std::cout << "Position After 2: " << m1.position << "\n";

	// Test processSignal
	Step step1;
	TopOfBook tob;

	step1 = 27;
	tob = { step1, 995, 1, 1010, 1 };
	m1.processSignal(tob, step1, 0.5, -100, engine, distUreal);
	std::cout << "\n\nProcess signal: \n";
	for (auto& x : m1.quoteCollector)
	{
		cSide1 = x.side == Side::BUY ? 'B' : 'S';
		std::cout << cSide1 << ":" << x.price << "\n";
	}
	m1.quoteCollector.clear();
	std::cout << "Quote Collector After Clear: " << m1.quoteCollector.size() << "\n";

	step1 = 35;
	tob = { step1, 995, 1, 1010, 1 };
	m1.processSignal(tob, step1, 0.5, -100, engine, distUreal);
	std::cout << "\n\nProcess signal: \n";
	for (auto& x : m1.quoteCollector)
	{
		cSide1 = x.side == Side::BUY ? 'B' : 'S';
		std::cout << cSide1 << ":" << x.price << "\n";
	}
	m1.quoteCollector.clear();
	std::cout << "Quote Collector After Clear: " << m1.quoteCollector.size() << "\n";

	std::cout << std::endl;
}

void TraderTests::testPJ()
{
	engine.seed(44);

	TopOfBook tob;
	cSide cSide1;
	PennyJumper j1(1, 1, setMaxQ(50), 1);
	std::cout << "Trader Type: " << j1.traderType << "\n";
	std::cout << "Max Quantity: " << j1.orderSize << "\n";
	std::cout << "Trader ID: " << j1.tId << "\n";
	std::cout << "MPI: " << j1.mpi << "\n";
	std::cout << "Quote Collector Before: " << j1.quoteCollector.size() << "\n";

	// seed == 17 generates first > 0.5 and second < 0.5
	engine.seed(17);

	// Spread > mpi
	std::cout << "\nQuote books should be empty" << "\n";
	std::cout << "Ask Quote Book empty: \n";
	std::cout << "Size: " << j1.askBook.size() << "\n";
	std::cout << "Bid Quote Book empty: \n";
	std::cout << "Size: " << j1.bidBook.size() << "\n";

	// PJ jumps bid and ask by 1
	tob = { 27, 999, 5, 1008, 5 };
	j1.processSignal(tob, 28, 0.5, engine, distUreal);
	j1.processSignal(tob, 29, 0.5, engine, distUreal);
	std::cout << "\nPJ takes the inside" << "\n";
	cSide1 = j1.askBook[0].side == Side::BUY ? 'B' : 'S';
	std::cout << "Ask Quote 1007: \n";
	std::cout << "Trader ID: " << j1.askBook[0].id << "\n";
	std::cout << "Order ID: " << j1.askBook[0].oid << "\n";
	std::cout << "Timestamp: " << j1.askBook[0].step << "\n";
	std::cout << "Type: " << j1.askBook[0].otype << "\n";
	std::cout << "Quantity: " << j1.askBook[0].qty << "\n";
	std::cout << "Side: " << cSide1 << "\n";
	std::cout << "Price: " << j1.askBook[0].price << "\n";
	cSide1 = j1.bidBook[0].side == Side::BUY ? 'B' : 'S';
	std::cout << "Bid Quote 1000: \n";
	std::cout << "Trader ID: " << j1.bidBook[0].id << "\n";
	std::cout << "Order ID: " << j1.bidBook[0].oid << "\n";
	std::cout << "Timestamp: " << j1.bidBook[0].step << "\n";
	std::cout << "Type: " << j1.bidBook[0].otype << "\n";
	std::cout << "Quantity: " << j1.bidBook[0].qty << "\n";
	std::cout << "Side: " << cSide1 << "\n";
	std::cout << "Price: " << j1.bidBook[0].price << "\n";

	// PJ behind the best prices: cancels then jumps bid and ask by 1
	engine.seed(17);
	tob = { 27, 1001, 5, 1006, 5 };
	j1.processSignal(tob, 28, 0.5, engine, distUreal);
	j1.processSignal(tob, 29, 0.5, engine, distUreal);

	std::cout << "\nPJ Cancels Old Quotes" << "\n";
	cSide1 = j1.cancelCollector[0].side == Side::BUY ? 'B' : 'S';
	std::cout << "Cancel Bid Quote 1000: \n";
	std::cout << "Trader ID: " << j1.cancelCollector[0].id << "\n";
	std::cout << "Order ID: " << j1.cancelCollector[0].oid << "\n";
	std::cout << "Timestamp: " << j1.cancelCollector[0].step << "\n";
	std::cout << "Type: " << j1.cancelCollector[0].otype << "\n";
	std::cout << "Quantity: " << j1.cancelCollector[0].qty << "\n";
	std::cout << "Side: " << cSide1 << "\n";
	std::cout << "Price: " << j1.cancelCollector[0].price << "\n";
	cSide1 = j1.cancelCollector[1].side == Side::BUY ? 'B' : 'S';
	std::cout << "Cancel Ask Quote 1007: \n";
	std::cout << "Trader ID: " << j1.cancelCollector[1].id << "\n";
	std::cout << "Order ID: " << j1.cancelCollector[1].oid << "\n";
	std::cout << "Timestamp: " << j1.cancelCollector[1].step << "\n";
	std::cout << "Type: " << j1.cancelCollector[1].otype << "\n";
	std::cout << "Quantity: " << j1.bidBook[0].qty << "\n";
	std::cout << "Side: " << cSide1 << "\n";
	std::cout << "Price: " << j1.cancelCollector[1].price << "\n";

	std::cout << "\nPJ takes the inside" << "\n";
	cSide1 = j1.askBook[0].side == Side::BUY ? 'B' : 'S';
	std::cout << "Ask Quote 1005: \n";
	std::cout << "Trader ID: " << j1.askBook[0].id << "\n";
	std::cout << "Order ID: " << j1.askBook[0].oid << "\n";
	std::cout << "Timestamp: " << j1.askBook[0].step << "\n";
	std::cout << "Type: " << j1.askBook[0].otype << "\n";
	std::cout << "Quantity: " << j1.askBook[0].qty << "\n";
	std::cout << "Side: " << cSide1 << "\n";
	std::cout << "Price: " << j1.askBook[0].price << "\n";
	cSide1 = j1.bidBook[0].side == Side::BUY ? 'B' : 'S';
	std::cout << "Bid Quote 1002: \n";
	std::cout << "Trader ID: " << j1.bidBook[0].id << "\n";
	std::cout << "Order ID: " << j1.bidBook[0].oid << "\n";
	std::cout << "Timestamp: " << j1.bidBook[0].step << "\n";
	std::cout << "Type: " << j1.bidBook[0].otype << "\n";
	std::cout << "Quantity: " << j1.bidBook[0].qty << "\n";
	std::cout << "Side: " << cSide1 << "\n";
	std::cout << "Price: " << j1.bidBook[0].price << "\n";
	j1.cancelCollector.clear();

	// PJ alone at the inside: nothing happens
	engine.seed(17);
	tob = { 27, 1002, 10, 1005, 10 };
	j1.processSignal(tob, 28, 0.5, engine, distUreal);
	j1.processSignal(tob, 29, 0.5, engine, distUreal);

	std::cout << "\nPJ cancelCollector is empty" << "\n";
	std::cout << j1.cancelCollector.size();

	std::cout << "\nPJ quotes unchanged" << "\n";
	cSide1 = j1.askBook[0].side == Side::BUY ? 'B' : 'S';
	std::cout << "Ask Quote 1005: \n";
	std::cout << "Trader ID: " << j1.askBook[0].id << "\n";
	std::cout << "Order ID: " << j1.askBook[0].oid << "\n";
	std::cout << "Timestamp: " << j1.askBook[0].step << "\n";
	std::cout << "Type: " << j1.askBook[0].otype << "\n";
	std::cout << "Quantity: " << j1.askBook[0].qty << "\n";
	std::cout << "Side: " << cSide1 << "\n";
	std::cout << "Price: " << j1.askBook[0].price << "\n";
	cSide1 = j1.bidBook[0].side == Side::BUY ? 'B' : 'S';
	std::cout << "Bid Quote 1002: \n";
	std::cout << "Trader ID: " << j1.bidBook[0].id << "\n";
	std::cout << "Order ID: " << j1.bidBook[0].oid << "\n";
	std::cout << "Timestamp: " << j1.bidBook[0].step << "\n";
	std::cout << "Type: " << j1.bidBook[0].otype << "\n";
	std::cout << "Quantity: " << j1.bidBook[0].qty << "\n";
	std::cout << "Side: " << cSide1 << "\n";
	std::cout << "Price: " << j1.bidBook[0].price << "\n";

	// PJ not alone at inside: cancels then jumps bid and ask by 1
	engine.seed(17);
	tob = { 27, 1002, 20, 1005, 20 };
	j1.processSignal(tob, 28, 0.5, engine, distUreal);
	j1.processSignal(tob, 29, 0.5, engine, distUreal);

	std::cout << "\nPJ Cancels Old Quotes" << "\n";
	cSide1 = j1.cancelCollector[0].side == Side::BUY ? 'B' : 'S';
	std::cout << "Cancel Bid Quote 1002: \n";
	std::cout << "Trader ID: " << j1.cancelCollector[0].id << "\n";
	std::cout << "Order ID: " << j1.cancelCollector[0].oid << "\n";
	std::cout << "Timestamp: " << j1.cancelCollector[0].step << "\n";
	std::cout << "Type: " << j1.cancelCollector[0].otype << "\n";
	std::cout << "Quantity: " << j1.cancelCollector[0].qty << "\n";
	std::cout << "Side: " << cSide1 << "\n";
	std::cout << "Price: " << j1.cancelCollector[0].price << "\n";
	cSide1 = j1.cancelCollector[1].side == Side::BUY ? 'B' : 'S';
	std::cout << "Cancel Ask Quote 1005: \n";
	std::cout << "Trader ID: " << j1.cancelCollector[1].id << "\n";
	std::cout << "Order ID: " << j1.cancelCollector[1].oid << "\n";
	std::cout << "Timestamp: " << j1.cancelCollector[1].step << "\n";
	std::cout << "Type: " << j1.cancelCollector[1].otype << "\n";
	std::cout << "Quantity: " << j1.bidBook[0].qty << "\n";
	std::cout << "Side: " << cSide1 << "\n";
	std::cout << "Price: " << j1.cancelCollector[1].price << "\n";

	std::cout << "\nPJ takes the inside" << "\n";
	cSide1 = j1.askBook[0].side == Side::BUY ? 'B' : 'S';
	std::cout << "Ask Quote 1004: \n";
	std::cout << "Trader ID: " << j1.askBook[0].id << "\n";
	std::cout << "Order ID: " << j1.askBook[0].oid << "\n";
	std::cout << "Timestamp: " << j1.askBook[0].step << "\n";
	std::cout << "Type: " << j1.askBook[0].otype << "\n";
	std::cout << "Quantity: " << j1.askBook[0].qty << "\n";
	std::cout << "Side: " << cSide1 << "\n";
	std::cout << "Price: " << j1.askBook[0].price << "\n";
	cSide1 = j1.bidBook[0].side == Side::BUY ? 'B' : 'S';
	std::cout << "Bid Quote 1003: \n";
	std::cout << "Trader ID: " << j1.bidBook[0].id << "\n";
	std::cout << "Order ID: " << j1.bidBook[0].oid << "\n";
	std::cout << "Timestamp: " << j1.bidBook[0].step << "\n";
	std::cout << "Type: " << j1.bidBook[0].otype << "\n";
	std::cout << "Quantity: " << j1.bidBook[0].qty << "\n";
	std::cout << "Side: " << cSide1 << "\n";
	std::cout << "Price: " << j1.bidBook[0].price << "\n";
	j1.cancelCollector.clear();

	// Spread at MPI, PJ alone at inside: nothing happens
	engine.seed(17);
	tob = { 27, 1003, 10, 1004, 10 };
	j1.processSignal(tob, 28, 0.5, engine, distUreal);
	j1.processSignal(tob, 29, 0.5, engine, distUreal);

	std::cout << "\nPJ cancelCollector is empty" << "\n";
	std::cout << j1.cancelCollector.size();

	std::cout << "\nPJ at the inside; spread == 1" << "\n";
	cSide1 = j1.askBook[0].side == Side::BUY ? 'B' : 'S';
	std::cout << "Ask Quote 1004: \n";
	std::cout << "Trader ID: " << j1.askBook[0].id << "\n";
	std::cout << "Order ID: " << j1.askBook[0].oid << "\n";
	std::cout << "Timestamp: " << j1.askBook[0].step << "\n";
	std::cout << "Type: " << j1.askBook[0].otype << "\n";
	std::cout << "Quantity: " << j1.askBook[0].qty << "\n";
	std::cout << "Side: " << cSide1 << "\n";
	std::cout << "Price: " << j1.askBook[0].price << "\n";
	cSide1 = j1.bidBook[0].side == Side::BUY ? 'B' : 'S';
	std::cout << "Bid Quote 1003: \n";
	std::cout << "Trader ID: " << j1.bidBook[0].id << "\n";
	std::cout << "Order ID: " << j1.bidBook[0].oid << "\n";
	std::cout << "Timestamp: " << j1.bidBook[0].step << "\n";
	std::cout << "Type: " << j1.bidBook[0].otype << "\n";
	std::cout << "Quantity: " << j1.bidBook[0].qty << "\n";
	std::cout << "Side: " << cSide1 << "\n";
	std::cout << "Price: " << j1.bidBook[0].price << "\n";

	// Spread at MPI, PJ not at inside: PJ cancels
	engine.seed(17);
	PennyJumper j2(1, 1, setMaxQ(50), 1);
	tob = { 27, 1000, 10, 1010, 10 };
	j2.processSignal(tob, 28, 0.5, engine, distUreal);
	j2.processSignal(tob, 29, 0.5, engine, distUreal);

	std::cout << "\nPJ spread == 8" << "\n";
	cSide1 = j2.askBook[0].side == Side::BUY ? 'B' : 'S';
	std::cout << "Ask Quote 1009: \n";
	std::cout << "Trader ID: " << j2.askBook[0].id << "\n";
	std::cout << "Order ID: " << j2.askBook[0].oid << "\n";
	std::cout << "Timestamp: " << j2.askBook[0].step << "\n";
	std::cout << "Type: " << j2.askBook[0].otype << "\n";
	std::cout << "Quantity: " << j2.askBook[0].qty << "\n";
	std::cout << "Side: " << cSide1 << "\n";
	std::cout << "Price: " << j2.askBook[0].price << "\n";
	cSide1 = j2.bidBook[0].side == Side::BUY ? 'B' : 'S';
	std::cout << "Bid Quote 1001: \n";
	std::cout << "Trader ID: " << j2.bidBook[0].id << "\n";
	std::cout << "Order ID: " << j2.bidBook[0].oid << "\n";
	std::cout << "Timestamp: " << j2.bidBook[0].step << "\n";
	std::cout << "Type: " << j2.bidBook[0].otype << "\n";
	std::cout << "Quantity: " << j2.bidBook[0].qty << "\n";
	std::cout << "Side: " << cSide1 << "\n";
	std::cout << "Price: " << j2.bidBook[0].price << "\n";

	engine.seed(17);
	tob = { 27, 1005, 10, 1006, 10 };
	j2.processSignal(tob, 28, 0.5, engine, distUreal);
	j2.processSignal(tob, 29, 0.5, engine, distUreal);

	std::cout << "\nQuote books should be empty" << "\n";
	std::cout << "Ask Quote Book empty: \n";
	std::cout << "Size: " << j2.askBook.size() << "\n";
	std::cout << "Bid Quote Book empty: \n";
	std::cout << "Size: " << j2.bidBook.size() << "\n";

	std::cout << std::endl;
}

*/
