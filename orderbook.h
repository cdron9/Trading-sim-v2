#ifndef ORDERBOOK_H
#define ORDERBOOK_H

#include "types.h"
// add order to the appropriate orderbook
void add_order_to_book(OrderBook* book, Order order);

// try to match and execute trades
void match_orders(OrderBook* book, User* user);

// execute single trade when orders match
void execute_trade(Order* buy_order, Order* sell_order, OrderBook* book, User* user);

void sort_buy_orders(OrderBook* book);

void sort_sell_orders(OrderBook* book);

int can_orders_match(Order* buy, Order* sell);


#endif