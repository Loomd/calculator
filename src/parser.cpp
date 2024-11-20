/* @brief Parser implementation
** Conditionally reads user input and passes along to appropriate functions.
** Error handling, using try{}catch{}, to avoid program crashes and inform user of proper program usage.
*/

#include "../include/parser.h"
#include "../include/calculator.h"
#include "../include/history.h"


namespace parser {
    
    double Parser::evaluateSimpleExpression(const std::string& user_input, calculator::Calculator& calculator, history::History& history){
        double operand_a{0.0}, operand_b{0.0}, result{0.0};
	    char operation{' '};
		std::string expression{" "};
	    std::istringstream buffer{user_input};
            if(buffer>>operand_a>>operation>>operand_b){
	    			switch (operation){
	    			case '+':
						result = calc.addition(operand_a, operand_b);
						expression = std::to_string(operand_a) + " " + operation + " " + std::to_string(operand_b);
						history.add_entry(expression, result);
						return result;
	    				//break;
	    			case '-':
						result = calc.subtraction(operand_a, operand_b);
	    				expression = std::to_string(operand_a) + " " + operation + " " + std::to_string(operand_b);
						history.add_entry(expression, result);
						return result;
	    				//break;
	    			case '*':
						result = calc.multiplication(operand_a, operand_b);
	    				expression = std::to_string(operand_a) + " " + operation + " " + std::to_string(operand_b);
						history.add_entry(expression, result);
						return result;
	    				//break;
	    			case '/':
						result = calc.division(operand_a, operand_b);
						expression = std::to_string(operand_a) + " " + operation + " " + std::to_string(operand_b);
						history.add_entry(expression, result);
						return result;
	    				//break;
	    			case '^':
						result = calc.exponentiation(operand_a, operand_b);
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
    
    
}