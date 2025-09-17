#ifndef UI_H
#define UI_H

#include "types.h"

void display_main_menu(); // fixing funcitons with calls to structs.
void display_buy_menu();
void display_sell_menu();
void display_portfolio_menu(User* user);


// input 
int get_user_input();

#endif
