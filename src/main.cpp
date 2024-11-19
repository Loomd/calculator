// Entry point for calculator program.
#include "../include/calculator.h"
#include "../include/parser.h"
#include <stdexcept>
#include <iostream>

int main() {
    calculator::Calculator calculator;
    parser::Parser parser;

    bool running{true};
    std::string user_input;

    calculator.display_menu();

    while (running) {
        try {
            std::cout << "\033[35m>\033[0m";
            std::getline(std::cin, user_input);

            if (user_input == "exit") {
                running = false;
                continue;
            } else if (user_input == "menu") {
                calculator.display_menu();
                continue;
            }

            double result = parser.evaluateSimpleExpression(user_input, calculator);
            std::cout << "Result: " << result << "\n";
        } catch (const std::invalid_argument& error) {
            std::cout << "\033[31mError: " << error.what() << "\033[0m\n";
        }
    }

    return 0;
}


	return 0;
}