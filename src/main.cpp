// Entry point for calculator program.
#include "../include/calculator.h"
#include <iostream>
#include <stdexcept>
#include <sstream>


int main() {
	calculator::Calculator calculator;

	bool running{true};
	std::string user_input{" "};
	double operand_a{0.0}, operand_b{0.0};
	char operation{' '};

	calculator.display_menu();

	while(running) {
		try {
			std::cout<<"\033[35m>\033[0m";
			std::getline(std::cin, user_input);
			if(user_input == "exit") {
				running = false;
				continue;
			}

			std::istringstream buffer(user_input);

			if(buffer>>operand_a>>operation>>operand_b) {
                switch (operation){
                    case '+': std::cout<<operand_a<<" + "<<operand_b<<" = "<<calculator.addition(operand_a, operand_b)<<std::endl; break;
                    case '-': std::cout<<operand_a<<" - "<<operand_b<<" = "<<calculator.subtraction(operand_a, operand_b)<<std::endl; break;
                    case '*': std::cout<<operand_a<<" * "<<operand_b<<" = "<<calculator.multiplication(operand_a, operand_b)<<std::endl; break;  
                    case '/': std::cout<<operand_a<<" / "<<operand_b<<" = "<<calculator.division(operand_a, operand_b)<<std::endl; break;
                    case '^': std::cout<<operand_a<<" ^ "<<operand_b<<" = "<<calculator.exponentiation(operand_a, operand_b)<<std::endl; break;
                    default : throw std::invalid_argument("Invalid");
                }
			}

		} catch(const std::invalid_argument& error) {
			std::cout << "\033[31mError: " << error.what() << "\033[0m" << std::endl;
		}

	}

	return 0;
}