// Orderbook.cpp
// Orderbook class

#include "stdafx.h"

#include <fstream>
#include <iostream>

#include "Orderbook.h"

Orderbook::Orderbook() :
	orderSequence(0)
{
}

void Orderbook::addHistory(Order &q)
{
	history.emplace_back(ExOrder{ ++orderSequence, q.id, q.oid, q.step, q.otype, q.qty, q.side, q.price });
}

void Orderbook::addBook(traderId tid, Id id, Side side, Prc prc, Qty qty, Step step)
{
	auto b = side == Side::BUY ? &bids : &asks;
	if (b->count(prc) > 0)
	{
		b->at(prc).qty += qty;
		b->at(prc).ocnt++;
		b->at(prc).quotes.emplace_back(Quote{ tid, id, qty, prc, side, step });
	}
	else
		b->emplace(prc, Level{ qty, 1, Quotes{ Quote{ tid, id, qty, prc, side, step } } });
	auto l = b->find(prc);
	auto q = l->second.quotes.begin();
	lookup[std::make_pair(tid, id)] = std::make_tuple(b, l, q);
}

void Orderbook::addBook2(traderId tid, Id id, Side side, Prc prc, Qty qty, Step step)
{
	auto b = side == Side::BUY ? &bids : &asks;
	auto l = b->find(prc);
	if (l == b->end())
		l = b->emplace(std::make_pair(prc, Level{ 0, 0, Quotes{ } })).first;
	l->second.ocnt++;
	l->second.qty += qty;
	auto q = l->second.quotes.emplace(l->second.quotes.end(), Quote{ tid, id, qty, prc, side, step });
	lookup[std::make_pair(tid, id)] = std::make_tuple(b, l, q);
}

void Orderbook::remove(traderId tid, Id id, Qty qty)
{
	OrderId oid = std::make_pair(tid, id);
	auto& blq = lookup[oid];
	auto& b = std::get<0>(blq);
	auto& l = std::get<1>(blq);
	auto& q = std::get<2>(blq);
	l->second.qty -= qty;
	l->second.quotes.erase(q);
	l->second.ocnt--;
	if (!(l->second.ocnt))
		b->erase(l);
	lookup.erase(oid);
}

void Orderbook::modify(traderId tid, Id id, Qty qty)
{
	OrderId oid = std::make_pair(tid, id);
	auto& blq = lookup[oid];
	auto& b = std::get<0>(blq);
	auto& l = std::get<1>(blq);
	auto& q = std::get<2>(blq);
	l->second.qty -= qty;
	q->qty -= qty;
	if (!(q->qty))
	{
		l->second.quotes.erase(q);
		l->second.ocnt--;
		if (!(l->second.ocnt)) { b->erase(l); }
		lookup.erase(oid);
	}
}

void Orderbook::addTrade(traderId restid, Id restoid, Step reststep, traderId incid, Id incoid, Step incstep, Qty qty, Side side, Prc price)
{
	trades.emplace_back(ExTrade{ restid, restoid, reststep, incid, incoid, incstep, qty, side, price });
}

void Orderbook::confirmTrade(traderId restid, Id restoid, Step reststep, Qty qty, Side side, Prc price)
{
	tradeconfirms.emplace_back(TConfirm{ restid, restoid, reststep, qty, side, price });
}

void Orderbook::confirmModify(traderId restid, Id restoid, Step reststep, Qty qty, Side side)
{
	modifyconfirms.emplace_back(MConfirm{ restid, restoid, reststep, qty, side});
}

auto Orderbook::bid() { return bids.empty() ? std::make_tuple(Prc(0), Qty(0)) : std::make_tuple(bids.rbegin()->first, bids.rbegin()->second.qty); }
auto Orderbook::ask() { return asks.empty() ? std::make_tuple(Prc(0), Qty(0)) : std::make_tuple(asks.begin()->first, asks.begin()->second.qty); }

void Orderbook::process(Order &q)
{
	modifyconfirms.clear();
	if (q.otype == 'A')
	{
		if (q.side == Side::BUY)
		{
			if (q.price >= std::get<0>(ask()))
				cross(q);
			else
				addBook2(q.id, q.oid, q.side, q.price, q.qty, q.step);
		}
		else
		{
			if (q.price <= std::get<0>(bid()))
				cross(q);
			else
				addBook2(q.id, q.oid, q.side, q.price, q.qty, q.step);
		}
	}
	else
	{
		confirmModify(q.id, q.oid, q.step, q.qty, q.side);
		if (q.otype == 'C')
			remove(q.id, q.oid, q.qty);
		else
			modify(q.id, q.oid, q.qty);
	}
}

