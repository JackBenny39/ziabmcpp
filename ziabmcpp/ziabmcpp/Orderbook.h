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

struct Quote { traderId id; Id oid; Qty qty; Prc prc; Side side; };
using Quotes = std::list<Quote>;

struct Level {Qty qty; int ocnt; Quotes quotes; };
using BookSide = std::map<Prc, Level>;

using BLQ = std::tuple<BookSide*, BookSide::iterator, Quotes::iterator>;
using Lookup = std::map<std::pair<traderId, Id>, BLQ>;

struct Execution {Id id; Prc prc; Qty executed; Qty remaining;};


class Orderbook
{
public:
	Orderbook();
	std::vector<ExOrder> history;

	BookSide bids, asks;

	Lookup lookup;
	
	void addHistory(Order &);
	void addBook(traderId, Id, Side, Prc, Qty);
	void addBook2(traderId, Id, Side, Prc, Qty);
	void remove(traderId, Id, Qty);
	void modify(traderId, Id, Qty);
	std::vector<Execution> cross(Side, Prc, Qty);
	auto bid();
	auto ask();
private:
	exId orderSequence;
};

#endif