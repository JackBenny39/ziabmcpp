// Taker.h

#pragma once

#ifndef TAKER_H
#define TAKER_H

#include "stdafx.h"

#include <string>		// std::string

#include "ZITrader.h"

class Taker : public ZITrader
{
public:
	Taker(const std::string &, const int);
	void processSignal(int, double, double);
};

#endif
