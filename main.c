#include <stdio.h>
#include "types.h"
#include "ui.h"
#include "stocks.h"
#include "user.h"
#include "order.h"
#include "orderbook.h"

#define MAX_ORDERS 100

int main(void) {
    User user = initialise_user();
    Stock stocks[3];
    initialise_stocks(stocks);
    Order orders_array[MAX_ORDERS];

    OrderBook orderbooks[3];
    for (int i = 0; i <= 3; i++) {
        orderbooks[i].ticker = stocks[i].ticker;
        orderbooks[i].buy_count = 0;
        orderbooks[i].sell_count = 0;
        orderbooks[i].last_price = stocks[i].shareprice; // starts with stock price.
    }
    
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
                        case 1: orders_array[new_id] = order_create(&stocks[0], new_id); break;
                        case 2: orders_array[new_id] = order_create(&stocks[1], new_id); break;
                        case 3: orders_array[new_id] = order_create(&stocks[2], new_id); break;
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

                    switch (sell_choice) {
                        case 1: break;
                        case 2: break;
                        case 3: break;
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
    }
    
    return 0;
}