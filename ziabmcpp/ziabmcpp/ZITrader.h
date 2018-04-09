// ZITrader.h

#pragma once

#ifndef ZITRADER_H
#define ZITRADER_H

#include "stdafx.h"

#include <list>			// std::list
#include <random>		// std::random_device
#include <string>		// std::string
#include <tuple>        // std::tuple
#include <vector>		// std::vector

using quote_t = std::tuple<std::string, int, char, int, char, int>;


class ZITrader
{
public:
	ZITrader(const std::string &, const int);
	//	std::string getTraderId() const;
	//	std::string getTraderType() const;
	std::string traderType;
	std::string traderId;
	std::vector<int> defaultVec;
	int orderSize;
	void setQuantity(int);
	int getQuantity() const;
	quote_t makeAddQuote(int, char, int);
	std::list<quote_t> quoteCollector;
private:
	//	std::string traderId;
	//	int orderSize;
	int quoteSequence;
	std::random_device random_device;
	typedef std::mt19937 Mers;
	Mers eng;
	std::uniform_int_distribution<int> dist;
};

#endif