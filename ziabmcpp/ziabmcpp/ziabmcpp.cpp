// ziabmcpp.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"

#include <iostream>     // std::cout, std::endl
#include <list>			// std::list
#include <map>			// std::map
#include <random>		// std::random_device, std::mt19937, std::uniform_real_distribution, std::uniform_int_distribution
#include <string>		// std::string
#include <tuple>        // std::tuple, std::get
#include <vector>		// std::vector

#include "Sharedstx.h"
#include "ZITrader.h"
#include "Orderbook.h"
#include "Taker.h"

using cSide = char;

std::random_device random_device;
std::mt19937 engine{ random_device() };
std::vector<int> defaultVec = { 1, 5, 10, 25, 50 };
std::uniform_real_distribution<> distUreal(0, 1);

int setMaxQ(int maxq)
{
	std::vector<int> actualVec(0);
	std::copy_if(defaultVec.begin(), defaultVec.end(), std::back_inserter(actualVec), [&maxq](int i) { return i <= maxq; });
	std::uniform_int_distribution<int> distUint(0, actualVec.size() - 1);
	return actualVec[distUint(engine)];
}

double buySellP()
{
	return distUreal(engine);
}

void testZITrader()
/* Instantiate a ZITrader; test makeAddQuote
*/
{
	ZITrader z1(1, setMaxQ(50));
	std::cout << "Trader Type: " << z1.traderType << "\n";
	std::cout << "Max Quantity: " << z1.orderSize << "\n";
	std::cout << "Trader ID: " << z1.tId << "\n";
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

	ZITrader z2(2, setMaxQ(50));
	std::cout << "Trader Type: " << z2.traderType << "\n";
	std::cout << "Max Quantity: " << z2.orderSize << "\n";
	std::cout << "Trader ID: " << z2.tId << "\n";
	std::cout << "Quote Collector Before: " << z2.quoteCollector.size() << "\n";
	std::cout << std::endl;
}

void testTaker()
/* Instantiate a Taker; test processSignal
*/
{
	Taker t1(1, setMaxQ(50));
	std::cout << "Trader Type: " << t1.traderType << "\n";
	std::cout << "Max Quantity: " << t1.orderSize << "\n";
	std::cout << "Trader ID: " << t1.tId << "\n";
	std::cout << "Quote Collector Before: " << t1.quoteCollector.size() << "\n";
	std::cout << std::endl;

	Step step1 = 27;
	double qTake = 0.5;

	t1.processSignal(step1, qTake, buySellP());
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

	Taker t2(2, setMaxQ(50));
	Taker t3(27, setMaxQ(50));
	std::cout << "Trader Type: " << t2.traderType << "\n";
	std::cout << "Max Quantity: " << t2.orderSize << "\n";
	std::cout << "Trader ID: " << t2.tId << "\n";
	std::cout << "Quote Collector Before: " << t2.quoteCollector.size() << "\n";
	std::cout << std::endl;
}

//void testOrderbookQuote()
//{
//	Side myside = Side::BUY;
//	if (myside == Side::BUY)
//		std::cout << "Side out: " << "BUY" << std::endl;

//	Quote q1 = { "t1_1", 100 };
//	Quote q2 = { "t1_2", 200 };
//	Quote q3 = { "t1_3", 300 };
//	Quotes quotes1, quotes2, quotes3;
//	quotes1.emplace_back(q1);
//	quotes2.emplace_back(q2);
//	quotes3.emplace_back(q3);
//	quotes3.emplace_back(Quote{ "t1_4", 400 });
//	Level l1 = { 1000, quotes1 };
//	BookSide bids;
//	Id id{ "t2_1" };
//	Side side{ Side::BUY };
//	Prc price{ 1009 };
//	Qty qty{ 250 };

//	if (side == Side::BUY)
//		if (bids.count(price) > 0)
//			std::cout << "Price in map already!" << std::endl;
//		else
//			bids.emplace(price, Level{ qty, Quotes{ Quote{ id, qty } } });

//	Id id2{ "t2_2" };
//	Side side2{ Side::BUY };
//	Prc price2{ 1009 };
//	Qty qty2{ 150 };

//	if (side == Side::BUY)
//		if (bids.count(price2) > 0)
//		{
//			bids.at(price2).qty += qty;
//			bids.at(price2).quotes.emplace_back(Quote{ id2, qty2 });
//		}
//		else
//			bids.emplace(price2, Level{ qty2, Quotes{ Quote{ id2, qty2 } } });

//	auto b = &bids;

	//	bids.emplace(1001, Level { 100, quotes1 });
//	b->emplace(1001, Level{ 100, quotes1 });
//	bids.emplace(999, Level{ 200, quotes2 });
//	bids.emplace(1005, Level{ 700, quotes3 });
//	for (auto &x : bids)
//	{
//		std::cout << "Price: " << x.first << ", Qty: " << x.second.qty << "\n";
//		for (auto &y : x.second.quotes)
//			std::cout << "Id: " << y.id << ", Qty: " << y.qty << "\n";
//	}

