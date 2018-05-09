// Taker.h

#pragma once

#ifndef TAKER_H
#define TAKER_H

#include "stdafx.h"

#include "ZITrader.h"

class Taker : public ZITrader
{
public:
	Taker(const int, const int, const char);
	void processSignal(Step, double, double);
};

#endif
