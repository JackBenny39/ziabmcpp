// ZITrader.h

#pragma once

#ifndef ZITRADER_H
#define ZITRADER_H

#include "stdafx.h"

#include <list>			// std::list
#include <string>		// std::string
#include <tuple>        // std::tuple

using quote_t = std::tuple<std::string, int, char, int, char, int>;


class ZITrader
{
public:
	ZITrader(const std::string &, const int);
	int orderSize;
	std::string traderType;
	std::string traderId;
	quote_t makeAddQuote(int, char, int);
	std::list<quote_t> quoteCollector;
private:
	int quoteSequence;
};

#endif