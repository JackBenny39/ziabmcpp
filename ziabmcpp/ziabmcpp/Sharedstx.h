// Sharedstx.h

#pragma once

#ifndef SHAREDSTX_H
#define SHAREDSTX_H

#include "stdafx.h"

#include <utility> 

using Prc = unsigned;
using Qty = unsigned;
using Id = unsigned;
using Step = unsigned;
using traderId = unsigned;
using exId = unsigned;

enum struct Side { BUY, SELL };

struct Order { traderId id; Id oid; Step step; char otype; Qty qty; Side side; Prc price; };
struct TConfirm { traderId restid; Id restoid; Step reststep; Qty qty; Side side; Prc price; };
struct TopOfBook { Step step; Prc bestbid; Qty bestbidsz; Prc bestask; Qty bestasksz; };





#endif