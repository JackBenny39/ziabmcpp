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
	MarketMaker5(const int, const int, const double, const int, const int);
	std::discrete_distribution<int> askP;
	std::discrete_distribution<int> bidP;
	void makeProbs();
//	std::discrete_distribution<int> makeAskProb();
//	std::discrete_distribution<int> makeBidProb();
	void processSignal(TopOfBook &, Step, double, double, std::mt19937 &, std::uniform_real_distribution<> &);

};

#endif
