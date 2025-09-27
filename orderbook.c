#include <stdio.h>
#include "types.h"
#include "orderbook.h"
#include "stocks.h"
#include "bot.h"

#include <stdio.h>

#define MAX_ORDERS 100


void add_order_to_book(OrderBook* book, Order order) {
    printf("[DEBUG] Adding order: %s %s %.0f @ $%.2f (id=%d)\n", 
        (order.orderType == BUY_LIMIT || order.orderType == BUY_MARKET) ? "BUY" : "SELL", 
        order.ticker, order.quantity, order.orderprice, order.id);
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

void execute_trade(Stock* stock, Order* buy, Order* sell, OrderBook* book, User* user) {
    double trade_quantity = (buy->quantity < sell->quantity) ?
                            buy->quantity : sell->quantity;

    double trade_price = sell->orderprice; // seller was there first
    printf("[DEBUG] Executing trade: BUY id=%d, SELL id=%d, qty=%.0f, price=%.2f\n", buy->id, sell->id, trade_quantity, trade_price);

    printf("TRADE: %.0f shares at $%.2f\n", trade_quantity, trade_price);

    // update order quantities
    buy->quantity -= trade_quantity;
    sell->quantity -= trade_quantity;

    // TODO: Update user accounts, stock last price
    // track last price
    book->last_price = trade_price;

    int stock_index = find_stock_index(book->ticker);
    printf("[DEBUG] Stock index for %s: %d\n", book->ticker, stock_index);
    // Only update user if the order has a valid user order ID (>= 0)
    if (user != NULL) {
        // User is buyer
        if (buy->id >= 0) {
            printf("[DEBUG] User is BUYER. Before: cash=%.2f, qty=%.2f, avg=%.2f\n", user->cash, user->holdings[stock_index].user_quantity, user->holdings[stock_index].order_price);
            user->cash -= (trade_quantity * trade_price);
            user->holdings[stock_index].user_quantity += trade_quantity;
            user->holdings[stock_index].order_price += trade_price;
            printf("[DEBUG] User is BUYER. After: cash=%.2f, qty=%.2f, avg=%.2f\n", user->cash, user->holdings[stock_index].user_quantity, user->holdings[stock_index].order_price);
        }
        // User is seller
        if (sell->id >= 0) {
            printf("[DEBUG] User is SELLER. Before: cash=%.2f, qty=%.2f, avg=%.2f\n", user->cash, user->holdings[stock_index].user_quantity, user->holdings[stock_index].order_price);
            user->cash += (trade_quantity * trade_price);
            user->holdings[stock_index].user_quantity -= trade_quantity;
            user->holdings[stock_index].order_price -= trade_price;
            printf("[DEBUG] User is SELLER. After: cash=%.2f, qty=%.2f, avg=%.2f\n", user->cash, user->holdings[stock_index].user_quantity, user->holdings[stock_index].order_price);
        }
    }
}

//matching engine
void match_orders(Stock* stock, OrderBook* book, User* user) {
    // Keep matching as long as possible
    while (book->buy_count > 0 && book->sell_count > 0) {
        Order* best_buy = &book->buy_orders[0];
        Order* best_sell = &book->sell_orders[0];
        if (!can_orders_match(best_buy, best_sell)) {
            break;
        }
        execute_trade(stock, best_buy, best_sell, book, user);
        // Support for partially filled orders:
        // Only remove an order if its quantity is now <= 0 (fully filled).
        if (best_buy->quantity <= 0) {
            for (int i = 0; i < book->buy_count - 1; i++) {
                book->buy_orders[i] = book->buy_orders[i + 1];
            }
            book->buy_count--;
        }
        if (best_sell->quantity <= 0) {
            for (int i = 0; i < book->sell_count - 1; i++) {
                book->sell_orders[i] = book->sell_orders[i + 1];
            }
            book->sell_count--;
        }
        // If either order was only partially filled, it remains at the front of the book for the next match.
    }
}
