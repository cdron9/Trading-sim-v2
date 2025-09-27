#ifndef STOCKS_H
#define STOCKS_H

#include "types.h"

void initialise_stocks(Stock stocks[3]);

void update_recent_avg(Stock* stock);
void update_price_history(Stock* stock, double new_price);

#endif