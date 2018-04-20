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

using Id = std::string;
using Qty = unsigned;
using Prc = unsigned;

struct ExOrder { int exid; traderId id; int oid; int step; char otype; int qty; char side; int price; };

enum struct Side { BUY, SELL };

struct Quote { Id id; Qty qty; };
using Quotes = std::list<Quote>;

struct Level {Qty qty; Quotes quotes;};
using BookSide = std::map<Prc, Level>;

using BLQ = std::tuple<BookSide*, BookSide::iterator, Quotes::reverse_iterator>;
using Lookup = std::unordered_map<Id, BLQ>;

struct Execution {Id id; Prc prc; Qty executed; Qty remaining;};


class Orderbook
{
public:
	Orderbook();
	std::vector<ExOrder> history;
	Lookup lookup;
	BookSide bids, asks;
	void addHistory(Order &);
	void add(Id, Side, Prc, Qty);
	void modify(Id, Qty);
	std::vector<Execution> cross(Side, Prc, Qty);
	auto bid();
	auto ask();
private:
	int orderSequence;
};

#endif