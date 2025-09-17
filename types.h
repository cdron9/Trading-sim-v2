#ifndef TYPES_H
#define TYPES_H

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
    Stock shareprice;
    Stock ticker;
    double quantity;
} Order;

#endif
