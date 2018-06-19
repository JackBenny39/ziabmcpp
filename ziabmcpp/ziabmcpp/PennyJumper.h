// PennyJumper.h

#pragma once

#ifndef PENNYJUMPER_H
#define PENNYJUMPER_H

#include "stdafx.h"

#include "ZITrader.h"

class PennyJumper : public ZITrader
{
public:
	PennyJumper(const Step, const int, const int, const Prc);
	void confirmTrade(TConfirm &) override;
	void processSignal(TopOfBook &, Step, double, std::mt19937 &, std::uniform_real_distribution<> &) override;
};

#endif

