// OrderbookTests.h

#pragma once

#ifndef ORDERBOOKTESTS_H
#define ORDERBOOKTESTS_H

#include "stdafx.h"

#include "Sharedstx.h"

#include "Orderbook.h"

using cSide = char;

class OrderbookTests
{
public:
	OrderbookTests() = default;
	void testExchangeAddHistory();
	void testExchangeAddBook2();
	void testOrderbookRemove();
	void testOrderbookModify();
	void testExchangeAddTrade();
	void testExchangeConfirmTrade();
	void testExchangeConfirmModify();
	void testExchangeBookTop();
	void testExchangeBookTop2();
	void testExchangeProcess();
	void testExchangeCrossCrash();
	void testExchangeCrossSell1();
	void testExchangeCrossBuy1();
	void testExchangeCrossSell1r();
	void testExchangeCrossBuy1r();
	void testExchangeCrossTime();
	void testExchangeOrdersToCsv(std::string);
	void testExchangeTradesToCsv(std::string);
	void testExchangeSipToCsv(std::string);
};

#endif

