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
    stocks[0].base_fair_value = stocks[0].shareprice;
    stocks[0].volatility = 0.025; // 2.5% for TECH
    stocks[0].current_fair_value = calculate_current_fair_value(&stocks[0]);
    stocks[0].trend_strength = (stocks[0].shareprice - stocks[0].recent_avg) / stocks[0].recent_avg;

    // GOIL
    stocks[1].quantity_available = initial_quantity;
    stocks[1].shareprice = (rand() % (max - min + 1)) + min;
    stocks[1].ticker = "GOIL";
    stocks[1].base_fair_value = stocks[1].shareprice;
    stocks[1].volatility = 0.017; // 1.7% for GOIL
    stocks[1].current_fair_value = calculate_current_fair_value(&stocks[1]);
    stocks[1].trend_strength = (stocks[1].shareprice - stocks[1].recent_avg) / stocks[1].recent_avg;

    // FOOD
    stocks[2].quantity_available = initial_quantity;
    stocks[2].shareprice = (rand() % (max - min + 1)) + min;
    stocks[2].ticker = "FOOD";
    stocks[2].base_fair_value = stocks[2].shareprice;
    stocks[2].volatility = 0.01; // 1% for FOOD
    stocks[2].current_fair_value = calculate_current_fair_value(&stocks[2]);
    stocks[2].trend_strength = (stocks[2].shareprice - stocks[2].recent_avg) / stocks[2].recent_avg;
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

double calculate_current_fair_value(const Stock* stock) {
    // Simple weighted average of base fair value and recent average price
    double weight_base = 0.5;
    double weight_recent = 0.5;
    return (weight_base * stock->base_fair_value) + (weight_recent * stock->recent_avg);
}

void update_trend_strength(Stock* stock) {
    if (stock->recent_avg > 0) {
        stock->trend_strength = (stock->shareprice - stock->recent_avg) / stock->recent_avg;
        // Optionally clamp to [-1, 1]
        if (stock->trend_strength > 1.0) stock->trend_strength = 1.0;
        if (stock->trend_strength < -1.0) stock->trend_strength = -1.0;
    } else {
        stock->trend_strength = 0.0;
    }
}

