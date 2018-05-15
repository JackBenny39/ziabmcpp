// Orderbook.h

#pragma once

#ifndef ORDERBOOK_H
#define ORDERBOOK_H

#include "Sharedstx.h"

#include <list>			// std::list
#include <map>			// std::map
#include <string>		// std::string
#include <tuple>        // std::tuple
#include <unordered_map>        // std::unordered_map
#include <vector>        // std::vector

struct ExOrder { exId exid; traderId id; Id oid; Step step; char otype; Qty qty; Side side; Prc price; };
struct ExTrade { traderId restid; Id restoid; Step reststep; traderId incid; Id incoid; Step incstep; Qty qty; Side side; Prc price; };
struct TConfirm { traderId restid; Id restoid; Step reststep; Qty qty; Side side; Prc price; };
struct MConfirm { traderId restid; Id restoid; Step reststep; Qty qty; Side side; };

struct Quote { traderId id; Id oid; Qty qty; Prc prc; Side side; };
using Quotes = std::list<Quote>;

struct Level {Qty qty; int ocnt; Quotes quotes; };
using BookSide = std::map<Prc, Level>;

using BLQ = std::tuple<BookSide*, BookSide::iterator, Quotes::iterator>;
using OrderId = std::pair<traderId, Id>;
using Lookup = std::map<OrderId, BLQ>;

struct Execution {Id id; Prc prc; Qty executed; Qty remaining;};


class Orderbook
{
public:
	Orderbook();
	std::vector<ExOrder> history;
	std::vector<ExTrade> trades;
	std::vector<TConfirm> tradeconfirms;
	std::vector<MConfirm> modifyconfirms;
	std::vector<TopOfBook> tob;

	BookSide bids, asks;

	Lookup lookup;
	
	void addHistory(Order &);
	void addTrade(traderId, Id, Step, traderId, Id, Step, Qty, Side, Prc);
	void confirmTrade(traderId, Id, Step, Qty, Side, Prc);
	void confirmModify(traderId, Id, Step, Qty, Side);
	void addBook(traderId, Id, Side, Prc, Qty);
	void addBook2(traderId, Id, Side, Prc, Qty);
	void remove(traderId, Id, Qty);
	void modify(traderId, Id, Qty);
	void process(Order &);
	void cross(Order &);
//	std::vector<Execution> cross(Side, Prc, Qty);
	auto bid();
	auto ask();
	std::vector<TopOfBook>::iterator bookTop(Step);
	void bookTop2(Step step);

private:
	exId orderSequence;
};

#endif