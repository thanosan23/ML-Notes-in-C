#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <time.h>

#define EPOCHS 1e4

float sigmoid(float x) {
    return 1.0f/(1.0f+exp(-x));
}

float trainX[4][2] = {
    {0, 0},
    {1, 1},
    {0, 1},
    {1, 0}
};

float trainY[4] = {0, 1, 0, 0};

float predict(float w1, float w2, float b, float x1, float x2) {
    return sigmoid(w1*x1 + w2*x2 + b);
}

// mse
float cost(float w1, float w2, float b) {
    float out = 0.0f;
    for(int i = 0; i < 4; i++) {
        float pred = predict(w1, w2, b, trainX[i][0], trainX[i][1]);
        float c = (trainY[i] - pred);
        c*=c;
        out += c;
    }
    out /= 4; // average out
    return out;
}


int main() {
    // initialize hyperparameters
    srand(time(0));
    float w1 = (float)rand()  / RAND_MAX;
    float w2 = (float)rand()  / RAND_MAX;
    float b = (float)rand()  / RAND_MAX;

    float lr = 1e-1;

    // run through gradient descent
    for(int i = 0; i < EPOCHS; i++) {
        float c = cost(w1, w2, b);

        // calculate to derivatives (using an approximation)
        float h = 1e-4;
        float gradient_w1 = (cost(w1 + h, w2, b) - c)/h;
        float gradient_w2 = (cost(w1, w2 + h, b) - c)/h;
        float gradient_b = (cost(w1, w2, b + h) - c)/h;


        // update using backpropogation
        w1 -= lr * gradient_w1;
        w2 -= lr * gradient_w2;
        b -= lr * gradient_b;
        printf("Loss = %f\n", c);
    }

    for(int i = 0; i < 4; i++) {
        printf("Prediction for [%f, %f]: %f\n", trainX[i][0], trainX[i][1], predict(w1, w2, b, trainX[i][0], trainX[i][1]));
    }

    return 0;
}