//	auto l = b->find(999);

//	std::cout << "Total Quantity: " << l1.qty << "\n";
//	std::cout << bids.at(999).quotes.begin()->id << "\n";
//	std::cout << bids.rbegin()->second.quotes.begin()->id << "\n";

//	std::cout << std::endl;
//}

void testExchangeAddHistory()
{
	Orderbook exchange1 = Orderbook();
	ZITrader z1(1, setMaxQ(50));

	Step step1 = 23;
	Side side1 = Side::SELL;
	Prc price1 = 1099;

	Order q1 = z1.makeAddQuote(step1, side1, price1);
	std::cout << "Order Collector Before: " << exchange1.history.size() << "\n";
	exchange1.addHistory(q1);
	cSide cSide4 = exchange1.history[0].side == Side::BUY ? 'B' : 'S';
	std::cout << "Order Collector After: " << exchange1.history.size() << "\n";
	std::cout << "First Order: \n";
	std::cout << "Exchange ID: " << exchange1.history[0].exid << "\n";
	std::cout << "Trader ID: " << exchange1.history[0].id << "\n";
	std::cout << "Order ID: " << exchange1.history[0].oid << "\n";
	std::cout << "Timestamp: " << exchange1.history[0].step << "\n";
	std::cout << "Type: " << exchange1.history[0].otype << "\n";
	std::cout << "Quantity: " << exchange1.history[0].qty << "\n";
	std::cout << "Side: " << cSide4 << "\n";
	std::cout << "Price: " << exchange1.history[0].price << "\n";
	std::cout << std::endl;
}

void testExchangeAddBook2()
{
	Orderbook exchange1 = Orderbook();
	exchange1.addBook2(1001, 1, Side::BUY, 999, 100);
	exchange1.addBook2(1001, 2, Side::BUY, 1000, 200);
	exchange1.addBook2(1001, 3, Side::BUY, 1001, 300);
	exchange1.addBook2(1001, 4, Side::BUY, 999, 200);
	std::cout << "Bids:\n";
	for (auto &x : exchange1.bids)
	{
		std::cout << "Price: " << x.first << ", Qty: " << x.second.qty << "\n";
		for (auto &y : x.second.quotes)
			std::cout << "Trader Id: " << y.id << ", Order Id: " << y.oid << ", Qty: " << y.qty << "\n";
	}

	exchange1.addBook2(5001, 1, Side::SELL, 1005, 100);
	exchange1.addBook2(5001, 2, Side::SELL, 1006, 200);
	exchange1.addBook2(5001, 3, Side::SELL, 1007, 300);
	exchange1.addBook2(5001, 4, Side::SELL, 1005, 200);
	std::cout << "Asks:\n";
	for (auto &x : exchange1.asks)
	{
		std::cout << "Price: " << x.first << ", Qty: " << x.second.qty << "\n";
		for (auto &y : x.second.quotes)
			std::cout << "Trader Id: " << y.id << ", Order Id: " << y.oid << ", Qty: " << y.qty << "\n";
	}

	traderId tid = 5001;
	Id oid = 1;
	auto& blq = exchange1.lookup[std::make_pair(tid, oid)];
	auto& b = std::get<0>(blq);
	auto& l = std::get<1>(blq);
	auto& q = std::get<2>(blq);
	std::cout << "From lookup:\n";
	std::cout << "From b:\n";
	for (auto &x : *b)
		std::cout << "Price: " << x.first << ", Qty: " << x.second.qty << "\n";
	std::cout << "From l:\n";
	std::cout << "Price: " << l->first << ", Qty: " << l->second.qty << ", Count" << l->second.ocnt << "\n";
	std::cout << "With decrement!!!" << ", Price: " << l->first << ", Qty: " << l->second.qty << ", Count" << --l->second.ocnt << "\n";
	std::cout << "From q:\n";
	std::cout << "TraderId: " << q->id << ", Id: " << q->oid << ", Qty: " << q->qty << "\n";

	std::cout << std::endl;
}

