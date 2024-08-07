#include "Chatbot.h"
#include <iostream>
#include <vector>
#include <sstream>
#include <algorithm>
#include <cctype>

Chatbot::Chatbot() : nn(5, 4, 3) { // 5 input features, 4 hidden neurons, 3 output classes
    initializeResponses();
    nn.generateDataset(1000); // Generate and train on a dataset of 1000 examples
}

void Chatbot::initializeResponses() {
    responses[0] = "Hi there! How can I assist you today?";
    responses[1] = "I'm just a computer program, but thanks for asking!";
    responses[2] = "I'm called Chatbot. What can I do for you?";
}

// Convert string to lowercase
std::string toLowerCase(const std::string& input) {
    std::string result = input;
    std::transform(result.begin(), result.end(), result.begin(), ::tolower);
    return result;
}

// Tokenize the input text
std::vector<std::string> tokenize(const std::string& input) {
    std::vector<std::string> tokens;
    std::istringstream stream(input);
    std::string token;
    while (stream >> token) {
        tokens.push_back(token);
    }
    return tokens;
}

// Enhanced preprocessing
std::vector<double> Chatbot::preprocessInput(const std::string& input) {
    std::vector<double> inputVector(5, 0); // Assuming 5 input features

    // Convert input to lowercase
    std::string lowerInput = toLowerCase(input);

    // Tokenize input
    std::vector<std::string> tokens = tokenize(lowerInput);

    // Mark features based on tokens
    if (std::find(tokens.begin(), tokens.end(), "hello") != tokens.end()) {
        inputVector[0] = 1; // Mark "hello"
    }
    if (std::find(tokens.begin(), tokens.end(), "how") != tokens.end() &&
        std::find(tokens.begin(), tokens.end(), "are") != tokens.end() &&
        std::find(tokens.begin(), tokens.end(), "you") != tokens.end()) {
        inputVector[1] = 1; // Mark "how are you"
    }
    if (std::find(tokens.begin(), tokens.end(), "name") != tokens.end()) {
        inputVector[2] = 1; // Mark "what is your name"
    }
    if (std::find(tokens.begin(), tokens.end(), "help") != tokens.end()) {
        inputVector[3] = 1; // Mark "help"
    }
    if (std::find(tokens.begin(), tokens.end(), "bye") != tokens.end()) {
        inputVector[4] = 1; // Mark "bye"
    }

    return inputVector;
}

void Chatbot::startChat() {
    std::cout << "Hello! I'm a simple chatbot. Type 'exit' to end the chat." << std::endl;

    std::string userInput;
    while (true) {
        std::cout << "You: ";
        getline(std::cin, userInput);

        // Check for exit command
        if (userInput == "exit") {
            std::cout << "Chatbot: Goodbye! Have a great day!" << std::endl;
            break;
        }

        // Preprocess the user input into a vector
        std::vector<double> inputVector = preprocessInput(userInput);

        // Get the prediction from the neural network
        std::vector<double> output = nn.predict(inputVector);

        // Find the index of the maximum value in the output vector
        int responseIndex = 0;
        double maxValue = output[0];
        for (int i = 1; i < output.size(); ++i) {
            if (output[i] > maxValue) {
                maxValue = output[i];
                responseIndex = i;
            }
        }

        // Respond based on the predicted index
        std::cout << "Chatbot: " << responses[responseIndex] << std::endl;
    }
}
