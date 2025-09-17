#ifndef ORDER_H
#define ORDER_H

#include "types.h"

Order order_create(Stock* specific_stock, int id); // MAX_ORDERS = 100
int order_getID();

#endif