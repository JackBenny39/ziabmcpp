// Provider.h

#pragma once

#ifndef PROVIDER_H
#define PROVIDER_H

#include "stdafx.h"

#include "Sharedstx.h"

#include <random>
#include <unordered_map>
#include <vector>

class Provider
{
public:
	Provider(const Step, const int, const int, const double, const Prc);

	Step arrInt;
	traderId tId;
	Qty orderSize;
	char traderType;
	Prc mpi;
	double delta;

	Order makeCancelQuote(Order &, Step);
	void confirmTrade(TConfirm &);
	void bulkCancel(Step, std::mt19937 &, std::uniform_real_distribution<> &);
	Order processSignal(TopOfBook &, Step, double, double, std::mt19937 &, std::uniform_real_distribution<> &);
	Prc chooseP(Side, Prc, double, std::mt19937 &, std::uniform_real_distribution<> &);
	std::unordered_map<Id, Order> localBook;
	std::vector<Order> cancelCollector;
private:
	Id quoteSequence;
};

#endif
