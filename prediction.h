#define learning_rate 0.002

extern double E_carbs;
extern double E_dextrose;
extern double E_protein;
extern double E_insulin;

void gradient_descent(int iterations);
void init_E_values();