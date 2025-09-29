#include "ui.h"
#include "types.h"
#include "stocks.h"
#include <stdio.h>
#include <stdbool.h>
#include <ctype.h>
#include <string.h>
#include <stdlib.h>

void display_main_menu(Stock* stocks, User* user) {
    printf("\033[2J\033[H");
    printf("\n\n== MAIN MENU ==\n\n");
    printf("1. Create BUY order\n");
    printf("2. Create SELL order\n");
    printf("3. Show portfolio\n");
    printf("\n4. QUIT\n");

    // Display user cash and holdings summary
    printf("\nYour cash: $%.2f\n", user->cash);

    printf("\n== Current stock prices ==\n");
    for (int i = 0; i < 3; i++) {
        Stock* s = &stocks[i];
        printf("%s: $%.2f\n", s->ticker, s->shareprice);
    }
}

void display_sell_menu() {
    printf("\033[2J\033[H");
    printf("\n\n== SELL MENU ==\n\n");
    printf("Select a stock.\n\n");
    printf("1. TECH\n");
    printf("2. GOIL\n");
    printf("3. FOOD\n");
    printf("\n4. BACK\n");
}

void display_buy_menu(User* user) {
    printf("\033[2J\033[H");
    printf("\n\n== BUY MENU ==\n\n");
    printf("Select a stock.\n\n");
    printf("1. TECH\n");
    printf("2. GOIL\n");
    printf("3. FOOD\n");
    printf("\n4. BACK\n");

    // show user cash
    printf("Your cash: $%.2f\n", user->cash);
}


void display_portfolio_menu(User* user) {
    printf("\033[2J\033[H");
    printf("\n\n== PORTFOLIO ==\n\n");
    printf("User cash: $%.2f\n\n", user->cash);
    printf("User holdings:\n");
    for (int i = 0; i < 3; i++) {
        Stock* s = &user->holdings[i];
        float avg_price = (s->user_quantity > 0) ? (s->total_cost / s->user_quantity) : 0.0f;
        printf("%s: Quantity: %u, Avg Price: $%.2f\n", s->ticker, s->user_quantity, avg_price);
    }
    printf("\n1. BACK\n");
}

void display_order_accepted(const Order* order) {
    printf("\033[2J\033[H");
    printf("\n\n== ORDER ACCEPTED ==\n\n");
    printf("Order for %s accepted!\n", order->ticker);
    printf("Type: %s\n", (order->orderType == BUY_LIMIT || order->orderType == BUY_MARKET) ? "BUY" : "SELL");
    printf("Quantity: %.0f\n", order->quantity);
    printf("Price: $%.2f\n", order->orderprice);
    printf("\nPress ENTER to continue...\n");
    int c;
    while ((c = getchar()) != '\n' && c != EOF) {} // flush leftover input
    getchar();
}

int get_user_input(void) {
    char buffer[3];
    int choice;

    while (1) {
        if (!fgets(buffer, sizeof(buffer), stdin)) {
            // input error, try again
            continue;
        }

        // strip newline
        buffer[strcspn(buffer, "\n")] = '\0';

        // check that *every* character is a digit
        int valid = 1;
        for (int i = 0; buffer[i] != '\0'; i++) {
            if (!isdigit((unsigned char)buffer[i])) {
                valid = 0;
                break;
            }
        }

        if (!valid) {
            printf("Invalid input (letters/symbols not allowed).\n");
            continue;
        }

        choice = atoi(buffer);

        if (choice < 1 || choice > 9) {
            printf("Number out of range. Try again.\n");
            continue;
        }

        return choice; // success
    }
}

