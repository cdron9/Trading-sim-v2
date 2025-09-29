#ifndef BOT_H
#define BOT_H
#include "types.h"

void initialise_bots(Bot* bots, int count);
void run_bot_simulation_step(Bot* bots, int bot_count, Stock* stock, OrderBook* books);
Order* bot_make_decision(Bot *bots, Stock* stocks, OrderBook* books);
int find_stock_index(const char* ticker);

// order creation 
Order* bot_create_buy_order(Bot* bot, Stock* stock);
Order* bot_create_sell_order(Bot* bot, Stock* stock);
// bot logic for order nums
double bot_calculate_order_quantity(Bot* bot, Stock* stock);
double bot_calculate_buy_price(Bot* bot, Stock* stock);
double bot_calculate_sell_price(Bot* bot, Stock* stock);

// strategy logic
Order* momentum_strategy(Bot* bot, Stock* stocks, OrderBook* books);
Order* random_strategy(Bot* bot, Stock* stocks, OrderBook* books);



#endif