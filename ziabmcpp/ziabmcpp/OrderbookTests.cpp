// OrderbookTests.cpp
// OrderbookTests class

#include "stdafx.h"

#include <iostream>

#include "OrderbookTests.h"
#include "ZITrader.h"

void OrderbookTests::testExchangeAddHistory()
{
	Orderbook exchange1 = Orderbook();
	ZITrader z1(7, 1, 10, 1);

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

void OrderbookTests::testExchangeAddBook2()
{
	Orderbook exchange1 = Orderbook();
	exchange1.addBook2(1001, 1, Side::BUY, 999, 100, 1);
	exchange1.addBook2(1001, 2, Side::BUY, 1000, 200, 2);
	exchange1.addBook2(1001, 3, Side::BUY, 1001, 300, 3);
	exchange1.addBook2(1001, 4, Side::BUY, 999, 200, 4);
	std::cout << "Bids:\n";
	for (auto &x : exchange1.bids)
	{
		std::cout << "Price: " << x.first << ", Qty: " << x.second.qty << "\n";
		for (auto &y : x.second.quotes)
			std::cout << "Trader Id: " << y.id << ", Order Id: " << y.oid << ", Qty: " << y.qty << "\n";
	}

	exchange1.addBook2(5001, 1, Side::SELL, 1005, 100, 5);
	exchange1.addBook2(5001, 2, Side::SELL, 1006, 200, 6);
	exchange1.addBook2(5001, 3, Side::SELL, 1007, 300, 7);
	exchange1.addBook2(5001, 4, Side::SELL, 1005, 200, 8);
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

void OrderbookTests::testOrderbookRemove()
{
	Orderbook exchange1 = Orderbook();
	exchange1.addBook2(1001, 1, Side::BUY, 999, 100, 1);
	exchange1.addBook2(1001, 2, Side::BUY, 1000, 200, 2);
	exchange1.addBook2(1001, 3, Side::BUY, 1001, 300, 3);
	exchange1.addBook2(1001, 4, Side::BUY, 999, 200, 4);

	exchange1.addBook2(5001, 1, Side::SELL, 1005, 100, 5);
	exchange1.addBook2(5001, 2, Side::SELL, 1006, 200, 6);
	exchange1.addBook2(5001, 3, Side::SELL, 1007, 300, 7);
	exchange1.addBook2(5001, 4, Side::SELL, 1005, 200, 8);

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

void OrderbookTests::testOrderbookModify()
{
	Orderbook exchange1 = Orderbook();
	exchange1.addBook2(1001, 1, Side::BUY, 999, 100, 1);
	exchange1.addBook2(1001, 2, Side::BUY, 1000, 200, 2);
	exchange1.addBook2(1001, 3, Side::BUY, 1001, 300, 3);
	exchange1.addBook2(1001, 4, Side::BUY, 999, 200, 4);

	exchange1.addBook2(5001, 1, Side::SELL, 1005, 100, 5);
	exchange1.addBook2(5001, 2, Side::SELL, 1006, 200, 6);
	exchange1.addBook2(5001, 3, Side::SELL, 1007, 300, 7);
	exchange1.addBook2(5001, 4, Side::SELL, 1005, 200, 8);

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

void OrderbookTests::testExchangeAddTrade()
{
	Orderbook exchange1 = Orderbook();

	traderId restid1 = 1004;
	Id restoid1 = 123;
	Step reststep1 = 23;
	traderId incid1 = 5010;
	Id incoid1 = 468;
	Step incstep1 = 27;
	Qty qty1 = 150;
	Side side1 = Side::SELL;
	Prc price1 = 1099;

	std::cout << "Trade Book Before: " << exchange1.trades.size() << "\n";
	exchange1.addTrade(restid1, restoid1, reststep1, incid1, incoid1, incstep1, qty1, side1, price1);

	cSide cSide4 = exchange1.trades[0].side == Side::BUY ? 'B' : 'S';
	std::cout << "Trade Book After: " << exchange1.trades.size() << "\n";
	std::cout << "First Order: \n";
	std::cout << "Resting Trader ID: " << exchange1.trades[0].restid << "\n";
	std::cout << "Resting Order ID: " << exchange1.trades[0].restoid << "\n";
	std::cout << "Resting Step: " << exchange1.trades[0].reststep << "\n";
	std::cout << "Incoming Trader ID: " << exchange1.trades[0].incid << "\n";
	std::cout << "Incomig Order ID: " << exchange1.trades[0].incoid << "\n";
	std::cout << "Incoming Step: " << exchange1.trades[0].incstep << "\n";
	std::cout << "Quantity: " << exchange1.trades[0].qty << "\n";
	std::cout << "Side: " << cSide4 << "\n";
	std::cout << "Price: " << exchange1.trades[0].price << "\n";
	std::cout << std::endl;
}

void OrderbookTests::testExchangeConfirmTrade()
{
	Orderbook exchange1 = Orderbook();

	traderId restid1 = 1004;
	Id restoid1 = 123;
	Step reststep1 = 23;
	Qty qty1 = 150;
	Side side1 = Side::BUY;
	Prc price1 = 955;

	std::cout << "Trade Confirms Before: " << exchange1.tradeconfirms.size() << "\n";
	exchange1.confirmTrade(restid1, restoid1, reststep1, qty1, side1, price1);

	cSide cSide4 = exchange1.tradeconfirms[0].side == Side::BUY ? 'B' : 'S';
	std::cout << "Trade Confirms After: " << exchange1.tradeconfirms.size() << "\n";
	std::cout << "First Order: \n";
	std::cout << "Resting Trader ID: " << exchange1.tradeconfirms[0].restid << "\n";
	std::cout << "Resting Order ID: " << exchange1.tradeconfirms[0].restoid << "\n";
	std::cout << "Resting Step: " << exchange1.tradeconfirms[0].reststep << "\n";
	std::cout << "Quantity: " << exchange1.tradeconfirms[0].qty << "\n";
	std::cout << "Side: " << cSide4 << "\n";
	std::cout << "Price: " << exchange1.tradeconfirms[0].price << "\n";
	std::cout << std::endl;
}

void OrderbookTests::testExchangeConfirmModify()
{
	Orderbook exchange1 = Orderbook();

	traderId restid1 = 5002;
	Id restoid1 = 1206;
	Step reststep1 = 96587;
	Qty qty1 = 350;
	Side side1 = Side::BUY;

	std::cout << "Modify Confirms Before: " << exchange1.modifyconfirms.size() << "\n";
	exchange1.confirmModify(restid1, restoid1, reststep1, qty1, side1);

	cSide cSide4 = exchange1.modifyconfirms[0].side == Side::BUY ? 'B' : 'S';
	std::cout << "Modify Confirms After: " << exchange1.modifyconfirms.size() << "\n";
	std::cout << "First Order: \n";
	std::cout << "Resting Trader ID: " << exchange1.modifyconfirms[0].restid << "\n";
	std::cout << "Resting Order ID: " << exchange1.modifyconfirms[0].restoid << "\n";
	std::cout << "Resting Step: " << exchange1.modifyconfirms[0].reststep << "\n";
	std::cout << "Quantity: " << exchange1.modifyconfirms[0].qty << "\n";
	std::cout << "Side: " << cSide4 << "\n";
	std::cout << std::endl;
}

void OrderbookTests::testExchangeBookTop()
{
	Orderbook exchange1 = Orderbook();
	exchange1.addBook2(1001, 1, Side::BUY, 999, 100, 1);
	exchange1.addBook2(1001, 2, Side::BUY, 1000, 200, 2);
	exchange1.addBook2(1001, 3, Side::BUY, 1001, 300, 3);
	exchange1.addBook2(1001, 4, Side::BUY, 999, 200, 4);

	exchange1.addBook2(5001, 1, Side::SELL, 1005, 100, 5);
	exchange1.addBook2(5001, 2, Side::SELL, 1006, 200, 6);
	exchange1.addBook2(5001, 3, Side::SELL, 1007, 300, 7);
	exchange1.addBook2(5001, 4, Side::SELL, 1005, 200, 8);

	std::vector<TopOfBook>::iterator top;
	top = exchange1.bookTop(23);

	std::cout << "From returned TopOfBook struct: \n\n";
	std::cout << "Step: " << top->step << "\n";
	std::cout << "Best Bid: " << top->bestbid << "\n";
	std::cout << "Best Bid Size: " << top->bestbidsz << "\n";
	std::cout << "Best Ask: " << top->bestask << "\n";
	std::cout << "Best Ask Size: " << top->bestasksz << "\n\n";
	std::cout << std::endl;

	std::cout << "From TopOfBook Container: \n\n";
	std::cout << "Step: " << exchange1.tob[0].step << "\n";
	std::cout << "Best Bid: " << exchange1.tob[0].bestbid << "\n";
	std::cout << "Best Bid Size: " << exchange1.tob[0].bestbidsz << "\n";
	std::cout << "Best Ask: " << exchange1.tob[0].bestask << "\n";
	std::cout << "Best Ask Size: " << exchange1.tob[0].bestasksz << "\n\n";
	std::cout << std::endl;

	exchange1.addBook2(5001, 5, Side::SELL, 1004, 600, 9);
	top = exchange1.bookTop(27);

	std::cout << "From returned TopOfBook struct: \n\n";
	std::cout << "Step: " << top->step << "\n";
	std::cout << "Best Bid: " << top->bestbid << "\n";
	std::cout << "Best Bid Size: " << top->bestbidsz << "\n";
	std::cout << "Best Ask: " << top->bestask << "\n";
	std::cout << "Best Ask Size: " << top->bestasksz << "\n";
	std::cout << std::endl;

	std::cout << "From TopOfBook Container: \n\n";
	std::cout << "Step: " << exchange1.tob[1].step << "\n";
	std::cout << "Best Bid: " << exchange1.tob[1].bestbid << "\n";
	std::cout << "Best Bid Size: " << exchange1.tob[1].bestbidsz << "\n";
	std::cout << "Best Ask: " << exchange1.tob[1].bestask << "\n";
	std::cout << "Best Ask Size: " << exchange1.tob[1].bestasksz << "\n";
	std::cout << std::endl;
}

void OrderbookTests::testExchangeBookTop2()
{
	Orderbook exchange1 = Orderbook();
	exchange1.addBook2(1001, 1, Side::BUY, 999, 100, 1);
	exchange1.addBook2(1001, 2, Side::BUY, 1000, 200, 2);
	exchange1.addBook2(1001, 3, Side::BUY, 1001, 300, 3);
	exchange1.addBook2(1001, 4, Side::BUY, 999, 200, 4);

	exchange1.addBook2(5001, 1, Side::SELL, 1005, 100, 5);
	exchange1.addBook2(5001, 2, Side::SELL, 1006, 200, 6);
	exchange1.addBook2(5001, 3, Side::SELL, 1007, 300, 7);
	exchange1.addBook2(5001, 4, Side::SELL, 1005, 200, 8);

	exchange1.bookTop2(23);

	std::cout << "From returned TopOfBook struct: \n\n";
	std::cout << "Step: " << exchange1.tob.back().step << "\n";
	std::cout << "Best Bid: " << exchange1.tob.back().bestbid << "\n";
	std::cout << "Best Bid Size: " << exchange1.tob.back().bestbidsz << "\n";
	std::cout << "Best Ask: " << exchange1.tob.back().bestask << "\n";
	std::cout << "Best Ask Size: " << exchange1.tob.back().bestasksz << "\n\n";
	std::cout << std::endl;

	std::cout << "From TopOfBook Container: \n\n";
	std::cout << "Step: " << exchange1.tob[0].step << "\n";
	std::cout << "Best Bid: " << exchange1.tob[0].bestbid << "\n";
	std::cout << "Best Bid Size: " << exchange1.tob[0].bestbidsz << "\n";
	std::cout << "Best Ask: " << exchange1.tob[0].bestask << "\n";
	std::cout << "Best Ask Size: " << exchange1.tob[0].bestasksz << "\n\n";
	std::cout << std::endl;

	exchange1.addBook2(5001, 5, Side::SELL, 1004, 600, 9);
	exchange1.bookTop(27);

	auto &topper = exchange1.tob.back();

	std::cout << "From returned TopOfBook struct: \n\n";
	std::cout << "Step: " << topper.step << "\n";
	std::cout << "Best Bid: " << topper.bestbid << "\n";
	std::cout << "Best Bid Size: " << topper.bestbidsz << "\n";
	std::cout << "Best Ask: " << topper.bestask << "\n";
	std::cout << "Best Ask Size: " << topper.bestasksz << "\n";
	std::cout << std::endl;

	std::cout << "From TopOfBook Container: \n\n";
	std::cout << "Step: " << exchange1.tob[1].step << "\n";
	std::cout << "Best Bid: " << exchange1.tob[1].bestbid << "\n";
	std::cout << "Best Bid Size: " << exchange1.tob[1].bestbidsz << "\n";
	std::cout << "Best Ask: " << exchange1.tob[1].bestask << "\n";
	std::cout << "Best Ask Size: " << exchange1.tob[1].bestasksz << "\n";
	std::cout << std::endl;
}

void OrderbookTests::testExchangeProcess()
{
	Orderbook exchange1 = Orderbook();
	//	Prime Book
	exchange1.addBook2(1001, 1, Side::BUY, 999, 100, 0);
	exchange1.addBook2(1002, 1, Side::SELL, 1005, 100, 0);

	std::cout << "Prime Bid and Ask\n";
	std::cout << "Bids:\n";
	for (auto &x : exchange1.bids)
	{
		std::cout << "Price: " << x.first << ", Qty: " << x.second.qty << "\n";
		for (auto &y : x.second.quotes)
			std::cout << "Trader Id: " << y.id << ", Order Id: " << y.oid << ", Qty: " << y.qty << "\n";
	}
	std::cout << "Asks:\n";
	for (auto &x : exchange1.asks)
	{
		std::cout << "Price: " << x.first << ", Qty: " << x.second.qty << "\n";
		for (auto &y : x.second.quotes)
			std::cout << "Trader Id: " << y.id << ", Order Id: " << y.oid << ", Qty: " << y.qty << "\n";
	}

	//	Add a new bid to the book
	Order o1{ 1001, 2, 2, 'A', 200, Side::BUY, 997 };
	exchange1.process(o1);
	std::cout << "Add new Bid\n";
	std::cout << "Bids:\n";
	for (auto &x : exchange1.bids)
	{
		std::cout << "Price: " << x.first << ", Qty: " << x.second.qty << "\n";
		for (auto &y : x.second.quotes)
			std::cout << "Trader Id: " << y.id << ", Order Id: " << y.oid << ", Qty: " << y.qty << "\n";
	}

	// Add a new ask to the book
	Order o2{ 1002, 2, 3, 'A', 200, Side::SELL, 1007 };
	exchange1.process(o2);
	std::cout << "Add new Ask\n";
	std::cout << "Asks:\n";
	for (auto &x : exchange1.asks)
	{
		std::cout << "Price: " << x.first << ", Qty: " << x.second.qty << "\n";
		for (auto &y : x.second.quotes)
			std::cout << "Trader Id: " << y.id << ", Order Id: " << y.oid << ", Qty: " << y.qty << "\n";
	}

	//	Modify inside bid
	Order o3{ 1001, 1, 5, 'M', 25, Side::BUY, 999 };
	exchange1.process(o3);
	std::cout << "Modify inside Bid\n";
	std::cout << "Bids:\n";
	for (auto &x : exchange1.bids)
	{
		std::cout << "Price: " << x.first << ", Qty: " << x.second.qty << "\n";
		for (auto &y : x.second.quotes)
			std::cout << "Trader Id: " << y.id << ", Order Id: " << y.oid << ", Qty: " << y.qty << "\n";
	}

	//	Modify inside Ask
	Order o4{ 1002, 1, 7,'M', 75, Side::SELL, 1005 };
	exchange1.process(o4);
	std::cout << "Modify inside Ask\n";
	std::cout << "Asks:\n";
	for (auto &x : exchange1.asks)
	{
		std::cout << "Price: " << x.first << ", Qty: " << x.second.qty << "\n";
		for (auto &y : x.second.quotes)
			std::cout << "Trader Id: " << y.id << ", Order Id: " << y.oid << ", Qty: " << y.qty << "\n";
	}

	//	Cancel away Bid
	Order o5{ 1001, 2, 10, 'C', 200, Side::BUY, 997 };
	exchange1.process(o5);
	std::cout << "Cancel away Bid\n";
	std::cout << "Bids:\n";
	for (auto &x : exchange1.bids)
	{
		std::cout << "Price: " << x.first << ", Qty: " << x.second.qty << "\n";
		for (auto &y : x.second.quotes)
			std::cout << "Trader Id: " << y.id << ", Order Id: " << y.oid << ", Qty: " << y.qty << "\n";
	}

	// Cancel inside Ask
	Order o6{ 1002, 1, 7,'C', 25, Side::SELL, 1005 };
	exchange1.process(o6);
	std::cout << "Cancel inside Ask\n";
	std::cout << "Asks:\n";
	for (auto &x : exchange1.asks)
	{
		std::cout << "Price: " << x.first << ", Qty: " << x.second.qty << "\n";
		for (auto &y : x.second.quotes)
			std::cout << "Trader Id: " << y.id << ", Order Id: " << y.oid << ", Qty: " << y.qty << "\n";
	}

	//	Buy cross the spread
	Order o7{ 4001, 1, 20, 'A', 100, Side::BUY, 1010 };
	std::cout << "Buy order results in a trade at the ask\n";
	exchange1.process(o7);

	//	Sell cross the spread
	Order o8{ 4001, 2, 30, 'A', 10, Side::SELL, 900 };
	std::cout << "Sell order results in a trade at the bid\n";
	exchange1.process(o8);

	std::cout << std::endl;
}

void OrderbookTests::testExchangeCrossCrash()
{
	Orderbook exchange1 = Orderbook();

	//Order { traderId id; Id oid; Step step; char otype; Qty qty; Side side; Prc price; };

	// Test collapse
	Order o1{ 4001, 2, 30, 'A', 10, Side::SELL, 900 };
	exchange1.cross(o1);
	Order o2{ 4001, 3, 30, 'A', 10, Side::BUY, 900 };
	exchange1.cross(o2);
}

void OrderbookTests::testExchangeCrossSell1()
{
	cSide cSide1;
	Orderbook exchange1 = Orderbook();
	//	Prime Book
	exchange1.addBook2(1001, 1, Side::BUY, 999, 100, 0);
	exchange1.addBook2(1002, 1, Side::SELL, 1005, 100, 0);

	// Add some depth
	Order o3{ 1001, 2, 3, 'A', 100, Side::SELL, 1005 };
	Order o4{ 1001, 3, 4, 'A', 100, Side::SELL, 1006 };
	Order o5{ 1001, 4, 4, 'A', 100, Side::SELL, 1008 };

	Order o6{ 1002, 2, 3, 'A', 100, Side::BUY, 999 };
	Order o7{ 1002, 3, 4, 'A', 100, Side::BUY, 998 };
	Order o8{ 1002, 4, 4, 'A', 100, Side::BUY, 996 };

	exchange1.process(o3);
	exchange1.process(o4);
	exchange1.process(o5);
	exchange1.process(o6);
	exchange1.process(o7);
	exchange1.process(o8);

	std::cout << "Bids:\n";
	for (auto &x : exchange1.bids)
	{
		std::cout << "Price: " << x.first << ", Qty: " << x.second.qty << "\n";
		for (auto &y : x.second.quotes)
			std::cout << "Trader Id: " << y.id << ", Order Id: " << y.oid << ", Qty: " << y.qty << "\n";
	}
	std::cout << "\n\nAsks:\n";
	for (auto &x : exchange1.asks)
	{
		std::cout << "Price: " << x.first << ", Qty: " << x.second.qty << "\n";
		for (auto &y : x.second.quotes)
			std::cout << "Trader Id: " << y.id << ", Order Id: " << y.oid << ", Qty: " << y.qty << "\n";
	}

	// Incoming order takes out part of best bid : 1001-1
	// Impacts trades. tradeconfirms, and the bid book.

	Order o9{ 4001, 2, 10, 'A', 50, Side::SELL, 0 };
	exchange1.cross(o9);

	std::cout << "\n\nBid Qty reduced by 50\n";
	std::cout << "Bids:\n";
	for (auto &x : exchange1.bids)
	{
		std::cout << "Price: " << x.first << ", Qty: " << x.second.qty << "\n";
		for (auto &y : x.second.quotes)
			std::cout << "Trader Id: " << y.id << ", Order Id: " << y.oid << ", Qty: " << y.qty << "\n";
	}

	cSide1 = exchange1.trades[0].side == Side::BUY ? 'B' : 'S';
	std::cout << "\nTrade Book After: " << exchange1.trades.size() << "\n";
	std::cout << "First Order: \n";
	std::cout << "Resting Trader ID: " << exchange1.trades[0].restid << "\n";
	std::cout << "Resting Order ID: " << exchange1.trades[0].restoid << "\n";
	std::cout << "Resting Step: " << exchange1.trades[0].reststep << "\n";
	std::cout << "Incoming Trader ID: " << exchange1.trades[0].incid << "\n";
	std::cout << "Incomig Order ID: " << exchange1.trades[0].incoid << "\n";
	std::cout << "Incoming Step: " << exchange1.trades[0].incstep << "\n";
	std::cout << "Quantity: " << exchange1.trades[0].qty << "\n";
	std::cout << "Side: " << cSide1 << "\n";
	std::cout << "Price: " << exchange1.trades[0].price << "\n";

	cSide1 = exchange1.tradeconfirms[0].side == Side::BUY ? 'B' : 'S';
	std::cout << "\nTrade Confirms After: " << exchange1.tradeconfirms.size() << "\n";
	std::cout << "First Order: \n";
	std::cout << "Resting Trader ID: " << exchange1.tradeconfirms[0].restid << "\n";
	std::cout << "Resting Order ID: " << exchange1.tradeconfirms[0].restoid << "\n";
	std::cout << "Step: " << exchange1.tradeconfirms[0].reststep << "\n";
	std::cout << "Quantity: " << exchange1.tradeconfirms[0].qty << "\n";
	std::cout << "Side: " << cSide1 << "\n";
	std::cout << "Price: " << exchange1.tradeconfirms[0].price << "\n";

	// Incoming order takes out remainder of best bid : 1001-1
	// Incoming order takes out some of the next best bid : 1002-2
	// Impacts trades. tradeconfirms, and the bid book.
	exchange1.tradeconfirms.clear();
	Order o10{ 4001, 3, 12, 'A', 75, Side::SELL, 0 };
	exchange1.cross(o10);

	std::cout << "\n\nBid Qty reduced by 75\n";
	std::cout << "Bids:\n";
	for (auto &x : exchange1.bids)
	{
		std::cout << "Price: " << x.first << ", Qty: " << x.second.qty << "\n";
		for (auto &y : x.second.quotes)
			std::cout << "Trader Id: " << y.id << ", Order Id: " << y.oid << ", Qty: " << y.qty << "\n";
	}

	cSide1 = exchange1.trades[1].side == Side::BUY ? 'B' : 'S';
	std::cout << "\nTrade Book After first: " << exchange1.trades.size() << "\n";
	std::cout << "First Order: \n";
	std::cout << "Resting Trader ID: " << exchange1.trades[1].restid << "\n";
	std::cout << "Resting Order ID: " << exchange1.trades[1].restoid << "\n";
	std::cout << "Resting Step: " << exchange1.trades[1].reststep << "\n";
	std::cout << "Incoming Trader ID: " << exchange1.trades[1].incid << "\n";
	std::cout << "Incomig Order ID: " << exchange1.trades[1].incoid << "\n";
	std::cout << "Incoming Step: " << exchange1.trades[1].incstep << "\n";
	std::cout << "Quantity: " << exchange1.trades[1].qty << "\n";
	std::cout << "Side: " << cSide1 << "\n";
	std::cout << "Price: " << exchange1.trades[1].price << "\n";

	cSide1 = exchange1.trades[2].side == Side::BUY ? 'B' : 'S';
	std::cout << "\nTrade Book After second: " << exchange1.trades.size() << "\n";
	std::cout << "Second Order: \n";
	std::cout << "Resting Trader ID: " << exchange1.trades[2].restid << "\n";
	std::cout << "Resting Order ID: " << exchange1.trades[2].restoid << "\n";
	std::cout << "Resting Step: " << exchange1.trades[2].reststep << "\n";
	std::cout << "Incoming Trader ID: " << exchange1.trades[2].incid << "\n";
	std::cout << "Incomig Order ID: " << exchange1.trades[2].incoid << "\n";
	std::cout << "Incoming Step: " << exchange1.trades[2].incstep << "\n";
	std::cout << "Quantity: " << exchange1.trades[2].qty << "\n";
	std::cout << "Side: " << cSide1 << "\n";
	std::cout << "Price: " << exchange1.trades[2].price << "\n";

	cSide1 = exchange1.tradeconfirms[0].side == Side::BUY ? 'B' : 'S';
	std::cout << "\nTrade Confirms After 1: " << exchange1.tradeconfirms.size() << "\n";
	std::cout << "First Order: \n";
	std::cout << "Resting Trader ID: " << exchange1.tradeconfirms[0].restid << "\n";
	std::cout << "Resting Order ID: " << exchange1.tradeconfirms[0].restoid << "\n";
	std::cout << "Step: " << exchange1.tradeconfirms[0].reststep << "\n";
	std::cout << "Quantity: " << exchange1.tradeconfirms[0].qty << "\n";
	std::cout << "Side: " << cSide1 << "\n";
	std::cout << "Price: " << exchange1.tradeconfirms[0].price << "\n";

	cSide1 = exchange1.tradeconfirms[1].side == Side::BUY ? 'B' : 'S';
	std::cout << "\nTrade Confirms After 2: " << exchange1.tradeconfirms.size() << "\n";
	std::cout << "Second Order: \n";
	std::cout << "Resting Trader ID: " << exchange1.tradeconfirms[1].restid << "\n";
	std::cout << "Resting Order ID: " << exchange1.tradeconfirms[1].restoid << "\n";
	std::cout << "Step: " << exchange1.tradeconfirms[1].reststep << "\n";
	std::cout << "Quantity: " << exchange1.tradeconfirms[1].qty << "\n";
	std::cout << "Side: " << cSide1 << "\n";
	std::cout << "Price: " << exchange1.tradeconfirms[1].price << "\n";

	// Incoming order takes out remainder of best bid : 1002-2
	// Incoming order takes out next best bid : 1002-3 @ 998
	// Incoming order adds new order at 997
	// Impacts trades. tradeconfirms, and the bid book.
	exchange1.tradeconfirms.clear();
	Order o11{ 4001, 4, 15, 'A', 200, Side::SELL, 997 };
	exchange1.cross(o11);

	std::cout << "\n\nAsk Qty @ 997 = 25\n";
	std::cout << "Asks:\n";
	for (auto &x : exchange1.asks)
	{
		std::cout << "Price: " << x.first << ", Qty: " << x.second.qty << "\n";
		for (auto &y : x.second.quotes)
			std::cout << "Trader Id: " << y.id << ", Order Id: " << y.oid << ", Qty: " << y.qty << "\n";
	}

	std::cout << std::endl;
}

void OrderbookTests::testExchangeCrossBuy1()
{
	cSide cSide1;
	Orderbook exchange1 = Orderbook();
	//	Prime Book
	exchange1.addBook2(1001, 1, Side::BUY, 999, 100, 0);
	exchange1.addBook2(1002, 1, Side::SELL, 1005, 100, 0);

	// Add some depth
	Order o3{ 1001, 2, 3, 'A', 100, Side::SELL, 1005 };
	Order o4{ 1001, 3, 4, 'A', 100, Side::SELL, 1006 };
	Order o5{ 1001, 4, 4, 'A', 100, Side::SELL, 1008 };

	Order o6{ 1002, 2, 3, 'A', 100, Side::BUY, 999 };
	Order o7{ 1002, 3, 4, 'A', 100, Side::BUY, 998 };
	Order o8{ 1002, 4, 4, 'A', 100, Side::BUY, 996 };

	exchange1.process(o3);
	exchange1.process(o4);
	exchange1.process(o5);
	exchange1.process(o6);
	exchange1.process(o7);
	exchange1.process(o8);

	std::cout << "Bids:\n";
	for (auto &x : exchange1.bids)
	{
		std::cout << "Price: " << x.first << ", Qty: " << x.second.qty << "\n";
		for (auto &y : x.second.quotes)
			std::cout << "Trader Id: " << y.id << ", Order Id: " << y.oid << ", Qty: " << y.qty << "\n";
	}
	std::cout << "\n\nAsks:\n";
	for (auto &x : exchange1.asks)
	{
		std::cout << "Price: " << x.first << ", Qty: " << x.second.qty << "\n";
		for (auto &y : x.second.quotes)
			std::cout << "Trader Id: " << y.id << ", Order Id: " << y.oid << ", Qty: " << y.qty << "\n";
	}

	// Incoming order takes out part of best ask : 1001-1
	// Impacts trades. tradeconfirms, and the ask book.

	Order o9{ 4001, 2, 10, 'A', 50, Side::BUY, 100000 };
	exchange1.cross(o9);

	std::cout << "\n\nAsk Qty reduced by 50\n";
	std::cout << "Asks:\n";
	for (auto &x : exchange1.asks)
	{
		std::cout << "Price: " << x.first << ", Qty: " << x.second.qty << "\n";
		for (auto &y : x.second.quotes)
			std::cout << "Trader Id: " << y.id << ", Order Id: " << y.oid << ", Qty: " << y.qty << "\n";
	}

	cSide1 = exchange1.trades[0].side == Side::BUY ? 'B' : 'S';
	std::cout << "\nTrade Book After: " << exchange1.trades.size() << "\n";
	std::cout << "First Order: \n";
	std::cout << "Resting Trader ID: " << exchange1.trades[0].restid << "\n";
	std::cout << "Resting Order ID: " << exchange1.trades[0].restoid << "\n";
	std::cout << "Resting Step: " << exchange1.trades[0].reststep << "\n";
	std::cout << "Incoming Trader ID: " << exchange1.trades[0].incid << "\n";
	std::cout << "Incomig Order ID: " << exchange1.trades[0].incoid << "\n";
	std::cout << "Incoming Step: " << exchange1.trades[0].incstep << "\n";
	std::cout << "Quantity: " << exchange1.trades[0].qty << "\n";
	std::cout << "Side: " << cSide1 << "\n";
	std::cout << "Price: " << exchange1.trades[0].price << "\n";

	cSide1 = exchange1.tradeconfirms[0].side == Side::BUY ? 'B' : 'S';
	std::cout << "\nTrade Confirms After: " << exchange1.tradeconfirms.size() << "\n";
	std::cout << "First Order: \n";
	std::cout << "Resting Trader ID: " << exchange1.tradeconfirms[0].restid << "\n";
	std::cout << "Resting Order ID: " << exchange1.tradeconfirms[0].restoid << "\n";
	std::cout << "Step: " << exchange1.tradeconfirms[0].reststep << "\n";
	std::cout << "Quantity: " << exchange1.tradeconfirms[0].qty << "\n";
	std::cout << "Side: " << cSide1 << "\n";
	std::cout << "Price: " << exchange1.tradeconfirms[0].price << "\n";

	// Incoming order takes out remainder of best ask : 1002-1
	// Incoming order takes out some of the next best ask : 1001-2
	// Impacts trades. tradeconfirms, and the bid book.
	exchange1.tradeconfirms.clear();
	Order o10{ 4001, 3, 12, 'A', 75, Side::BUY, 100000 };
	exchange1.cross(o10);

	std::cout << "\n\nAsk Qty reduced by 75\n";
	std::cout << "Asks:\n";
	for (auto &x : exchange1.asks)
	{
		std::cout << "Price: " << x.first << ", Qty: " << x.second.qty << "\n";
		for (auto &y : x.second.quotes)
			std::cout << "Trader Id: " << y.id << ", Order Id: " << y.oid << ", Qty: " << y.qty << "\n";
	}

	cSide1 = exchange1.trades[1].side == Side::BUY ? 'B' : 'S';
	std::cout << "\nTrade Book After first: " << exchange1.trades.size() << "\n";
	std::cout << "First Order: \n";
	std::cout << "Resting Trader ID: " << exchange1.trades[1].restid << "\n";
	std::cout << "Resting Order ID: " << exchange1.trades[1].restoid << "\n";
	std::cout << "Resting Step: " << exchange1.trades[1].reststep << "\n";
	std::cout << "Incoming Trader ID: " << exchange1.trades[1].incid << "\n";
	std::cout << "Incomig Order ID: " << exchange1.trades[1].incoid << "\n";
	std::cout << "Incoming Step: " << exchange1.trades[1].incstep << "\n";
	std::cout << "Quantity: " << exchange1.trades[1].qty << "\n";
	std::cout << "Side: " << cSide1 << "\n";
	std::cout << "Price: " << exchange1.trades[1].price << "\n";

	cSide1 = exchange1.trades[2].side == Side::BUY ? 'B' : 'S';
	std::cout << "\nTrade Book After second: " << exchange1.trades.size() << "\n";
	std::cout << "Second Order: \n";
	std::cout << "Resting Trader ID: " << exchange1.trades[2].restid << "\n";
	std::cout << "Resting Order ID: " << exchange1.trades[2].restoid << "\n";
	std::cout << "Resting Step: " << exchange1.trades[2].reststep << "\n";
	std::cout << "Incoming Trader ID: " << exchange1.trades[2].incid << "\n";
	std::cout << "Incomig Order ID: " << exchange1.trades[2].incoid << "\n";
	std::cout << "Incoming Step: " << exchange1.trades[2].incstep << "\n";
	std::cout << "Quantity: " << exchange1.trades[2].qty << "\n";
	std::cout << "Side: " << cSide1 << "\n";
	std::cout << "Price: " << exchange1.trades[2].price << "\n";

	cSide1 = exchange1.tradeconfirms[0].side == Side::BUY ? 'B' : 'S';
	std::cout << "\nTrade Confirms After 1: " << exchange1.tradeconfirms.size() << "\n";
	std::cout << "First Order: \n";
	std::cout << "Resting Trader ID: " << exchange1.tradeconfirms[0].restid << "\n";
	std::cout << "Resting Order ID: " << exchange1.tradeconfirms[0].restoid << "\n";
	std::cout << "Step: " << exchange1.tradeconfirms[0].reststep << "\n";
	std::cout << "Quantity: " << exchange1.tradeconfirms[0].qty << "\n";
	std::cout << "Side: " << cSide1 << "\n";
	std::cout << "Price: " << exchange1.tradeconfirms[0].price << "\n";

	cSide1 = exchange1.tradeconfirms[1].side == Side::BUY ? 'B' : 'S';
	std::cout << "\nTrade Confirms After 2: " << exchange1.tradeconfirms.size() << "\n";
	std::cout << "Second Order: \n";
	std::cout << "Resting Trader ID: " << exchange1.tradeconfirms[1].restid << "\n";
	std::cout << "Resting Order ID: " << exchange1.tradeconfirms[1].restoid << "\n";
	std::cout << "Step: " << exchange1.tradeconfirms[1].reststep << "\n";
	std::cout << "Quantity: " << exchange1.tradeconfirms[1].qty << "\n";
	std::cout << "Side: " << cSide1 << "\n";
	std::cout << "Price: " << exchange1.tradeconfirms[1].price << "\n";

	// Incoming order takes out remainder of best ask : 1001-2
	// Incoming order takes out next best ask : 1003-3 @ 1006
	// Incoming order adds new order at 1007
	// Impacts trades. tradeconfirms, and the bid book.
	exchange1.tradeconfirms.clear();
	Order o11{ 4001, 4, 15, 'A', 200, Side::BUY, 1007 };
	exchange1.cross(o11);

	std::cout << "\n\nBid Qty @ 1007 = 25\n";
	std::cout << "Bids:\n";
	for (auto &x : exchange1.bids)
	{
		std::cout << "Price: " << x.first << ", Qty: " << x.second.qty << "\n";
		for (auto &y : x.second.quotes)
			std::cout << "Trader Id: " << y.id << ", Order Id: " << y.oid << ", Qty: " << y.qty << "\n";
	}

	std::cout << std::endl;
}

void OrderbookTests::testExchangeOrdersToCsv(std::string filer)
{
	Orderbook exchange1 = Orderbook();

	Order o3{ 1001, 2, 3, 'A', 100, Side::SELL, 1005 };
	Order o4{ 1001, 3, 4, 'A', 100, Side::SELL, 1006 };
	Order o5{ 1001, 4, 4, 'A', 100, Side::SELL, 1008 };

	Order o6{ 1002, 2, 3, 'A', 100, Side::BUY, 999 };
	Order o7{ 1002, 3, 4, 'A', 100, Side::BUY, 998 };
	Order o8{ 1002, 4, 4, 'A', 100, Side::BUY, 996 };

	exchange1.addHistory(o3);
	exchange1.addHistory(o4);
	exchange1.addHistory(o5);
	exchange1.addHistory(o6);
	exchange1.addHistory(o7);
	exchange1.addHistory(o8);

	exchange1.ordersToCsv(filer);
}

void OrderbookTests::testExchangeTradesToCsv(std::string file1)
{
	Orderbook exchange1 = Orderbook();

	traderId restid1 = 1004;
	Id restoid1 = 123;
	Step reststep1 = 23;
	traderId incid1 = 5010;
	Id incoid1 = 468;
	Step incstep1 = 27;
	Qty qty1 = 150;
	Side side1 = Side::SELL;
	Prc price1 = 1099;
	exchange1.addTrade(restid1, restoid1, reststep1, incid1, incoid1, incstep1, qty1, side1, price1);

	restid1 = 1007;
	restoid1 = 986;
	reststep1 = 1028;
	incid1 = 5005;
	incoid1 = 10865;
	incstep1 = 1099;
	qty1 = 300;
	side1 = Side::BUY;
	price1 = 1106;
	exchange1.addTrade(restid1, restoid1, reststep1, incid1, incoid1, incstep1, qty1, side1, price1);

	exchange1.tradesToCsv(file1);
}

void OrderbookTests::testExchangeSipToCsv(std::string file1)
{
	Orderbook exchange1 = Orderbook();

	exchange1.addBook2(1001, 1, Side::BUY, 999, 100, 1);
	exchange1.addBook2(1001, 2, Side::BUY, 1000, 200, 2);
	exchange1.addBook2(1001, 3, Side::BUY, 1001, 300, 3);
	exchange1.addBook2(1001, 4, Side::BUY, 999, 200, 4);
	exchange1.addBook2(5001, 1, Side::SELL, 1005, 100, 5);
	exchange1.addBook2(5001, 2, Side::SELL, 1006, 200, 6);
	exchange1.addBook2(5001, 3, Side::SELL, 1007, 300, 7);
	exchange1.addBook2(5001, 4, Side::SELL, 1005, 200, 8);
	exchange1.bookTop2(23);

	exchange1.addBook2(5001, 5, Side::SELL, 1004, 600, 9);
	exchange1.bookTop(27);

	exchange1.sipToCsv(file1);
}