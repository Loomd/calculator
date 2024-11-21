/* @brief Parser implementation
** Conditionally reads user input and passes along to appropriate functions.
** Error handling, using try{}catch{}, to avoid program crashes and inform user of proper program usage.
*/

#include "../include/parser.h"
#include "../include/calculator.h"
#include "../include/history.h"
#include <sstream>
#include <iostream>

namespace parser {
    
    double Parser::evaluateSimpleExpression(const std::string& user_input, calculator::Calculator& calculator, history::History& history){
        double operand_a{0.0}, operand_b{0.0}, result{0.0};
	    char operation{' '};
		std::string expression{" "};
	    std::istringstream buffer{user_input};
            if(buffer>>operand_a>>operation>>operand_b){
	    			switch (operation){
	    			case '+':
						result = calculator.addition(operand_a, operand_b);
						expression = std::to_string(operand_a) + " " + operation + " " + std::to_string(operand_b);
						history.add_entry(expression, result);
						return result;
	    				//break;
	    			case '-':
						result = calculator.subtraction(operand_a, operand_b);
	    				expression = std::to_string(operand_a) + " " + operation + " " + std::to_string(operand_b);
						history.add_entry(expression, result);
						return result;
	    				//break;
	    			case '*':
						result = calculator.multiplication(operand_a, operand_b);
	    				expression = std::to_string(operand_a) + " " + operation + " " + std::to_string(operand_b);
						history.add_entry(expression, result);
						return result;
	    				//break;
	    			case '/':
						result = calculator.division(operand_a, operand_b);
						expression = std::to_string(operand_a) + " " + operation + " " + std::to_string(operand_b);
						history.add_entry(expression, result);
						return result;
	    				//break;
	    			case '^':
						result = calculator.exponentiation(operand_a, operand_b);
	    				expression = std::to_string(operand_a) + "  " + operation + " "+ std::to_string(operand_b);
						history.add_entry(expression, result);
						return result;
	    				//break;
	    			default :
	    				throw std::invalid_argument("Error: Invalid expression, use format: 'operand' 'operator' 'operand'.\033[0m");
	    			}
            }
		throw std::invalid_argument("\033[31mError: Invalid operation (use '+', '-', '*', '/', '^').\033[0m");
    }
    
    double Parser::evaluateSquareRoot(const std::string& user_input, calculator::Calculator& calculator, history::History& history){
        //Find index of open parenthesis
        size_t openParenPos = user_input.find('(');
		//Find index of closing parenthesis.
        size_t closeParenPos = user_input.find(')', openParenPos);
        
        //Extract substring between parentheses by using the indexes plus one and minus one to exclude the parentheses.
        std::string inner = user_input.substr(openParenPos + 1, closeParenPos - openParenPos - 1);
		//Create a buffer to read the inner string.
        std::istringstream buffer{inner};

		//Read the operand into a double to determine if the input is a number vs an expression before checking for .eof
		//Distinguishes between a simple number and a more complex expression.
        double operand;
        buffer>>operand;

        //Check if there's more to read, indicating an expression
        if(!buffer.eof()){
            //Evaluate the expression.
            return calculator.squareRoot(evaluateSimpleExpression(inner, calculator, history));
        }

        //If there's only a number.
        double result = calculator.squareRoot(operand);
        history.add_entry("sqrt(" + std::to_string(operand) + ")", result);
        return result;
    }
}