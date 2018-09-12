// MarketMaker.h

#pragma once

#ifndef MARKETMAKER_H
#define MARKETMAKER_H

#include "stdafx.h"

#include "Sharedstx.h"

#include <cstdint>
#include <random>
#include <unordered_map>
#include <vector>


class MarketMaker
{
public:
	MarketMaker(const Step, const int, const int, const double, const int, const int);

	Step arrInt;
	traderId tId;
	Qty orderSize;
	char traderType;
	double delta;
	int numQuotes, quoteRange, position;
	int64_t cashFlow;

	Order makeCancelQuote(Order &, Step);
	void confirmTrade(TConfirm &);
	void bulkCancel(Step, std::mt19937 &, std::uniform_real_distribution<> &);
	void processSignal(TopOfBook &, Step, double, double, std::mt19937 &, std::uniform_real_distribution<> &);

	std::unordered_map<Id, Order> localBook;
	std::vector<CFlow> cashFlowCollector;
	std::vector<Order> cancelCollector;
	std::vector<Order> quoteCollector;

private:
	Id quoteSequence;
};

#endif
