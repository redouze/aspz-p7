#include <stdio.h>
#include <stdlib.h>
#include <time.h>

float rand_float_0_1() {
    return (float)rand() / (float)RAND_MAX;
}

float rand_float_0_n(float n) {
    return rand_float_0_1() * n;
}

int main() {
    srand((unsigned int)time(NULL));

    int count = 10;
    float n;

    printf("Enter a floating-point number n for range [0.0, n]: ");
    if (scanf("%f", &n) != 1 || n <= 0.0f) {
        fprintf(stderr, "Invalid input. Must be a positive float.\n");
        return 1;
    }

    printf("\nRandom floats in [0.0, 1.0]:\n");
    for (int i = 0; i < count; ++i) {
        printf("%.6f ", rand_float_0_1());
    }

    printf("\n\nRandom floats in [0.0, %.2f]:\n", n);
    for (int i = 0; i < count; ++i) {
        printf("%.6f ", rand_float_0_n(n));
    }

    printf("\n");
    return 0;
}
