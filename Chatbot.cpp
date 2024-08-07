#include "Chatbot.h"
#include <iostream>
#include <vector>

Chatbot::Chatbot() : nn(5, 4, 3) { // 5 input features, 4 hidden neurons, 3 output classes
    initializeResponses();
    nn.generateDataset(1000); // Generate and train on a dataset of 1000 examples
}

void Chatbot::initializeResponses() {
    responses[0] = "Hi there! How can I assist you today?";
    responses[1] = "I'm just a computer program, but thanks for asking!";
    responses[2] = "I'm called Chatbot. What can I do for you?";
}

std::vector<double> Chatbot::preprocessInput(const std::string& input) {
    std::vector<double> inputVector(5, 0); // Assuming 5 input features
    if (input.find("hello") != std::string::npos) {
        inputVector[0] = 1; // Mark "hello"
    }
    else if (input.find("how are you") != std::string::npos) {
        inputVector[1] = 1; // Mark "how are you"
    }
    else if (input.find("what is your name") != std::string::npos) {
        inputVector[2] = 1; // Mark "what is your name"
    }
    else if (input.find("help") != std::string::npos) {
        inputVector[3] = 1; // Mark "help"
    }
    else if (input.find("bye") != std::string::npos) {
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