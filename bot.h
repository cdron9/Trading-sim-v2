#ifndef BOT_H
#define BOT_H
#include "types.h"

void initlialise_bots(Bot* bots, int count);
void run_bot_simulation_step(Bot* bots, int bot_count, Stock* stock, OrderBook* books);
Order bot_make_decision(Bot *bots[], Stock* stocks, OrderBook* books);

#endif