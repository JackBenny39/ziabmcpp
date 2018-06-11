// MarketMaker.h

#pragma once

#ifndef MARKETMAKER_H
#define MARKETMAKER_H

#include "stdafx.h"

#include "Provider.h"

struct CFlow { traderId id; Step step; int64_t cashFlow; unsigned position; };

class MarketMaker : public Provider
{
public:
	MarketMaker(const Step, const int, const int, const double, const int, const int);
	void confirmTrade(TConfirm &); // need this? declared in Provider
	void processSignal(TopOfBook &, Step, double, double, std::mt19937 &, std::uniform_real_distribution<> &);
	std::vector<CFlow> cashFlowCollector;
};

#endif
