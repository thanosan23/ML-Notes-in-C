#include <stdlib.h>
#include <stdio.h>
#include <time.h>

float train[][2] = {
    {1, 2},
    {2, 4},
    {3, 6},
    {4, 8}
};

#define N 4

float cost(float w, float b, float data[][2]) {
    float out = 0.0f;
    for(int i = 0; i < N; i++) {
        float pred = w*data[i][0] + b;
        float c = (data[i][1] - pred);
        c *= c;
        out += c;
    }
    out /= N;
    return out;
}

int main() {
    srand(time(0));
    const int train_len = sizeof(train) / sizeof(train[0]);
    float w = (float)rand()/RAND_MAX;
    float b = (float)rand()/RAND_MAX;
    for(int i = 0; i < 1e5; i++) {
        float c = cost(w, b, train);
        float h = 1e-4;
        float gradient_w = (cost(w + h, b, train) - c) / h;
        float gradient_b = (cost(w, b + h, train) - c) / h;
        w -= 0.1 * gradient_w;
        b -= 0.1 * gradient_b;
        printf("Loss = %f\n", c);
    }
    printf("Equation: y = %fx + %f\n", w, b);
    return 0;
}
