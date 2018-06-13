// BucketTests.h

#pragma once

#ifndef BUCKETTESTS_H
#define BUCKETTESTS_H

#include "stdafx.h"

#include <memory>
#include <set>

#include "Sharedstx.h"

#include "ZITrader.h"
#include "Taker.h"
#include "Informed.h"
#include "Provider.h"
#include "Provider5.h"
#include "MarketMaker.h"
#include "MarketMaker5.h"
#include "PennyJumper.h"

using cSide = char;

class BucketTests
{
public:
	BucketTests(std::vector<int> &, std::uniform_int_distribution<> &, std::mt19937 &);
	std::mt19937 engine;
	std::uniform_int_distribution<> distUint;
	std::uniform_real_distribution<> distUreal;
	std::vector<int> defaultVec;
	std::vector<std::shared_ptr<ZITrader>> bucket;
	int setMaxQ(int);
	void testInstances();
	void testZITrader();
	void testTaker();
	void testInformed();
	void testProvider();
	void testProvider5();
	void testMarketMaker();
	void testMarketMaker5();
	void testPJ();
};

#endif

