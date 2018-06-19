// Provider.h

#pragma once

#ifndef PROVIDER_H
#define PROVIDER_H

#include "stdafx.h"

#include "ZITrader.h"

class Provider : public ZITrader
{
public:
	Provider(const Step, const int, const int, const double, const Prc);
	Provider(const Step, const int, const int, const double, const int, const int);
	void confirmTrade(TConfirm &) override;
	void processSignal(TopOfBook &, Step, double, double, std::mt19937 &, std::uniform_real_distribution<> &) override;
};

#endif
