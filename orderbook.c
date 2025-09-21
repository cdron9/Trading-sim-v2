#include "types.h"
#include "orderbook.h"

#include <stdio.h>

#define MAX_ORDERS 100

void add_order_to_book(OrderBook* book, Order order) {
    if (order.orderType == BUY_LIMIT || order.orderType == BUY_MARKET) {
        // add to end of array
        book->buy_orders[book->buy_count] = order;
        book->buy_count++;

        // sort the array (highest price first for buy limit orders)
        sort_buy_orders(book);
        
    } else {
        // add to sell orders
        book->sell_orders[book->sell_count] = order;
        book->sell_count++;

        sort_sell_orders(book);
    }
}

// sorted in descending order, lowest (best) prices indexed from 0 up.
void sort_buy_orders(OrderBook* book) {
    // bubble sort
    for (int i = 0; i < book->buy_count - 1; i++) {
        for (int j = 0; j < book->buy_count - 1 - i; j++) {
            if (book->buy_orders[j].orderprice < book->buy_orders[j + 1].orderprice) {
                //swap
                Order temp = book->buy_orders[j];
                book->buy_orders[j] = book->buy_orders[j + 1];
                book->buy_orders[j + 1] = temp;
            }
        }
    }
}

void sort_sell_orders(OrderBook* book) {
    // bubble sort again for now 
    for (int i = 0; i < book->sell_count - 1; i++) {
        for (int j = 0; j < book->sell_count - 1 - i; j++) {
            if (book->sell_orders[j].orderprice > book->sell_orders[j + 1].orderprice) {
                // swapsies
                Order temp = book->sell_orders[j];
                book->sell_orders[j] = book->sell_orders[j + 1];
                book->sell_orders[j + 1] = temp;
            }
        }
    }
}

// leave market orders for now until sorting is implemented via tree or linked list
