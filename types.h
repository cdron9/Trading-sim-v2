#ifndef TYPES_H
#define TYPES_H
#define MAX_ORDERS 100

typedef enum {
    BUY_LIMIT,
    SELL_LIMIT,
    BUY_MARKET,
    SELL_MARKET
} OrderType;

typedef enum {
    MAIN_MENU,
    BUY_MENU,
    SELL_MENU,
    PORTFOLIO_MENU
} ScreenState;

typedef struct {
    double shareprice;
    int quantity_available;
    char* ticker;
} Stock;

typedef struct {
    double cash;
} User;

typedef struct {
    int id;
    double orderprice;
    char* ticker;
    double quantity;
    OrderType orderType; // buy, sell @ limit || market
} Order;

typedef struct {
    char* ticker;

    Order buy_orders[MAX_ORDERS];       // all buy orders for the stock 
    Order sell_orders[MAX_ORDERS];      // all sell orders for the stock

    int buy_count;                      // how many buy orders currently
    int sell_count;                     // How many sell orders currently

    double last_price;                  // Price of most recent trade
} OrderBook;

#endif
