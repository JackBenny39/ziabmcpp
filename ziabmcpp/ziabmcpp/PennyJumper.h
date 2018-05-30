// PennyJumper.h

#pragma once

#ifndef PENNYJUMPER_H
#define PENNYJUMPER_H

#include "stdafx.h"

#include "ZITrader.h"

class PennyJumper : public ZITrader
{
public:
	PennyJumper(const int, const int, const Prc);
	Order makeCancelQuote(Order &, Step);
	std::vector<Order> cancelCollector;
	void confirmTrade(TConfirm &);
	void processSignal(TopOfBook &, Step, double, std::mt19937 &, std::uniform_real_distribution<> &);
	Prc mpi;
	Order askQuote, bidQuote, nullAsk, nullBid;
};

#endif

