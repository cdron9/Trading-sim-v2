#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>
#include "types.h"
#include "orderbook.h"
#include "order.h"
#include "bot.h"

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

        // assign 33% of bots holdings randomly
        if (rand() % 3 == 0) {
            for (int j = 0; j < 3; j++) {
                bots[i].holdings[j] = rand() % 20;
            }
        }
    }
}


void run_bot_simulation_step(Bot* bots, int bot_count, Stock* stocks, OrderBook* books) {
    for (int i = 0; i < bot_count; i++) {
        Order* bot_order = bot_make_decision(&bots[i], stocks, books);

        if (bot_order != NULL) {

            int stock_index = find_stock_index(bot_order->ticker);

            if (stock_index >= 0) {  // valid ticker found
                add_order_to_book(&books[stock_index], *bot_order);

          printf("Bot %d created order: %s %.0f shares of %s at $%.2f\n", 
              i, (bot_order->orderType <= 1) ? "BUY" : "SELL",
              bot_order->quantity, bot_order->ticker, bot_order->orderprice);
            } else {
                printf("Error: Invalid ticker %s\n", bot_order->ticker);
            }

            free(bot_order);
        }
    }   
}

int find_stock_index(const char* ticker) {
    if (strcmp(ticker, "TECH") == 0) return 0;
    if (strcmp(ticker, "GOIL") == 0) return 1;
    if (strcmp(ticker, "FOOD") == 0) return 2;
    
    return -1;  // Invalid ticker
}

Order* bot_make_decision(Bot* bot, Stock* stocks, OrderBook* books) {
   if (bot->cooldown_timer > 0) {
    bot->cooldown_timer--;
    return NULL; // bot cant act this tick
   }

   switch (bot->strategy) {
       case MOMENTUM:
           return momentum_strategy(bot, stocks, books);
       case RANDOM:
           return random_strategy(bot, stocks, books);
       // TODO: add other strategies here
       default:
           return momentum_strategy(bot, stocks, books);
   }
}


Order* random_strategy(Bot* bot, Stock* stocks, OrderBook* books) {
    int stock_index = rand() % 3;
    Stock* s = &stocks[stock_index];
    int action = rand() % 2; // 0 = buy, 1 = sell
    if (action == 0 && bot->cash > s->shareprice * 2) {
        return bot_create_buy_order(bot, s);
    } else if (action == 1 && bot->holdings[stock_index] > 0) {
        return bot_create_sell_order(bot, s);
    }
    return NULL;
}


Order* momentum_strategy(Bot* bot, Stock* stocks, OrderBook* books) {
    for (int stock_index = 0; stock_index < 3; stock_index++) {
        Stock* s = &stocks[stock_index];

        // buy if strong positive trend and enough cash
        if (s->trend_strength > 0.3 && bot->cash > s->shareprice * 5) {
            return bot_create_buy_order(bot, s);
        }

        // sell if strong negative trend and holdings exist
        if (s->trend_strength < -0.3 && bot->holdings[stock_index] > 0) {
            return bot_create_sell_order(bot, s);
        }
    }
    return NULL; // no action this tick
}

double bot_calculate_order_quantity(Bot* bot, Stock* stock) {
    // redo using psitionsizepct which varies between bots
    double base_quantity = (bot->cash * bot->position_size_pct) / stock->shareprice;

    // add risk tolerance for additional variance and accuracy
    double risk_multiplier = 0.5 + bot->risk_tolerance;

    return fmax(1, base_quantity * risk_multiplier);
}

double bot_calculate_buy_price(Bot* bot, Stock* stock) {
    double base_price = stock->shareprice;

    double price_variance = stock->volatility * bot->risk_tolerance;
    double random_factor = (rand() % 100 - 50) / 1000.0; // -0.05 - +0.05.

    return base_price * (1.0 + price_variance + random_factor);
}

double bot_calculate_sell_price(Bot* bot, Stock* stock) {
    if (bot->strategy == MOMENTUM && stock->shareprice < stock->recent_avg) {
        // panic sell and accept discount
        double discount = stock->volatility * bot->risk_tolerance;
        return stock->shareprice * (1.0 - discount);
    }

    return stock->shareprice * (1.0 + stock->volatility * 0.5);
}

Order* bot_create_buy_order(Bot* bot, Stock* stock) {
    Order* order = malloc(sizeof(Order));
    order->id = -1; // Mark as bot order
    order->ticker = stock->ticker;
    order->orderType = BUY_LIMIT;
    order->quantity = bot_calculate_order_quantity(bot, stock);
    order->orderprice = bot_calculate_buy_price(bot, stock);
    return order;
}

Order* bot_create_sell_order(Bot* bot, Stock* stock) {
    Order* order = malloc(sizeof(Order));
    order->id = -1; // Mark as bot order
    order->ticker = stock->ticker;
    order->orderType = SELL_LIMIT;
    order->quantity = bot_calculate_order_quantity(bot, stock);
    order->orderprice = bot_calculate_sell_price(bot, stock);
    return order;
}