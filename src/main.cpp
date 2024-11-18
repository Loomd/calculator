// Entry point for calculator program.
#include "calculator.h"
#include <iostream>
#include <stdexcept>
#include <sstream>


int main() {

	bool running{true};
	std::string user_input{" "};
	double operand_a{0.0}, operand_b{0.0};
	char operation{' '};

	std::cout<<"\033[32m==================CLI Calculator=================="<<std::endl
	         <<"Suported operations: "<<std::endl
	         <<" Addition '+'"<<std::endl
	         <<" Subtraction '-'"<<std::endl
	         <<" Multiplication '*'"<<std::endl
	         <<" Division  '/'"<<std::endl
	         <<" Exponentiation '^'\033[0m"<<std::endl;

	//std::cout<<"\033[34m>\033[0m";

	while(running) {
		try {
			std::cout<<"\033[35m>\033[0m";
			std::getline(std::cin, user_input);
			if(user_input == "exit") {
				running = false;
				break;
			}


			std::istringstream buffer(user_input);
			if(buffer>>operand_a>>operation>>operand_b) {
                switch (operation){
                    case '+': std::cout<<operand_a<<" + "<<operand_b<<" = "<<addition(operand_a, operand_b); break;
                    case '-': std::cout<<operand_a<<" - "<<operand_b<<" = "<<subtract(operand_a, operand_b); break;
                    case '*': std::cout<<operand_a<<" * "<<operand_b<<" = "<<addition(operand_a, operand_b); break;  
                    case '/': std::cout<<operand_a<<" / "<<operand_b<<" = "<<addition(operand_a, operand_b); break;
                    case '^': std::cout<<operand_a<<" ^ "<<operand_b<<" = "<<addition(operand_a, operand_b); break;
                    default : throw std::invalid_argument("Invalid");
                }
			}

		} catch(const std::invalid_argument& ia) {
			std::cout << "#1: " << ia.what() << '\n';
		}

	}

	return 0;
}