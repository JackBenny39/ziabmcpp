// Provider.h

#pragma once

#ifndef PROVIDER_H
#define PROVIDER_H

#include "stdafx.h"

#include <unordered_map>

#include "ZITrader.h"

class Provider : public ZITrader
{
public:
	Provider(const int, const int, const double);
	std::unordered_map<Id, Order> localBook;
	Order makeCancelQuote(Order &, Step);
	std::vector<Order> cancelCollector;
	void confirmCancel(Id);
	void confirmTrade(TConfirm &);
	void processSignal(TopOfBook &, Step, double, double, std::mt19937 &, std::uniform_real_distribution<> &);
	Prc chooseP(Side, Prc, double, std::mt19937 &, std::uniform_real_distribution<> &);
	void bulkCancel(Step, std::mt19937 &, std::uniform_real_distribution<> &);
	double delta;
};

#endif
