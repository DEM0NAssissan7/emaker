#include "meals.h"
#include "prediction.h"

#include <stdio.h>

int main() {
    init_meal_array();
    enter_meal(7.2, 78.4, 2.5, 3.33, 86, 87); // Dec 22
    enter_meal(0, 202, 4.5, 4.17, 90, 95); // Dec 23
    enter_meal(0, 96, 2.2, 0, 96, 83);
    enter_meal(6.6, 72, 2, 0, 87, 91);
    enter_meal(4, 197.9, 4.5, 0, 96, 100);

    init_E_values();
    gradient_descent(100000000);
    return 0;
}