// MakretMaker5.h

#pragma once

#ifndef MARKETMAKER5_H
#define MARKETMAKER5_H

#include "stdafx.h"

#include <vector>

#include "MarketMaker.h"

class MarketMaker5 : public MarketMaker
{
public:
	MarketMaker5(const Step, const int, const int, const double, const int, const int);
	void processSignal(TopOfBook &, Step, double, double, std::mt19937 &, std::uniform_real_distribution<> &) override;
};

#endif
