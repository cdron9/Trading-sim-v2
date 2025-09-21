#include <stdio.h>

#include "types.h"
#include "order.h"
#include "ui.h"

Order order_create(Stock* specific_stock, int id) {
    Order order;
    order.id = id;
    order.ticker = specific_stock->ticker;

    printf("\033[2J\033[H");
    printf("\n\n== ORDER MENU ==\n\n");
    
    printf("Enter desired price per share: ");
    double price;
    scanf("%lf", &price);
    order.orderprice = price;

    printf("\nEnter desired amount of shares: ");
    double quantity;
    scanf("%lf", &quantity);
    order.quantity = quantity;

    return order;
}

int order_getID() {
    static int currentID = 0;
    return currentID++; // return current then increment.
}