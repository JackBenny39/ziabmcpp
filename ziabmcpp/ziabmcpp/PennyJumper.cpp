// PennyJumper.cpp
// PennyJumper class

#include "stdafx.h"

#include "PennyJumper.h"

PennyJumper::PennyJumper(const Step arr, const int tnum, const int maxq, const Prc mpi)
	: ZITrader(arr, tnum, maxq, mpi) { traderType = 'J'; }

void PennyJumper::confirmTrade(TConfirm &c)
{
	if (c.side == Side::BUY)
		bidBook.clear();
	else
		askBook.clear();
}

void PennyJumper::processSignal(TopOfBook &tob, Step step, double qTake, std::mt19937 &engine, std::uniform_real_distribution<> &dist)
{
	Order q;
	quoteCollector.clear();
	cancelCollector.clear();
	if (tob.bestask - tob.bestbid > mpi) {
		if (dist(engine) < qTake) {
			if (!bidBook.empty()) {
				Order& qq = bidBook[0];
				if ((qq.price < tob.bestbid) || (qq.qty < tob.bestbidsz)) {
					cancelCollector.emplace_back(makeCancelQuote(qq, step));
					bidBook.clear();
				}
			}
			if (bidBook.empty()) {
				q = makeAddQuote(step, Side::BUY, tob.bestbid + mpi);
				quoteCollector.push_back(q);
				bidBook.push_back(q);
			}
		} 
		else {
			if (!askBook.empty()) {
				Order& qq = askBook[0];
				if ((qq.price > tob.bestask) || (qq.qty < tob.bestasksz)) {
					cancelCollector.emplace_back(makeCancelQuote(qq, step));
					askBook.clear();
				}
			}
			if (askBook.empty()) {
				q = makeAddQuote(step, Side::SELL, tob.bestask - mpi);
				quoteCollector.push_back(q);
				askBook.push_back(q);
			}
		}
	}
	else {
		if (!bidBook.empty()) {
			Order& qq = bidBook[0];
			if ((qq.price < tob.bestbid) || (qq.qty < tob.bestbidsz)) {
				cancelCollector.emplace_back(makeCancelQuote(qq, step));
				bidBook.clear();
			}
		}
		if (!askBook.empty()) {
			Order& qq = askBook[0];
			if ((qq.price > tob.bestask) || (qq.qty < tob.bestasksz)) {
				cancelCollector.emplace_back(makeCancelQuote(qq, step));
				askBook.clear();
			}
		}
	}
}
