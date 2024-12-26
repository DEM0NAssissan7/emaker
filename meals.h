typedef struct {
    float carbs;
    float protein;
    float insulin;
    float dextrose;
    float before_sugar;
    float after_sugar;
} Meal;

#define MEALSIZE sizeof(Meal)

int meal_count;
Meal* meals;

void enter_meal(float carbs, float protein, float insulin, float dextrose, float before_sugar, float after_sugar);
void init_meal_array();