// Informed.cpp
// Informed class

#include "stdafx.h"


#include "Informed.h"

Informed::Informed(const int tnum, const int maxq, Side side)
	: ZITrader(tnum, maxq), side(side)
{
	traderType = 'I';
	price = side == Side::BUY ? 2000000 : 0;
}

void Informed::processSignal(Step step)
{
	quoteCollector.emplace_back(makeAddQuote(step, side, price));
}