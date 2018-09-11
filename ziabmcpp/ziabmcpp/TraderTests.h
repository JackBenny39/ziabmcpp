// TraderTests.h

#pragma once

#ifndef TRADERTESTS_H
#define TRADERTESTS_H

#include "stdafx.h"

#include <set>

#include "Sharedstx.h"

//#include "ZITrader.h"
//#include "Taker.h"
//#include "Informed.h"
#include "Provider.h"
#include "Provider5.h"
//#include "MarketMaker.h"
//#include "MarketMaker5.h"
//#include "PennyJumper.h"

using cSide = char;

class TraderTests
{
public:
	TraderTests(std::vector<int> &, std::uniform_int_distribution<> &, std::mt19937 &);
	std::mt19937 engine;
	std::vector<int> defaultVec;
	std::uniform_real_distribution<> distUreal;
	std::uniform_int_distribution<> distUint;
	int seed;
	int setMaxQ(int);
//	void testZITrader();
//	void testTaker();
//	void testInformed();
	void testProvider();
	void testProvider5();
//	void testMarketMaker();
//	void testMarketMaker5();
//	void testPJ();
};

#endif
