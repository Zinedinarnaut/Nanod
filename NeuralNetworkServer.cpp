#include "NeuralNetwork.h"
#include <cmath>
#include <cstdlib>
#include <ctime>
#include <iostream>

// Constructor for the Neural Network
NeuralNetwork::NeuralNetwork(int inputSize, int hiddenSize, int outputSize)
    : inputSize(inputSize), hiddenSize(hiddenSize), outputSize(outputSize) {
    weightsInputHidden.resize(inputSize, std::vector<double>(hiddenSize));
    weightsHiddenOutput.resize(hiddenSize, std::vector<double>(outputSize));

    srand(static_cast<unsigned int>(time(nullptr))); // Seed for random number generation

    // Initialize weights for input to hidden layer
    for (int i = 0; i < inputSize; ++i) {
        for (int j = 0; j < hiddenSize; ++j) {
            weightsInputHidden[i][j] = static_cast<double>(rand()) / RAND_MAX;
        }
    }

    // Initialize weights for hidden to output layer
    for (int i = 0; i < hiddenSize; ++i) {
        for (int j = 0; j < outputSize; ++j) {
            weightsHiddenOutput[i][j] = static_cast<double>(rand()) / RAND_MAX;
        }
    }
}

// Sigmoid activation function
double NeuralNetwork::sigmoid(double x) {
    return 1.0 / (1.0 + exp(-x));
}

// Derivative of sigmoid function
double NeuralNetwork::sigmoidDerivative(double x) {
    return x * (1.0 - x);
}

// Forward pass through the network
void NeuralNetwork::forward(const std::vector<double>& input) {
    // Calculate hidden layer output
    hiddenLayerOutput.resize(hiddenSize);
    for (int j = 0; j < hiddenSize; ++j) {
        hiddenLayerOutput[j] = 0;
        for (int i = 0; i < inputSize; ++i) {
            hiddenLayerOutput[j] += input[i] * weightsInputHidden[i][j];
        }
        hiddenLayerOutput[j] = sigmoid(hiddenLayerOutput[j]);
    }

    // Calculate output layer output
    outputLayerOutput.resize(outputSize);
    for (int j = 0; j < outputSize; ++j) {
        outputLayerOutput[j] = 0; // Initialize output
        for (int i = 0; i < hiddenSize; ++i) {
            outputLayerOutput[j] += hiddenLayerOutput[i] * weightsHiddenOutput[i][j];
        }
        outputLayerOutput[j] = sigmoid(outputLayerOutput[j]);
    }
}

// Backward pass through the network
void NeuralNetwork::backward(const std::vector<double>& target, double learningRate, const std::vector<double>& input) {
    std::vector<double> outputErrors(outputSize);
    for (int j = 0; j < outputSize; ++j) {
        outputErrors[j] = target[j] - outputLayerOutput[j];
    }

    std::vector<double> hiddenErrors(hiddenSize);
    for (int j = 0; j < hiddenSize; ++j) {
        hiddenErrors[j] = 0;
        for (int k = 0; k < outputSize; ++k) {
            hiddenErrors[j] += outputErrors[k] * weightsHiddenOutput[j][k]; // Correct index access
        }
        hiddenErrors[j] *= sigmoidDerivative(hiddenLayerOutput[j]);
    }

    // Update weights between hidden and output layers
    for (int j = 0; j < hiddenSize; ++j) {
        for (int k = 0; k < outputSize; ++k) {
            weightsHiddenOutput[j][k] += learningRate * outputErrors[k] * hiddenLayerOutput[j];
        }
    }

    // Update weights between input and hidden layers
    for (int i = 0; i < inputSize; ++i) {
        for (int j = 0; j < hiddenSize; ++j) {
            weightsInputHidden[i][j] += learningRate * hiddenErrors[j] * input[i]; // Ensure 'input' is available here
        }
    }
}

// Train the neural network
void NeuralNetwork::train(const std::vector<std::vector<double>>& inputs, const std::vector<std::vector<double>>& outputs, int epochs, double learningRate) {
    for (int epoch = 0; epoch < epochs; ++epoch) {
        for (size_t i = 0; i < inputs.size(); ++i) {
            forward(inputs[i]);
            backward(outputs[i], learningRate, inputs[i]); // Pass the input vector to backward
        }
    }
}

// Predict using the neural network
std::vector<double> NeuralNetwork::predict(const std::vector<double>& input) {
    forward(input);
    return outputLayerOutput;
}

// Load Dataset and Train the Neural Network
void NeuralNetwork::generateDataset(int numExamples) {
    std::vector<std::vector<double>> trainingInputs;
    std::vector<std::vector<double>> trainingOutputs;

    for (int i = 0; i < numExamples; ++i) {
        std::vector<double> input(5, 0); // 5 input features
        std::vector<double> output(3, 0); // 3 output classes

        // Randomly generate inputs and outputs
        int intent = rand() % 5; // Randomly choose one of the intents
        input[intent] = 1; // Set the chosen input feature

        // Set the corresponding output
        switch (intent) {
        case 0:
            output[0] = 1; // Response for "hello"
            break;
        case 1:
            output[1] = 1; // Response for "how are you"
            break;
        case 2:
            output[2] = 1; // Response for "what is your name"
            break;
        case 3:
            output[0] = 1; // Response for "help"
            break;
        case 4:
            output[1] = 1; // Response for "bye"
            break;
        }

        trainingInputs.push_back(input);
        trainingOutputs.push_back(output);
    }

    // Train the neural network with the generated dataset
    train(trainingInputs, trainingOutputs, 10000, 0.1); // Train for 10,000 epochs
}