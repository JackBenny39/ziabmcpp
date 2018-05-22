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
	void confirmCancel(Id);
	void confirmTrade(TConfirm &);
	void processSignal(TopOfBook &, Step, double, double, double);
	Prc chooseP(Side, Prc, double);
	void bulkCancel(Step);
	double delta;
};

#endif
