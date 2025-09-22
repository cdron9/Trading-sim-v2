#ifndef ORDER_H
#define ORDER_H

#include "types.h"

Order order_create(Stock* specific_stock, int id); // MAX_ORDERS = 100
Order order_create_sell(Stock* specific_stock, int id);
int order_getID();

#endif