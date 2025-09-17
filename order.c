#include <stdio.h>

#include "types.h"
#include "order.h"

Order order_create(Stock* specific_stock, int id) {
    Order order;
    order.id = id;
    order.ticker = specific_stock->ticker;

    printf("Enter desired price per share: ");
    double price;
    scanf("%lf", &price);
    order.orderprice = price;

    printf("Enter desired amount of shares: ");
    double quantity;
    scanf("%lf", &quantity);
    order.quantity = quantity;

    return order;
}

int order_getID() {
    static int currentID = 0;
    return currentID++; // return current then increment.
}