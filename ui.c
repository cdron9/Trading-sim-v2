#include "ui.h"
#include "types.h"
#include "stocks.h"
#include <stdio.h>
#include <stdbool.h>
#include <ctype.h>
#include <string.h>
#include <stdlib.h>

void display_main_menu() {
    printf("\033[2J\033[H");
    printf("\n\n== MAIN MENU ==\n\n");
    printf("1. Create BUY order\n");
    printf("2. Create SELL order\n");
    printf("3. Show portfolio\n");
    printf("4. QUIT\n");
}

void display_buy_menu() {
    printf("\033[2J\033[H");
    printf("\n\n== BUY MENU ==\n\n");
    printf("Select a stock.\n\n");
    printf("1. TECH\n");
    printf("2. GOIL\n");
    printf("3. FOOD\n");
    printf("4. BACK\n");
}

void display_portfolio_menu(User* user) {
    printf("\033[2J\033[H");
    printf("\n\n== PORTFOLIO ==\n\n");
    printf("User cash: $%.2f\n\n", user->cash);
    printf("User holdings:\n");
    // Display holdings logic here
    printf("\n1. BACK\n");
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

