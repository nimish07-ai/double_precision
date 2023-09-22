#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <stdint.h>

// Define your custom float type
struct CustomFloat {
    uint32_t mantissa; // 4 bytes for the mantissa
    int16_t exponent;  // 2 bytes for the exponent
};

int main() {
    int size = 10;
    int k = 100;

    // Create 100x100 matrices
    double dm[size][size];
    struct CustomFloat fm[size][size];

    // Open the file for reading
    FILE *file = fopen("random_numbers.txt", "r");
    if (file == NULL) {
        printf("Error opening file for reading.\n");
        return 1;
    }

    // Read values from the file into both matrices simultaneously
    for (int i = 0; i < size; i++) {
        for (int j = 0; j < size; j++) {
            fscanf(file, "%lf", &dm[i][j]);

            // Convert the double value to your custom float
            fm[i][j].mantissa = *(uint32_t*)&dm[i][j];
            fm[i][j].exponent = (int16_t)floor(log2(fabs(dm[i][j]))) - 31; // Set the exponent based on the double value
        }
    }

    // Close the file
    fclose(file);

    // Create an array of size 100 to store the results
    double stat[100];

    // Create a 100x100 matrix Em
    long double Em[size][size];

    // Perform the operations for k times
    for (int iter = 0; iter < k; iter++) {
        // Multiply dm with itself
        for (int i = 0; i < size; i++) {
            for (int j = 0; j < size; j++) {
                dm[i][j] *= dm[i][j];
            }
        }

        // Multiply fm with itself
        for (int i = 0; i < size; i++) {
            for (int j = 0; j < size; j++) {
                // Multiply custom floats using custom logic
                // You need to implement the custom float multiplication here
                // For simplicity, I'll just multiply the mantissas and add the exponents
                fm[i][j].mantissa *= fm[i][j].mantissa;
                fm[i][j].exponent += fm[i][j].exponent;
            }
        }

        // Calculate the difference and store it in Em
        for (int i = 0; i < size; i++) {
            for (int j = 0; j < size; j++) {
                // Convert custom float back to double for the calculation
                double custom_float_value = ldexp((double)fm[i][j].mantissa, fm[i][j].exponent);
                Em[i][j] = dm[i][j] - custom_float_value;
            }
        }

        // Calculate the average of Em and store it in stat
        double sum = 0.0;
        for (int i = 0; i < size; i++) {
            for (int j = 0; j < size; j++) {
                sum += Em[i][j];
            }
        }
        stat[iter] = sum / (size * size);
    }

    // Open a file for writing the stat values
    FILE *statFile = fopen("stat_values.txt", "w");
    if (statFile == NULL) {
        printf("Error opening file for writing.\n");
        return 1;
    }

    // Write the stat values to the file
    for (int i = 0; i < k; i++) {
        fprintf(statFile, "%.15Le\n", stat[i]);
    }

    // Close the stat file
    fclose(statFile);

    return 0;
}
