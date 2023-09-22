#include <stdio.h>
#include <stdlib.h>
#include <math.h>

int main() {
    int size = 10 ;
    int k = 100;

    // Create 100x100 matrices
    double dm[size][size];
    float fm[size][size];

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
            fm[i][j] = (float)dm[i][j]; // Store the same value in fm as a float
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
                fm[i][j] *= fm[i][j];
            }
        }

        // Calculate the difference and store it in Em
        for (int i = 0; i < size; i++) {
            for (int j = 0; j < size; j++) {
                Em[i][j] = dm[i][j] - fm[i][j];
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
