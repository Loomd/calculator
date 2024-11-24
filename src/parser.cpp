/* @brief Parser implementation
** Reads user input and passes along to appropriate functions.
*/

#include "../include/parser.h"
#include "../include/calculator.h"
#include "../include/history.h"
#include <sstream>
#include <iostream>

namespace parser {

	/* @brief Turns a mathematical expression into tokens, the constituents of which are the operands, operators, and parentheses. 
	** Ex: 
	** 	Input: "(-3.5 + 2) * 4"
	** 	Output: ["(", "-3.5", "+", "2", ")", "*", "4"]
	*/
	std::vector<std::string> Parser::tokenizeExpression(const std::string& user_input){
		std::vector<std::string> token_vector; //Vector to store tokens as they are parsed.
		std::string token_builder; 			   //Essentially a buffer to build tokens.

		//Iterate through user_input character by character
		for(unsigned i = 0; i < user_input.length(); i++){
			char tkn = user_input[i]; 	//Extract current character, store in 'tkn'

			//If `tkn` is a number or part of a number append it to the buffer.
			if(isdigit(tkn) || tkn == '.' ){ token_builder += tkn; } 	
			else
			{
				//If a non-numeric character is encountered.
				//Push the completed number (int or float) into the vector.
				//Clear the token builder for the next token.
				if(!(token_builder.empty())){
					token_vector.push_back(token_builder);	
					token_builder.clear();					
				}

				//Check if the character is a parenthesis.
				//Treat parenthesis as a single toke by converting it and pushing it into vector.
				if(tkn == '(' || tkn == ')'){ token_vector.push_back(std::string(1, tkn)); }
				//Handle negatives.
				else if(parser::Parser::pemdas.find(std::string(1, tkn)) != parser::Parser::pemdas.end()){
					//If the character is `-` AND
					//It's at the start of the expression OR
                	//It follows an opening parenthesis think "( -5 ...)" OR
					//It's after another operator think "n * -5".
					//Append the negative sign to the token builder.
					if(tkn == '-' && (token_vector.empty() || token_vector.back() == "(" || parser::Parser::pemdas.find(token_vector.back()) != parser::Parser::pemdas.end())){ token_builder += tkn; }
					//Otherwise, treat '-' as a subtraction operator and place in vector.
					else{ token_vector.push_back(std::string(1, tkn)); }
				}
			}
		}

		//After looping, if any token remains push it into the vector of tokens.
		if(!(token_builder.empty())){ token_vector.push_back(token_builder); }

		//Return vector of strings containing the parsed tokens.
		return token_vector;
	}

	/* @brief Converts the tokenized expression into postfix notation (RPN)
	** Ex:
	** 	 input: ["(", "-3.5", "+", "2", ")", "+", "4"]
	** 	 output: ["-3.5", "2", "+", "4", "*"]
	*/
	std::vector<std::string> Parser::convertToPostfix(const std::vector<std::string>& token_vector){
		std::vector<std::string> outputQueue; 	//Store postfix expression.
		std::vector<std::string> operatorStack; //Holds operators and parentheses temporarily.

		//Iterate through token_vector, referring to it's address improving efficiency, token by token.
		for(const std::string& token : token_vector){

			//The token is a number (pos or neg).
			//- If the first token is a digit, it's positive.
			//- If the first token is '-' and the subsequent character of that token is a digit, it's negative
			//Store the token in the ouputQueue vector.
			if(isdigit(token[0]) || (token.size() > 1 && token[0] == '-' && isdigit(token[1]))){ outputQueue.push_back(token); }
			//The token is an operator (defined in pemdas map)
			else if(pemdas.find(token) != pemdas.end()){
				//Handle operator precedence
				//- while there are operators on the stack AND
				//- The operator currently at the top is greater than or equal to (has precedence) to the current token (operator)
				// - Pop operators from the operatorStack vector and add them to ouputQueue vector.
				// - Remove operators from the Operatorstack vector.
				while(!operatorStack.empty() && pemdas.find(operatorStack.back()) != pemdas.end() && pemdas[operatorStack.back()] >= pemdas[token]){
						outputQueue.push_back(operatorStack.back());
						operatorStack.pop_back();
				}
				//Push current operator into operatorStack vector to be processed later.
				operatorStack.push_back(token); 	
			//The token is an open parenthesis. This will mark the beginning of a sub expression and it's pushed into the operatorStack.
			}else if(token == "("){ operatorStack.push_back(token); }
			//The token is a closing parenthesis.
			 else if(token == ")"){
				//Closing parenthesis signals the end of a subexpression. All the operators between 
				//the opening and closing parentheses are popped out of the operatorStack until 
				//the opening parenthesis is accounted for.
				while(!operatorStack.empty() && operatorStack.back() != "("){
					outputQueue.push_back(operatorStack.back());
					operatorStack.pop_back();
				}
				//Discard the open parenthesis left in the operatorStack vector.
				if(!operatorStack.empty() && operatorStack.back() == "("){ operatorStack.pop_back(); }
				//If there's no open parenthesis there's a mismatched parenthesis
				else{ throw std::invalid_argument("Mismatched parentheses in expression."); }
			//Handle tokens which aren't supported.
			}else{ throw std::invalid_argument("Invalid token in expression: " + token); }
		}

			//After iterating through the tokens, there might be operators left within the operator stack
			//these must be added to outputQueue vector to complete postfix notation.
			while(!operatorStack.empty()){
				outputQueue.push_back(operatorStack.back());
				operatorStack.pop_back();
			}

		//Return the expression in RPN.
		return outputQueue; 
	}

