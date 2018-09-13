// Informed.h

#pragma once

#ifndef INFORMED_H
#define INFORMED_H

#include "stdafx.h"

#include "Sharedstx.h"

#include <random>
#include <set>

using stepset = std::set<Step>;

class Informed
{
public:
	Informed(const int, const int, Side, const unsigned, const unsigned, std::mt19937 &, std::uniform_int_distribution<> &);

	Step arrInt;
	traderId tId;
	Qty orderSize;
	char traderType;
	Side side; // must precede price
	Prc price;
	stepset steps;
	std::set<Step>::iterator it;

	void makeSteps(const unsigned, const unsigned, std::mt19937 &, std::uniform_int_distribution<> &);
	Order processSignal(Step);

private:
	Id quoteSequence;
};

#endif
