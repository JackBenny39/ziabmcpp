// Provider5.h

#pragma once

#ifndef PROVIDER5_H
#define PROVIDER5_H

#include "stdafx.h"

#include "Sharedstx.h"

#include <random>
#include <unordered_map>
#include <vector>

class Provider5
{
public:
	Provider5(const Step, const traderId, const Qty, const double);

	Step arrInt;
	traderId tId;
	Qty orderSize;
	static const char traderType;
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

