// Informed.h

#pragma once

#ifndef INFORMED_H
#define INFORMED_H

#include "stdafx.h"

#include "ZITrader.h"

class Informed : public ZITrader
{
public:
	Informed(const int, const int, Side);
	void processSignal(Step, double, double);
	Side side;
	Prc price;
};

#endif
