#include <stdio.h>
#include "types.h"
#include "user.h"
#include "stocks.h"

User initialise_user() {
    User user;
    user.cash = 10000;
    // Initialize holdings for TECH, GOIL, FOOD
    user.holdings[0].ticker = "TECH";
    user.holdings[0].user_quantity = 0;
    user.holdings[0].order_price = 0;
    user.holdings[1].ticker = "GOIL";
    user.holdings[1].user_quantity = 0;
    user.holdings[1].order_price = 0;
    user.holdings[2].ticker = "FOOD";
    user.holdings[2].user_quantity = 0;
    user.holdings[2].order_price = 0;
    return user;
}