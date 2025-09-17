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