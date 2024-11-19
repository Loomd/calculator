// history implementation file, for calculator. handles data structure for storing, retrieving indexes for reusability within expressions
// and displaying history of operations.

#include "../include/parser.h"
#include "../include/calculator.h"
#include "history.h"


namespace parser {
    
    double Parser::evaluateSimpleExpression(const std::string& user_input, calculator::Calculator& calc) {
        double operand_a{0.0}, operand_b{0.0}, result{0.0};
	    char operation{' '};
	    std::istringstream buffer{user_input};
            if(buffer>>operand_a>>operation>>operand_b) {
	    			switch (operation) {
	    			case '+':
	    				std::cout<<operand_a<<" + "<<operand_b<<" = "<<calc.addition(operand_a, operand_b)<<std::endl;
	    				return result = calc.addition(operand_a, operand_b);
	    				break;
	    			case '-':
	    				std::cout<<operand_a<<" - "<<operand_b<<" = "<<calc.subtraction(operand_a, operand_b)<<std::endl;
	    				break;
	    			case '*':
	    				std::cout<<operand_a<<" * "<<operand_b<<" = "<<calc.multiplication(operand_a, operand_b)<<std::endl;
	    				break;
	    			case '/':
	    				std::cout<<operand_a<<" / "<<operand_b<<" = "<<calc.division(operand_a, operand_b)<<std::endl;
	    				break;
	    			case '^':
	    				std::cout<<operand_a<<" ^ "<<operand_b<<" = "<<calc.exponentiation(operand_a, operand_b)<<std::endl;
	    				break;
	    			default :
	    				throw std::invalid_argument("Invalid");
	    			}
            }
    }
    
    
}