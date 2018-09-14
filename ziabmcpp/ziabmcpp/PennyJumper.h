// PennyJumper.h

#pragma once

#ifndef PENNYJUMPER_H
#define PENNYJUMPER_H

#include "stdafx.h"

#include "Sharedstx.h"

#include <random>

class PennyJumper
{
public:
	PennyJumper(const int, const int, const Prc);

	traderId tId;
	Qty orderSize;
	char traderType;
	Prc mpi;

	Order makeCancelQuote(Order &, Step);
	void confirmTrade(TConfirm &);
	void processSignal(TopOfBook &, Step, double, std::mt19937 &, std::uniform_real_distribution<> &);

	std::vector<Order> quoteCollector, cancelCollector, askBook, bidBook;
private:
	Id quoteSequence;
};

#endif

