#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <time.h>

// training data
float trainX[4][2] = {
    {0, 0},
    {1, 1},
    {0, 1},
    {1, 0}
};

float trainY[4] = {0, 1, 0, 0};

// activation functions
float sigmoid(float x) {
    return 1.0f/(1.0f+exp(-x));
}

// forward pass
float predict(float w1, float w2, float b, float x1, float x2) {
    return sigmoid(w1*x1 + w2*x2 + b);
}

// mean squared error loss function
float cost(float w1, float w2, float b) {
    float out = 0.0f;
    int size = sizeof(trainY) / sizeof(trainY[0]);
    for(int i = 0; i < size; i++) {
        float pred = predict(w1, w2, b, trainX[i][0], trainX[i][1]);
        float c = (trainY[i] - pred);
        c*=c;
        out += c;
    }
    out /= size; // average out
    return out;
}

const float EPOCHS = 1e4;
const float LEARNING_RATE = 1e-1;

int main() {
    // initialize hyperparameters
    srand(time(0));
    float w1 = (float)rand() / RAND_MAX;
    float w2 = (float)rand() / RAND_MAX;
    float b = (float)rand() / RAND_MAX;

    // run through gradient descent
    for(int i = 0; i < EPOCHS; i++) {
        float c = cost(w1, w2, b);

        // calculate the derivatives (using an approximation)
        float h = 1e-4; // epsilon
        float gradient_w1 = (cost(w1 + h, w2, b) - c)/h;
        float gradient_w2 = (cost(w1, w2 + h, b) - c)/h;
        float gradient_b = (cost(w1, w2, b + h) - c)/h;

        // update using backpropagation
        w1 -= LEARNING_RATE * gradient_w1;
        w2 -= LEARNING_RATE * gradient_w2;
        b -= LEARNING_RATE * gradient_b;

        // Log the loss value
        printf("Loss = %f\n", c);
    }

    // Run a prediction for each training value to gauge the model's learning
    for(int i = 0; i < 4; i++) {
        printf("Prediction for [%f, %f]: %f\n", trainX[i][0], trainX[i][1], predict(w1, w2, b, trainX[i][0], trainX[i][1]));
    }

    return 0;
}
