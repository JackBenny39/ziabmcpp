// Provider5.h

#pragma once

#ifndef PROVIDER5_H
#define PROVIDER5_H

#include "stdafx.h"

#include "Provider.h"

class Provider5 : public Provider
{
public:
	Provider5(const Step, const int, const int, const double, const Prc);
	void processSignal(TopOfBook &, Step, double, double, std::mt19937 &, std::uniform_real_distribution<> &) override;
	Prc chooseP(Side, Prc, double, std::mt19937 &, std::uniform_real_distribution<> &) override;
};

#endif

