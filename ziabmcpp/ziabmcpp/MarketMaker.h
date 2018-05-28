// Provider.h

#pragma once

#ifndef MARKETMAKER_H
#define MARKETMAKER_H

#include "stdafx.h"

#include <unordered_map>

#include "Provider.h"

struct CFlow { traderId id; Step step; uint64_t cashFlow; unsigned position; };

class MarketMaker : public Provider
{
public:
	MarketMaker(const int, const int, const double, const int, const int);
	void confirmTrade(TConfirm &);
	void processSignal(TopOfBook &, Step, double, double, std::mt19937 &, std::uniform_real_distribution<> &);
	std::vector<CFlow> cashFlowCollector;
	int numQuotes;
	int quoteRange;
	unsigned position;
	uint64_t cashFlow;
};

#endif