void testOrderbookRemove()
{
	Orderbook exchange1 = Orderbook();
	exchange1.addBook2(1001, 1, Side::BUY, 999, 100);
	exchange1.addBook2(1001, 2, Side::BUY, 1000, 200);
	exchange1.addBook2(1001, 3, Side::BUY, 1001, 300);
	exchange1.addBook2(1001, 4, Side::BUY, 999, 200);

	exchange1.addBook2(5001, 1, Side::SELL, 1005, 100);
	exchange1.addBook2(5001, 2, Side::SELL, 1006, 200);
	exchange1.addBook2(5001, 3, Side::SELL, 1007, 300);
	exchange1.addBook2(5001, 4, Side::SELL, 1005, 200);

	traderId tid = 1001;
	Id oid = 2;
	auto& blq = exchange1.lookup[std::make_pair(tid, oid)];
	auto b = std::get<0>(blq);
	auto& l = std::get<1>(blq);
	auto& q = std::get<2>(blq);
	std::cout << "Before\n";
	std::cout << "From lookup:\n";
	std::cout << "From b:\n";
	for (auto &x : *b)
		std::cout << "Price: " << x.first << ", Qty: " << x.second.qty << ", Count: " << x.second.ocnt << "\n";
	std::cout << "From l:\n";
	std::cout << "Price: " << l->first << ", Qty: " << l->second.qty << ", Count: " << l->second.ocnt << "\n";
	std::cout << "From q:\n";
	std::cout << "TraderId: " << q->id << ", Id: " << q->oid << ", Qty: " << q->qty << "\n";
	std::cout << "Lookup size: " << exchange1.lookup.size() << "\n";
	std::cout << std::endl;

	exchange1.remove(tid, oid, 200);

	std::cout << "Remove 1001-2\n";
	std::cout << "From lookup:\n";
	std::cout << "From b:\n";
	for (auto &x : *b)
		std::cout << "Price: " << x.first << ", Qty: " << x.second.qty << ", Count: " << x.second.ocnt << "\n";
	std::cout << "Lookup size: " << exchange1.lookup.size() << "\n";
	std::cout << std::endl;

	exchange1.remove(1001, 4, 200);
	std::cout << "Remove 1001-4\n";
	std::cout << "From lookup:\n";
	std::cout << "From b:\n";
	for (auto &x : *b)
		std::cout << "Price: " << x.first << ", Qty: " << x.second.qty << ", Count: " << x.second.ocnt << "\n";
	std::cout << "Lookup size: " << exchange1.lookup.size() << "\n";
	std::cout << std::endl;
}

void testOrderbookModify()
{
	Orderbook exchange1 = Orderbook();
	exchange1.addBook2(1001, 1, Side::BUY, 999, 100);
	exchange1.addBook2(1001, 2, Side::BUY, 1000, 200);
	exchange1.addBook2(1001, 3, Side::BUY, 1001, 300);
	exchange1.addBook2(1001, 4, Side::BUY, 999, 200);

	exchange1.addBook2(5001, 1, Side::SELL, 1005, 100);
	exchange1.addBook2(5001, 2, Side::SELL, 1006, 200);
	exchange1.addBook2(5001, 3, Side::SELL, 1007, 300);
	exchange1.addBook2(5001, 4, Side::SELL, 1005, 200);

	traderId tid = 5001;
	Id oid = 2;
	auto& blq = exchange1.lookup[std::make_pair(tid, oid)];
	auto b = std::get<0>(blq);
	auto& l = std::get<1>(blq);
	auto& q = std::get<2>(blq);
	std::cout << "Before\n";
	std::cout << "From lookup:\n";
	std::cout << "From b:\n";
	for (auto &x : *b)
		std::cout << "Price: " << x.first << ", Qty: " << x.second.qty << ", Count: " << x.second.ocnt << "\n";
	std::cout << "From l:\n";
	std::cout << "Price: " << l->first << ", Qty: " << l->second.qty << ", Count: " << l->second.ocnt << "\n";
	std::cout << "From q:\n";
	std::cout << "TraderId: " << q->id << ", Id: " << q->oid << ", Qty: " << q->qty << "\n";
	std::cout << "Lookup size: " << exchange1.lookup.size() << "\n";
	std::cout << std::endl;

	exchange1.modify(tid, oid, 50);

	std::cout << "Modify 5001-2\n";
	std::cout << "From lookup:\n";
	std::cout << "From b:\n";
	for (auto &x : *b)
		std::cout << "Price: " << x.first << ", Qty: " << x.second.qty << ", Count: " << x.second.ocnt << "\n";
	std::cout << "From l:\n";
	std::cout << "Price: " << l->first << ", Qty: " << l->second.qty << ", Count: " << l->second.ocnt << "\n";
	std::cout << "From q:\n";
	std::cout << "TraderId: " << q->id << ", Id: " << q->oid << ", Qty: " << q->qty << "\n";
	std::cout << "Lookup size: " << exchange1.lookup.size() << "\n";
	std::cout << std::endl;

	exchange1.modify(tid, oid, 150);

	std::cout << "Modify 5001-2\n";
	std::cout << "From lookup:\n";
	std::cout << "From b:\n";
	for (auto &x : *b)
		std::cout << "Price: " << x.first << ", Qty: " << x.second.qty << ", Count: " << x.second.ocnt << "\n";
	std::cout << "Lookup size: " << exchange1.lookup.size() << "\n";

	std::cout << std::endl;
}


int main()
{
	engine.seed(33);

//	testZITrader();
//	testTaker();
//	testOrderbookQuote();
//	testExchangeAddHistory();
//	testExchangeAddBook2();
//	testOrderbookRemove();

	testOrderbookModify();

	

	return 0;
}