	double Parser::evaluatePostfix(const std::vector<std::string>& postfix) {
    // Implementation here...
	}

    
    double Parser::evaluateSimpleExpression(const std::string& user_input, calculator::Calculator& calculator, history::History& history, bool log_history){
        double operand_a{0.0}, operand_b{0.0}, result{0.0};
	    char operation{' '};
		std::string expression{" "};
	    std::istringstream buffer{user_input};
            if(buffer>>operand_a>>operation>>operand_b){
	    			switch (operation){
	    			case '+':
						result = calculator.addition(operand_a, operand_b);
						expression = history.formatNumber(operand_a) + " " + operation + " " + history.formatNumber(operand_b);
						if(log_history) history.add_entry(expression, result);
						return result;
	    			case '-':
						result = calculator.subtraction(operand_a, operand_b);
	    				expression = history.formatNumber(operand_a) + " " + operation + " " + history.formatNumber(operand_b);
						if(log_history) history.add_entry(expression, result);
						return result;
	    			case '*':
						result = calculator.multiplication(operand_a, operand_b);
	    				expression = history.formatNumber(operand_a) + " " + operation + " " + history.formatNumber(operand_b);
						if(log_history) history.add_entry(expression, result);
						return result;
	    			case '/':
						result = calculator.division(operand_a, operand_b);
						expression = history.formatNumber(operand_a) + " " + operation + " " + history.formatNumber(operand_b);
						if(log_history) history.add_entry(expression, result);
						return result;
	    			case '^':
						result = calculator.exponentiation(operand_a, operand_b);
	    				expression = history.formatNumber(operand_a) + "  " + operation + " "+ history.formatNumber(operand_b);
						if(log_history) history.add_entry(expression, result);
						return result;
	    			default :
	    				throw std::invalid_argument("Error: Invalid expression, use format: 'operand' 'operator' 'operand'.\033[0m");
	    			}
            }
	throw std::invalid_argument("\033[31mError: Invalid operation (use '+', '-', '*', '/', '^').\033[0m");
    }
    
    double Parser::evaluateSquareRoot(const std::string& user_input, calculator::Calculator& calculator, history::History& history, bool log_history){
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
            double result_of_expression = evaluateSimpleExpression(inner, calculator, history, false);
            double result_of_sqrt = calculator.squareRoot(result_of_expression);
            if(log_history) history.add_entry("sqrt(" + inner + ")", result_of_sqrt);
            return result_of_sqrt;
        }

    	//If there's only a number.
    	double result = calculator.squareRoot(operand);
        if(log_history) history.add_entry("sqrt(" + history.formatNumber(operand) + ")", result);
        return result;
    }

	double Parser::usePriorAnswer(const std::string& user_input, calculator::Calculator& calculator, history::History& history, bool log_history){
		double index{0.0}, operand_b{0.0}, result{0.0};
	    char symbol{' '}, operation{' '};
		std::string expression{" "};
	    std::istringstream buffer{user_input};

		if(buffer>>symbol>>index>>operation>>operand_b){
			double prior_result = history.use_previous_result(index);
			
			switch(operation){
				case '+': result = calculator.addition(prior_result, operand_b); break;
				case '-': result = calculator.subtraction(prior_result, operand_b); break;
				case '*': result = calculator.multiplication(prior_result, operand_b); break;
				case '/': result = calculator.division(prior_result, operand_b); break;
				case '^': result = calculator.exponentiation(prior_result, operand_b); break;
			}

			expression = "@" + std::to_string(int(index)) + " " + operation + " " + history.formatNumber(operand_b);
			if(log_history) history.add_entry(expression, result);
			return result;
		}
	throw std::invalid_argument("\033[31mError: Invalid operation (use '+', '-', '*', '/', '^').\033[0m");
	}
}