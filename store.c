#include <stdio.h>
#include <stdlib.h>
#include <time.h>

int main() {
    int n;
    printf("Enter the range value (e.g., 10): ");
    scanf("%d", &n);

    int totalValues = 10000; // Number of random values to generate

    printf("Generating %d random double values between -%d and +%d.\n", totalValues, n, n);

    // Seed the random number generator with the current time
    srand(time(NULL));

    // Open a file for writing
    FILE *file = fopen("random_numbers.txt", "w");
    if (file == NULL) {
        printf("Error opening file for writing.\n");
        return 1;
    }

    // Generate and write random double values to the file
    for (int i = 0; i < totalValues; i++) {
        // Generate a random integer between -n and n
        int randomInt = rand() % (2 * n + 1) - n;

        // Convert to double
        double randomValue = (double)randomInt;

        fprintf(file, "%lf\n", randomValue);
    }

    // Close the file
    fclose(file);

    printf("%d random double values between -%d and +%d have been generated and stored in 'random_numbers.txt'.\n", totalValues, n, n);

    return 0;
}
