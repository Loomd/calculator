#include "../include/calculations.h"
#include "../include/parser.h"
#include <stdexcept>
#include <cmath>

namespace calculations{

    double Calculations::evaluatePostfix(const std::vector<std::string>& postfix_vector){

        std::string result_string;
        std::string a, b;
        std::vector<std::string> stack;

        for(const auto& token : postfix_vector){

            if(std::isdigit(token[0]) || (token[0] == '-' && std::isdigit(token[1]))){
                stack.push_back(token);

            }else if(parser::Parser::pemdas.find(token) != parser::Parser::pemdas.end()){

                if(stack.size() < 2){
                    throw std::invalid_argument("Invalid expression");
                }

                a = stack.back();
                stack.pop_back();

                b = stack.back();
                stack.pop_back();

                result_string = calculate(token, a, b);
                stack.push_back(result_string);

            }else
                throw std::invalid_argument("Invalid expression");
        
        }

        if(stack.size() != 1){
            throw std::invalid_argument("Invalid expression");
        }
        
        return std::stod(stack.back());
    }

    std::string Calculations::calculate(const std::string& operation, const std::string& operandA, const std::string& operandB){

        double result{0.0};

        switch(operation[0]){
            case '+':   result = std::stod(operandB) + std::stod(operandA); break;
            case '-':   result = std::stod(operandB) - std::stod(operandA); break;
            case '*':   result = std::stod(operandB) * std::stod(operandA); break;
            case '/':   if(std::stod(operandA) == 0) throw std::invalid_argument("Division by zero"); result = std::stod(operandB) / std::stod(operandA); break;
            case '^':   if(std::stod(operandB) < 0) throw std::invalid_argument("Negative base for exponentiation"); result = std::pow(std::stod(operandB), std::stod(operandA)); break;
        }

        return std::to_string(result);
    }

}//namespace calculations