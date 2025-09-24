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

typedef enum {
    MOMENTUM,      // buy rising sell falling
    MEAN_REVERSION, // buy dip sell spike
    SNIPER,         // patient limit orders close to fv
    SCALPER,        // quick small trades
    RANDOM          // day trading guru (liquidity provider lol)
} TradingStrategy;

typedef struct {
    int bot_id;
    double cash;
    int holdings[3];

    TradingStrategy strategy;

    // risk profiling (randomised per bot) potentally range will differ based on strategy
    double risk_tolerance;      // 0.1 = conservative, 0.8 = agro
    double position_size_pct;   // % of cash willing to use per trade
    double price_sensitivity;   // how much price movement triggers action

    // timing
    int cooldown_timer;         // ticks until can trade again
    int decision_freq;          // how often bot considers trading
} Bot;

typedef struct {
    double shareprice;
    int quantity_available;
    char* ticker;

    // market behaviour params
    double volatility;          // 0.01 / 1% as typical price swing
    double base_fair_value;     // what the bots consider fair price
    double trend_strength;      // current momentum (-1 to +1)

    // activity tracking
    double recent_volume;       // for bots so interest can be gauged
    double price_history[50];   // last 50 trade prices
    double recent_avg;          // price history / amount of price points in history
    int history_index;
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
