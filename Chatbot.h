#ifndef CHATBOT_H
#define CHATBOT_H

#include "NeuralNetwork.h"
#include <string>
#include <map>

class Chatbot {
public:
    Chatbot();
    void startChat();

private:
    NeuralNetwork nn;
    std::map<int, std::string> responses;

    void initializeResponses();
    std::vector<double> preprocessInput(const std::string& input);
};

#endif