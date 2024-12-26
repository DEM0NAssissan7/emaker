#include "meals.h"
#include <stdlib.h>

int meal_count = 0;

void enter_meal(float carbs, float protein, float insulin, float dextrose, float before_sugar, float after_sugar) {
    Meal m;
    m.carbs = carbs;
    m.protein = protein;
    m.insulin = insulin;
    m.dextrose = dextrose;
    m.before_sugar = before_sugar;
    m.after_sugar = after_sugar;

    // Add to meals array
    meals = realloc(meals, (meal_count+1) * MEALSIZE);
    meals[meal_count++] = m;
}

void init_meal_array() {
    meals = malloc(MEALSIZE);
}