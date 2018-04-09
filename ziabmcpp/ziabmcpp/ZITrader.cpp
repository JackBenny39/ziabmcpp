// ZITrader.cpp
// ZITrader class

#include "stdafx.h"

#include <string>

#include "ZITrader.h"

ZITrader::ZITrader(const std::string &name, const int maxq)
{
	traderId = name;
	orderSize = maxq;
	quoteSequence = 0;
	traderType = "ZITrader";
}

quote_t ZITrader::makeAddQuote(int timestamp, char side, int price)
{
	std::string orderId = traderId + "_" + std::to_string(++quoteSequence);
	return std::make_tuple(orderId, timestamp, 'A', orderSize, side, price);
}