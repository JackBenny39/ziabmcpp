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
	ZITrader(const int, const int);
	int orderSize;
	char traderType;
	traderId tId;
	Order makeAddQuote(int, char, int);
	std::vector<Order> quoteCollector;
private:
	int quoteSequence;
};

#endif