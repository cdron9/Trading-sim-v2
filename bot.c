#include <stdio.h>
#include <stdlib.h>
#include "types.h"
#include "orderbook.h"
#include "order.h"

void initialise_bots(Bot* bots, int count) {
    for (int i = 0; i < count; i++) {
        bots[i].bot_id = i;
        bots[i].cash = 5000 + (rand() % 10000); // 5 to 15k starting cash

        // random strategy assignment
        bots[i].strategy = rand() % 5; // 0-4 maps to enum values

        // randomise risk profiles
        bots[i].risk_tolerance = 0.1 + (rand() % 70) / 100.0;       // 0.1-0.8
        bots[i].position_size_pct = 0.05 + (rand() % 20) / 100.0;   // 5-25%
        bots[i].price_sensitivity = 0.01 + (rand() % 49) / 1000.0;  // 1-5%

        bots[i].cooldown_timer = 0;
        bots[i].decision_freq = 5 + rand() % 15;    // 5-20 ticks

        // make holdings empty
        for (int j = 0; j < 3; j++) {
            bots[i].holdings[j] = 0;
        }
    }
}

void run_bot_simulation_step(Bot* bots, int bot_count, Stock* stocks, OrderBook* books) {
    for (int i = 0; i < bot_count; i++) {
        Order* bot_order = bot_make_decision(&bots[i], bot_count, stocks, books); // logic to be written later, will be hefty and based on literally all data points.

        if (bot_order != NULL) {
            // send to correct orderbook
            int stock_index = find_stock_index(bot_order->ticker); // create fucntion for finding index. will be quite simple
            add_order_to_book(&books[stock_index], *bot_order);

            printf("Bot %d created order: %s %.0f shares of %s at $%.2f\n", i, (bot_order->orderType <= 1) ? "BUY" : "SELL",
            bot_order->quantity, bot_order->ticker, bot_order->orderprice);

            free(bot_order);
        }
    }   
}

Order* bot_make_decision(Bot* bot, int bot_count, Stock* stocks, OrderBook* books) {
   if (bot->cooldown_timer > 0) {
    bot->cooldown_timer--;
    return NULL; // bot cant act this tick
   }

   if (bot->strategy == MOMENTUM) {
    return momentum_strategy(bot, stocks, books);
   }
   // other strategies cont
}

Order* momentum_strategy(Bot* bot, Stock* stocks, OrderBook* books) {
    // select stock for analysis stand in for now at 0
    Stock* target_stock = &stocks[0];

    for (int stock_index = 0; stock_index < 3; stock_index++) {
        if (target_stock->shareprice > target_stock->recent_avg) {
            // price trending up -- create buy order
            if (bot->cash > target_stock->shareprice * 10) {    // can afford least 10 shares
                return order_create_bot_buy(bot, target_stock);
            }
        } else if (target_stock->shareprice < target_stock->recent_avg) {
            // price trend down -- create sell order
            if (bot->holdings[stock_index] > 0) {
                return order_create_bot_sell(bot, target_stock); // number = stock index. 
        }
    }

    return NULL; // no action this tick
}