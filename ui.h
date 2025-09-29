#ifndef UI_H
#define UI_H

#include "types.h"

void display_main_menu(Stock* stocks, User* user); // fixing funcitons with calls to structs.
void display_buy_menu(User* user);
void display_sell_menu();
void display_portfolio_menu(User* user);
void display_order_accepted(const Order* order);


// input 
int get_user_input();

#endif
