#include "types.h"
#include "stocks.h"
#include <stdlib.h>

void initialise_stocks(Stock stocks[3]) {
    int min = 150;
    int max = 300;
    int initial_quantity = 50000;

   // TECH
    stocks[0].quantity_available = initial_quantity;
    stocks[0].shareprice = (rand() % (max - min + 1)) + min;
    stocks[0].ticker = "TECH";

    // GOIL
    stocks[1].quantity_available = initial_quantity;
    stocks[1].shareprice = (rand() % (max - min + 1)) + min;
    stocks[1].ticker = "GOIL";

    // FOOG
    stocks[2].quantity_available = initial_quantity;
    stocks[2].shareprice = (rand() % (max - min + 1)) + min;
    stocks[2].ticker = "FOOD";
}

void update_price_history(Stock* stock, double new_price) {
    stock->price_history[stock->history_index] = new_price;

    stock->history_index = (stock->history_index + 1) % 50;  // 50 == hsotry buffer size

    if (stock->history_count < 50) {
        stock->history_count++;
    }

    stock->shareprice = new_price;
    update_recent_avg(stock);
}

void update_recent_avg(Stock* stock) {
    if (stock->history_count < 10) {
        stock->recent_avg = stock->shareprice; // not enough price hsitory for accurate calc
        return;
    }

    double sum = 0;
    for (int i = 0; i < 10; i++) {
        int index = (stock->history_index -1 -i + 50) % 50;
        sum += stock->price_history[index];
    }
    stock->recent_avg = sum / 10.0;
}
