#include <stdio.h>
#include "types.h"
#include "ui.h"
#include "stocks.h"
#include "user.h"
#include "order.h"
#include "orderbook.h"
#include "bot.h"

#define MAX_ORDERS 100
#define MAX_BOTS 20

int main(void) {
    User user = initialise_user();
    Stock stocks[3];
    initialise_stocks(stocks);
    Order orders_array[MAX_ORDERS];
    Bot trading_bots[MAX_BOTS];
    int num_active_bots = 10;

    OrderBook orderbooks[3];
    for (int i = 0; i < 3; i++) {
        orderbooks[i].ticker = stocks[i].ticker;
        orderbooks[i].buy_count = 0;
        orderbooks[i].sell_count = 0;
        orderbooks[i].last_price = stocks[i].shareprice; // starts with stock price.
    }

    initialise_bots(trading_bots, num_active_bots);
    
    int quit = 0;
    
    while (!quit) {
        display_main_menu();
        int main_choice = get_user_input();
        
        switch (main_choice) { 
            case 1: {   // buy menu
                int buy_quit = 0;
                while (!buy_quit) {
                    display_buy_menu();
                    int buy_choice = get_user_input();
                    int new_id = order_getID();
                    
                    switch (buy_choice) {
                        case 1: {
                            Order new_order = order_create_buy(&stocks[0], new_id);
                            orders_array[new_id] = new_order;
                            add_order_to_book(&orderbooks[0], orders_array[new_id]);
                            display_order_accepted(&orders_array[new_id]);
                            break;
                        }
                        case 2: {
                            Order new_order = order_create_buy(&stocks[1], new_id);
                            orders_array[new_id] = new_order;
                            add_order_to_book(&orderbooks[1], orders_array[new_id]);
                            display_order_accepted(&orders_array[new_id]);
                            break;
                        }
                        case 3: {
                            Order new_order = order_create_buy(&stocks[2], new_id);
                            orders_array[new_id] = new_order;
                            add_order_to_book(&orderbooks[2], orders_array[new_id]);
                            display_order_accepted(&orders_array[new_id]);
                            break;
                        }
                        case 4: buy_quit = 1; break;
                        default: printf("Invalid choice\n");
                    }
                }
                break;
            }
            
            case 2: { // sell menu
                int sell_quit = 0;
                while (!sell_quit) {
                    display_sell_menu();
                    int sell_choice = get_user_input();
                    int new_id = order_getID();

                    switch (sell_choice) {
                        case 1: 
                            if (user.holdings[0].user_quantity <= 0) {
                                printf("\n[ERROR] You do not have any TECH shares to sell.\n");
                                break;
                            }
                            orders_array[new_id] = order_create_sell(&stocks[0], new_id);
                            add_order_to_book(&orderbooks[0], orders_array[new_id]);
                            display_order_accepted(&orders_array[new_id]);
                            match_orders(stocks, &orderbooks[0], &user);
                            break;
                        case 2: 
                            if (user.holdings[1].user_quantity <= 0) {
                                printf("\n[ERROR] You do not have any GOIL shares to sell.\n");
                                break;
                            }
                            orders_array[new_id] = order_create_sell(&stocks[1], new_id);
                            add_order_to_book(&orderbooks[1], orders_array[new_id]);
                            display_order_accepted(&orders_array[new_id]);
                            match_orders(stocks, &orderbooks[1], &user);
                            break;
                        case 3: 
                            if (user.holdings[2].user_quantity <= 0) {
                                printf("\n[ERROR] You do not have any FOOD shares to sell.\n");
                                break;
                            }
                            orders_array[new_id] = order_create_sell(&stocks[2], new_id);
                            add_order_to_book(&orderbooks[2], orders_array[new_id]);
                            display_order_accepted(&orders_array[new_id]);
                            match_orders(stocks, &orderbooks[2], &user);
                            break;
                        case 4: sell_quit = 1; break;
                        default: printf("Invalid choice\n");
                    }
                }
                break;
            }
            
            case 3: { // portfolio
                int portfolio_quit = 0;
                while (!portfolio_quit) {
                    display_portfolio_menu(&user);
                    int portfolio_choice = get_user_input();
                    
                    switch (portfolio_choice) {
                        case 1: portfolio_quit = 1; break;
                        default: printf("Invalid choice\n");
                    }
                }
                break;
            }
            
            case 4: { // Quit
                quit = 1;
                break;
            }
            
            default:
                printf("Invalid choice\n");
        }
        // run bots every tick (or as desired)
        run_bot_simulation_step(trading_bots, num_active_bots, stocks, orderbooks);

        // process all orderbook matching at once 
        for (int i = 0; i < 3; i++) {
            match_orders(stocks, &orderbooks[i], &user); // shoudl match pending bot orders asw
        }
    }
    
    return 0;
}