#include "meals.h"
#include "prediction.h"

#include <math.h>
#include <stdio.h>
#include <stdlib.h>
#include <time.h>

// Initial E values
double E_carbs = 5;
double E_dextrose = 5;
double E_protein = 1.8;
double E_insulin = 60;

double random_double() {
    // Seed the random number generator with the current time
    srand((unsigned int)time(NULL) ^ (rand() % 1000)); 

    // Generate a random number between 0 and RAND_MAX, then normalize it to [0, 1]
    return (double)rand() / (double) RAND_MAX;
}

void init_E_values() {
    E_carbs *= random_double();
    E_dextrose *= random_double();
    E_protein *= random_double();
    E_insulin *= random_double();
}
float get_predicted_sugar(Meal* m) {
    return m->before_sugar +
        (m->carbs * E_carbs) +
        (m->protein * E_protein) -
        (m->insulin * E_insulin) +
        (m->dextrose * E_dextrose);
}

float get_avg_percent_error() {
    float retval = 0;
    for(int i = 0; i < meal_count; i++) {
        float after_sugar = meals[i].after_sugar;
        retval += fabsf((get_predicted_sugar(&meals[i]) - after_sugar) / after_sugar) * 100;
    }
    return retval / meal_count;
}


void gradient_descent(int iterations) {
    // Iterate for a fixed number of steps
    for (int iter = 0; iter < iterations; iter++) {
        // Initialize gradients to 0
        double grad_E_carbs = 0;      // Gradient of the error with respect to E_carbs
        double grad_E_dextrose = 0;   // Gradient of the error with respect to E_dextrose
        double grad_E_protein = 0;    // Gradient of the error with respect to E_protein
        double grad_E_insulin = 0;    // Gradient of the error with respect to E_insulin

        // Loop over all meals to calculate the gradients
        for (int i = 0; i < meal_count; i++) {
            Meal* m = &meals[i];                          // Get the current meal
            float predicted = get_predicted_sugar(m);     // Predicted sugar level
            float actual = m->after_sugar;               // Actual sugar level
            float error = predicted - actual;            // Error (difference between predicted and actual)

            // Calculate the gradient contributions for each parameter
            grad_E_carbs += (error / actual) * m->carbs;      // Gradient for E_carbs
            grad_E_dextrose += (error / actual) * m->dextrose; // Gradient for E_dextrose
            grad_E_protein += (error / actual) * m->protein;  // Gradient for E_protein
            grad_E_insulin -= (error / actual) * m->insulin;  // Gradient for E_insulin (negative because insulin reduces sugar)
        }

        // Average the gradients over all meals (to ensure scaling is consistent)
        grad_E_carbs /= meal_count;
        grad_E_dextrose /= meal_count;
        grad_E_protein /= meal_count;
        grad_E_insulin /= meal_count;

        // Update the parameters using the gradient descent formula
        E_carbs -= learning_rate * grad_E_carbs;        // Update E_carbs
        E_dextrose -= learning_rate * grad_E_dextrose;  // Update E_dextrose
        E_protein -= learning_rate * grad_E_protein;    // Update E_protein
        E_insulin -= learning_rate * grad_E_insulin;    // Update E_insulin

        // Print progress for debugging and monitoring
        printf("Iteration %d: Error = %.4f, E_carbs = %.4f, E_dextrose = %.4f, E_protein = %.4f, E_insulin = %.4f\n",
               iter + 1, get_avg_percent_error(), E_carbs, E_dextrose, E_protein, E_insulin);
    }
}