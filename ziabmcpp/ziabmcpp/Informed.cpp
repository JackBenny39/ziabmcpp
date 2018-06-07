// Informed.cpp
// Informed class

#include "stdafx.h"


#include "Informed.h"

Informed::Informed(const int tnum, const int maxq, Side side)
	: ZITrader(tnum, maxq, side) { traderType = 'I'; }

void Informed::processSignal(Step step)
{
	quoteCollector.emplace_back(makeAddQuote(step, side, price));
}