void Orderbook::cross(Order &q)
{
	tradeconfirms.clear();
	Prc best;
	if (q.side == Side::BUY)
	{
		while (q.qty > 0)
		{
			if ((best = std::get<0>(ask())))
			{
				if (q.price >= best)
				{ // Quote reference here!
					if (q.qty >= asks[best].quotes.front().qty)
					{
						confirmTrade(asks[best].quotes.front().id, asks[best].quotes.front().oid, q.step,
							asks[best].quotes.front().qty, asks[best].quotes.front().side, asks[best].quotes.front().prc);
						addTrade(asks[best].quotes.front().id, asks[best].quotes.front().oid, asks[best].quotes.front().step,
							q.id, q.oid, q.step, asks[best].quotes.front().qty, q.side, asks[best].quotes.front().prc);
						q.qty -= asks[best].quotes.front().qty;
						remove(asks[best].quotes.front().id, asks[best].quotes.front().oid, asks[best].quotes.front().qty);
					}
					else
					{
						confirmTrade(asks[best].quotes.front().id, asks[best].quotes.front().oid, q.step,
							q.qty, asks[best].quotes.front().side, asks[best].quotes.front().prc);
						addTrade(asks[best].quotes.front().id, asks[best].quotes.front().oid, asks[best].quotes.front().step,
							q.id, q.oid, q.step, q.qty, q.side, asks[best].quotes.front().prc);
						modify(asks[best].quotes.front().id, asks[best].quotes.front().oid, q.qty);
						break;
					}
				}
				else
				{
					addBook2(q.id, q.oid, q.side, q.price, q.qty, q.step);
					break;
				}
			}
			else
			{
				std::cout << "Ask Market Collapse with order: " << q.id << ":" << q.oid << "\n" << std::endl;
				break;
			}
		}
		
	}
	else
	{
		while (q.qty > 0)
		{
			if ((best = std::get<0>(bid())))
			{
				if (q.price <= best)
				{ // Quote reference here!
					if (q.qty >= bids[best].quotes.front().qty)
					{
						confirmTrade(bids[best].quotes.front().id, bids[best].quotes.front().oid, q.step,
							bids[best].quotes.front().qty, bids[best].quotes.front().side, bids[best].quotes.front().prc);
						addTrade(bids[best].quotes.front().id, bids[best].quotes.front().oid, bids[best].quotes.front().step,
							q.id, q.oid, q.step, bids[best].quotes.front().qty, q.side, bids[best].quotes.front().prc);
						q.qty -= bids[best].quotes.front().qty;
						remove(bids[best].quotes.front().id, bids[best].quotes.front().oid, bids[best].quotes.front().qty);
					}
					else
					{
						confirmTrade(bids[best].quotes.front().id, bids[best].quotes.front().oid, q.step,
							q.qty, bids[best].quotes.front().side, bids[best].quotes.front().prc);
						addTrade(bids[best].quotes.front().id, bids[best].quotes.front().oid, bids[best].quotes.front().step,
							q.id, q.oid, q.step, q.qty, q.side, bids[best].quotes.front().prc);
						modify(bids[best].quotes.front().id, bids[best].quotes.front().oid, q.qty);
						break;
					}
				}
				else
				{
					addBook2(q.id, q.oid, q.side, q.price, q.qty, q.step);
					break;
				}
			}
			else
			{
				std::cout << "Bid Market Collapse with order: " << q.id << ":" << q.oid << "\n" << std::endl;
				break;
			}
		}
	}
}

std::vector<TopOfBook>::iterator Orderbook::bookTop(Step step)
{
	auto bestbid = bid();
	auto bestask = ask();
	return tob.emplace(tob.end(), TopOfBook{ step, std::get<0>(bestbid), std::get<1>(bestbid), std::get<0>(bestask), std::get<1>(bestask) });
}

void Orderbook::bookTop2(Step step)
{
	auto bestbid = bid();
	auto bestask = ask();
	tob.emplace_back(TopOfBook{ step, std::get<0>(bestbid), std::get<1>(bestbid), std::get<0>(bestask), std::get<1>(bestask) });
}

void Orderbook::ordersToCsv(std::string &filename)
{
	char csd;
	std::ofstream csvfile;
	csvfile.open(filename);
	csvfile << "Sequence,TraderId,OrderId,Step,OrderType,Quantity,Side,Price\n";
	for (auto& x : history)
	{
		csd = x.side == Side::BUY ? 'B' : 'S';
		csvfile << x.exid << "," << x.id << "," << x.oid << "," << x.step << ","
				<< x.otype << "," << x.qty << "," << csd << "," << x.price << "\n";
	}
	csvfile.close();
}

void Orderbook::tradesToCsv(std::string &filename)
{
	char csd;
	std::ofstream csvfile;
	csvfile.open(filename);
	csvfile << "RestTraderId,RestOrderId,RestStep,IncTraderId,IncOrderId,IncStep,Quantity,Side,Price\n";
	for (auto& x : trades)
	{
		csd = x.side == Side::BUY ? 'B' : 'S';
		csvfile << x.restid << "," << x.restoid << "," << x.reststep << "," << x.incid << ","
				<< x.incoid << "," << x.incstep << "," << x.qty << "," << csd << "," << x.price << "\n";
	}
	csvfile.close();
}

void Orderbook::sipToCsv(std::string &filename)
{
	std::ofstream csvfile;
	csvfile.open(filename);
	csvfile << "Step,BestBidPrice,BestBidSize,BestAskPrice,BestAskSize\n";
	for (auto& x : tob)
		csvfile << x.step << "," << x.bestbid << "," << x.bestbidsz << "," << x.bestask << "," << x.bestasksz << "\n";
	csvfile.close();
}