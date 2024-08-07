// NeuralNetwork.h

#ifndef NEURALNETWORK_H
#define NEURALNETWORK_H

#include <vector>
#include <string>

class NeuralNetwork {
public:
    NeuralNetwork(int inputSize, int hiddenSize, int outputSize);
    void train(const std::vector<std::vector<double>>& inputs, const std::vector<std::vector<double>>& outputs, int epochs, double learningRate);
    std::vector<double> predict(const std::vector<double>& input);
    void generateDataset(int numExamples); // New method to generate dataset

private:
    double sigmoid(double x);
    double sigmoidDerivative(double x);
    void forward(const std::vector<double>& input);
    void backward(const std::vector<double>& target, double learningRate, const std::vector<double>& input); // Updated declaration

    int inputSize;
    int hiddenSize;
    int outputSize;

    std::vector<std::vector<double>> weightsInputHidden;
    std::vector<std::vector<double>> weightsHiddenOutput;

    std::vector<double> hiddenLayerOutput;
    std::vector<double> outputLayerOutput;
};

#endif