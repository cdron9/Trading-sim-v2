#include <stdio.h>
#include "types.h"
#include "user.h"
#include "stocks.h"

User initialise_user() {
    User user;
    user.cash = 10000;

    return user;
}