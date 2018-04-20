// Sharedstx.h

#pragma once

#ifndef SHAREDSTX_H
#define SHAREDSTX_H

#include "stdafx.h"

#include <utility> 

using traderId = std::pair<char, int>;
struct Order { traderId id; int oid; int step; char otype; int qty; char side; int price; };

#endif