# Nanod

Nanod is a simple neural network-based chatbot implemented in C++. The chatbot is capable of understanding basic user inputs and generating appropriate responses. It learns from a generated dataset of intents and responses.

## Features

- Simple feedforward neural network for intent recognition.
- Generates a dataset for training the neural network.
- Responds to user inputs based on learned intents.
- Interactive chat interface.

## Requirements

- C++11 or later
- A C++ compiler (e.g., GCC or MSVC)
- CMake (optional, for building)

## Installation

**Clone the repository**:
   ```bash
   git clone https://github.com/Zinedinarnaut/Nanod.git
   cd nanod
```   
   
```Build the project:
If you're using Visual Studio, open the solution file and build the project (Ctrl + Shift + B). 
```

```
Run the application:
Start the application (Ctrl + F5 in Visual Studio) to launch the chatbot.
```
# Usage
Once the application is running, you will see a greeting message from the chatbot.
You can type in simple phrases such as:
```"hello"
"how are you"
"what is your name"
"help"
"bye"
```
Type exit to end the chat session.

# Code Structure

- NeuralNetwork.h / NeuralNetwork.cpp: Defines and implements the neural network used for intent recognition.
- Chatbot.h / Chatbot.cpp: Defines and implements the chatbot interface and logic.
- main.cpp: Entry point of the application.

# Example Dataset
The chatbot generates a dataset on startup, which includes various intents and their corresponding outputs. The dataset is used to train the neural network.

# Contributions
Contributions are welcome! If you have suggestions for improvements or features, feel free to create a pull request or open an issue.

# License
This project is licensed under the MIT License. See the LICENSE file for more information.

# Acknowledgments
Thanks to the open-source community for providing the tools and resources to create this chatbot.

### Notes

- **Repository URL**: Replace `https://github.com/Zinedinarnaut/Nanod.git` with the actual URL of your repository if you plan to host it on GitHub or any other platform.
- **License**: [License](https://github.com/Zinedinarnaut/Nanod/blob/master/LICENSE.txt).
- **Contributions**: Coming soon
