// Informed.h

#pragma once

#ifndef INFORMED_H
#define INFORMED_H

#include "stdafx.h"

#include "ZITrader.h"

class Informed : public ZITrader
{
public:
	Informed(const int, const int, Side, const unsigned, const unsigned, std::mt19937 &, std::uniform_int_distribution<> &);
	void processSignal(Step) override;
};

#endif
