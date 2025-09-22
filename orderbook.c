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

int can_orders_match(Order* buy, Order* sell) {
    // market orders always match
    if (buy->orderType == BUY_MARKET || sell->orderType == SELL_MARKET) {
        return 1;
    }

    if (buy->orderprice >= sell->orderprice) {
        return 1;
    }

    return 0; // no match
}

void execute_trade(Order* buy, Order* sell, OrderBook* book, User* user) {
    double trade_quantity = (buy->quantity < sell->quantity) ?
                            buy->quantity : sell->quantity;

    double trade_price = sell->orderprice; // seller was there first

    printf("TRADE: %.0f shares at $%.2f\n", trade_quantity, trade_price);

    // update order quantities
    buy->quantity -= trade_quantity;
    sell->quantity -= trade_quantity;

    // TODO: Update user accounts, stock last price
    // track last price
    book->last_price = trade_price;

    // update user account
    user->cash -= (trade_quantity * trade_price);
}

//matching engine
void match_orders(OrderBook* book, User* user) {
    // Need least one buy and one sel
    if (book->buy_count == 0 || book->sell_count == 0) {
        return; // no matching possible
    }

    // get best orders from index 0 post sort
    Order* best_buy = &book->buy_orders[0];     // highest price buyer
    Order* best_sell = &book->sell_orders[0];   // Lowest price seller

    // check if can match 
    if (can_orders_match(best_buy, best_sell)) {
        execute_trade(best_buy, best_sell, book, user);
        // TODO: handle partially filled orders
        // TODO: remove fully filled orders
    }
}
