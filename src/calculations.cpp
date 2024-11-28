#include "../include/calculations.h"
#include "../include/parser.h"
#include <stdexcept>
#include <cmath>

namespace calculations{

    /*
     * @function: evaluatePostfix()
     * @params: const std::vector<std::string>& postfix_vector
     *  - Type: vector of strings
     *  - It's the RPN formatted user_input from parser.cpp 
     *  - qualifier: '&' pass the address instead as to avoid any overhead.
     *  - specifier: const prevents modification of the vector.
     * @brief: 
     * This function takes the RPN formatted expression (it's a vector of strings) and iterates through it.
     * The function follows the standard RPN evaluation algorithm:
     * 
     * - When a number is encountered, push it onto the stack
     * - When an operator is encountered:
     *   1. Pop the top two values from stack (b then a)
     *   2. Perform the operation: a (operator) b
     *   3. Push the result back onto the stack
     * 
     * The process continues until all tokens are processed, at which point
     * the final value on the stack is the result of the entire expression.
     * 
     * Note: The function assumes valid RPN input as the parser has already validated
     * and formatted the expression correctly.
     */
    double Calculations::evaluatePostfix(const std::vector<std::string>& postfix_vector){
        std::string result_string;                                                     //Holds intermediate results from operations.
        std::string a, b;                                                              //Operands for calculations.
        std::vector<std::string> stack;                                                //Vector acting as a FILO stack for operands and results.

        for(const auto& token : postfix_vector){

            if(std::isdigit(token[0]) || (token[0] == '-' && std::isdigit(token[1]))){
                stack.push_back(token);                                               //Push numbers (including negative) to stack.

            }else if(parser::Parser::pemdas.find(token) != parser::Parser::pemdas.end()){

                if(stack.size() < 2){                                                 //If the expression is incomplete, i.e. '1 + 2 * 3 - 1 *' would trigger this and the user would know the last valid operation '-' which is incomplete. 
                    throw std::invalid_argument("Invalid expression incomplete: " + token);
                }

                b = stack.back();                                                     //Pop second operand.
                stack.pop_back();

                a = stack.back();                                                     //Pop first operand.
                stack.pop_back();

                result_string = calculate(token, a, b);                               //Perform operation.
                stack.push_back(result_string);                                       //Push result to stack.
            }
        }

        return std::stod(stack.back());
    }//evaluatePostfix().

    /* 
     * @function: calculate()
     * @params: const std::string& operation, const std::string& operandA, const std::string& operandB
     * @brief: 
     * This function performs the arithmetic operation specified by the operation string on the two operands.
     * It supports addition, subtraction, multiplication, division, and exponentiation.
     */
    std::string Calculations::calculate(const std::string& operation, const std::string& operandA, const std::string& operandB){

        double result{0.0};

        switch(operation[0]){
            case '+':   result = std::stod(operandA) + std::stod(operandB); break;
            case '-':   result = std::stod(operandA) - std::stod(operandB); break;
            case '*':   result = std::stod(operandA) * std::stod(operandB); break;
            case '/':   if(std::stod(operandB) == 0) throw std::invalid_argument("Division by zero"); result = std::stod(operandA) / std::stod(operandB); break;
            case '^':   if(std::stod(operandA) < 0) throw std::invalid_argument("Negative base for exponentiation"); result = std::pow(std::stod(operandA), std::stod(operandB)); break;
        }

        return std::to_string(result);
    }//calculate().


}//namespace calculations