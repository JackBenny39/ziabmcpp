// ZITrader.h

#pragma once

#ifndef ZITRADER_H
#define ZITRADER_H

#include "stdafx.h"

#include "Sharedstx.h"

#include <vector>		// std::vector


class ZITrader
{
public:
	ZITrader(const int, const int, const char);
	Qty orderSize;
	char traderType;
	traderId tId;
	Order makeAddQuote(Step, Side, Prc);
	std::vector<Order> quoteCollector;
private:
	Id quoteSequence;
};

#endif