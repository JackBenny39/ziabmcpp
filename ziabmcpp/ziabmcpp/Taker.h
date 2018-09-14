// Taker.h

#pragma once

#ifndef TAKER_H
#define TAKER_H

#include "stdafx.h"

#include "Sharedstx.h"

#include <random>

class Taker
{
public:
	Taker(const Step, const traderId, const Qty);

	Step arrInt;
	traderId tId;
	Qty orderSize;
	static const char traderType;

	Order processSignal(Step, double, std::mt19937 &, std::uniform_real_distribution<> &);

private:
	Id quoteSequence;
};

#endif
