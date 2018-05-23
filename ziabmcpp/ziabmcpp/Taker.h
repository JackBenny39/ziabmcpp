// Taker.h

#pragma once

#ifndef TAKER_H
#define TAKER_H

#include "stdafx.h"

#include "ZITrader.h"

class Taker : public ZITrader
{
public:
	Taker(const int, const int);
	void processSignal(Step, double, std::mt19937 &, std::uniform_real_distribution<> &);
};

#endif
