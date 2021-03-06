// ZITrader.h

#pragma once

#ifndef ZITRADER_H
#define ZITRADER_H

#include "stdafx.h"

#include "Sharedstx.h"

#include <random>
#include <set>
#include <unordered_map>
#include <vector>

using stepset = std::set<Step>;
struct CFlow { traderId id; Step step; int64_t cashFlow; int position; };


class ZITrader
{
public:
	ZITrader(const Step, const int, const int, const Prc); // ZITrader, Taker, PennyJumper
	ZITrader(const int, const int, Side, const unsigned, const unsigned, std::mt19937 &, std::uniform_int_distribution<> &); //Informed
	ZITrader(const Step, const int, const int, const double, const Prc); // Provider, Provider5
	ZITrader(const Step, const int, const int, const double, const int, const int); // Provider, MarketMaker, MarketMaker5

	virtual void processSignal(Step, double, std::mt19937 &, std::uniform_real_distribution<> &);
	virtual void processSignal(Step);
	virtual void processSignal(TopOfBook &, Step, double, double, std::mt19937 &, std::uniform_real_distribution<> &);
	virtual void processSignal(TopOfBook &, Step, double, std::mt19937 &, std::uniform_real_distribution<> &);

	virtual void confirmTrade(TConfirm &);
	virtual Prc chooseP(Side, Prc, double, std::mt19937 &, std::uniform_real_distribution<> &);

	virtual ~ZITrader() = default;

	Step arrInt;
	traderId tId;
	Qty orderSize;
	char traderType;
	Side side; // must precede price
	Prc price, mpi;
	double delta;
	int numQuotes, quoteRange;
	int position;
	int64_t cashFlow;
	stepset steps;
	std::set<Step>::iterator it;
	Order makeAddQuote(Step, Side, Prc);
	Order makeCancelQuote(Order &, Step);
	void confirmCancel(Id);
	void bulkCancel(Step, std::mt19937 &, std::uniform_real_distribution<> &);
	void makeSteps(const unsigned, const unsigned, std::mt19937 &, std::uniform_int_distribution<> &);
	std::vector<Order> quoteCollector;
	std::unordered_map<Id, Order> localBook;
	std::vector<Order> cancelCollector, askBook, bidBook;
	std::vector<CFlow> cashFlowCollector;
private:
	Id quoteSequence;
};

#endif