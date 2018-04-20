// ZITrader.cpp
// ZITrader class

#include "stdafx.h"

#include <string>

#include "ZITrader.h"

ZITrader::ZITrader(const int tnum, const int maxq)
{
	traderType = 'Z'; 
	tId = traderId{ traderType, tnum };
	orderSize = maxq;
	quoteSequence = 0;
}

Order ZITrader::makeAddQuote(int timestamp, char side, int price)
{
	return Order{ tId, ++quoteSequence, timestamp, 'A', orderSize, side, price };
}