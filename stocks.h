#ifndef STOCKS_H
#define STOCKS_H

#include "types.h"

void initialise_stocks(Stock stocks[3]);

void update_recent_avg(Stock* stock);
void update_price_history(Stock* stock, double new_price);
double calculate_current_fair_value(const Stock* stock);
void update_trend_strength(Stock* stock);


#endif