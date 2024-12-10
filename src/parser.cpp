#include "../include/parser.h"
#include <stdexcept>

namespace parser{

	/*
	 * @function: tokenizeExpression()
	 * @params: type - string, pass-by-ref the user_input
	 * @brief:
	 * This function is passed the user_input from main.cpp
	 * it utilizes two local variables a string and a vector of strings
	 * as well as a main for loop to iterate through the user_input.
	 * 
	 * - The goal of the function is to break the expression down into individual
	 *   "tokens" of type string and store them within the vector for later processing.
	 * 
	 * - The tokenizer handles a decent amount of edge cases relative to the scope of the program,
	 *   i.e. it identifies unary negation vs binary subtraction, it also accounts for invalid operators.
	 *   Also, I have the capability to add more operators easily with this implementation.
	 * 
	 * The loop accomplishes this tokenization of individual operators and operands (and parentheses) 
	 * by leveraging various branches, conditional if, else if, and else blocks. Also, accounting for 
	 * whitespace, by simply iterating past them.
	 */
	std::vector<std::string> Parser::tokenizeExpression(const std::string& user_input){

		std::vector<std::string> output;					// Houses the individual tokens
		std::string token_builder;							/* Holds all tokens prior to being sent to vector, 
															  the thought here is to handle those tokens that may 
															  have several constituents, think both cases a singular 
															  operator and a decimal or negative number built of 
															  several characters. */
		for(unsigned i = 0; i < user_input.length(); i++){	//Main loop of the func, simply iterate through the len of the input char by char.

			char token = user_input[i];						//Break user input into characters, store each char within 'token'.

			if(std::isspace(token))
				continue;									//Skip whitespace, iterate past it.

			if(isdigit(token) || token == '.') 				//The main conditional blocks, if the token is an integer its added immediately to the token_builder, if not the logic in the else block is tested against the token (current char within the user_input string).
				token_builder += token;
			else{

				if(!(token_builder.empty())){				//The else block is only entered if the token isn't a number, so any operator or parenthesis is accounted for.
					output.push_back(token_builder);		//If the token builder was previously building a number lets use this expression as an example '2.35 + 1.65', after iterating through 2, ., 3, and 5 
						token_builder.clear();					//the whitespace is skipped above then the '+' token triggers the else block, when the else block is entered if the token_builder has anything within it
				}											//using the example it will have 2.35 within it, that token is pushed to the vector and then the token_builder is manually cleared as to avoid any potential errors for building future tokens.

				if(token == '(' || token == ')')			//If the token is a parentheses then convert the char into a string and put into the back (top) of the vector. 
					output.push_back(std::string(1, token));
															//else if, convert the token into a string since my pemdas map is comprised of string values, check if the token is a value (operator) within pemdas map.
				else if(parser::Parser::pemdas.find(std::string(1, token)) != parser::Parser::pemdas.end()){

					if(token == '-' && (output.empty() || output.back() == "(" || parser::Parser::pemdas.find(output.back()) != parser::Parser::pemdas.end()))
						token_builder += token; 			//If the character is a unary '-' symbol I handle this by simply checking for a few cases, either its the first character within the expression i.e. '-5 + 2', it follows an open paren i.e. '1 + (-5 * 2)', it's subsequent to another operator i.e. '1 + -5'.
					else									//Also, after the unary '-' symbol is added to the token_builder the function will then reach the end of the parent else block and then iterate to the next character being something like '-5' it accounts for the number as explained above.
						output.push_back(std::string(1, token)); //else (otherwise) the current token is an operator within pemdas, add it to the vector.

				}else{
					throw std::invalid_argument("Invalid character: " + std::string(1, token)); //If no conditions are met within the if or else blocks the rational here is that it's an unsupported token. So, throw an error and identify the unsupported character.
				}
			}
		}

		if(!(token_builder.empty()))						//At the end of the expression there will be a remaining number within the token_builder, the for loop is exited and the token is accounted for here
		 output.push_back(token_builder);					//By verifying the token_builder is not empty, and adding the token to the vector. i.e. '5 + 5 - 2' once the for loop iterates to the 2 at the end of the expression,
															//there isn't another token to force the else block to run and flush the token into the vector. This takes care of that.
		return output;			
	}//tokenizeExpression().

	/*
	 * @function: convertToPostfix()
	 * @params: vector of type string, token_vector created from the tokenizer
	 * @brief:
	 * This function is passed the previously created vector of tokens, it utilizes
	 * two vectors both of type string, outputQueue to hold the new postfix (RPN) format
	 * and the operatorStack which acts as a FILO stack. The function has a main for loop which
	 * iterates through each token within the infix formatted token_vector.
	 * 
	 * - The goal of the function is to read the infix formatted expression (as tokens within a vector)
	 *   and to return it formatted as a postfix expression. i.e. '2 + 2 - 1' -> '2 2 + 1 -'
	 * 
	 * - This function works in tandem with the tokenizer as a part of my shunting yard algorithm 
	 *   implementation. However the shunting yard algo utilizes stacks and queues typically, I achieve 
	 *   the same result here with vectors acting as my queue and my stack. 
	 *   Stacks are a part of the STL and can utilize vectors as one of their underlying containers; deriving 
	 *   their member functions.
	 * 
	 * - I use conditional branching and nested within the branches I utilize while loops to pop operators 
	 *   off the stack and into the output queue.   
	 */
	std::vector<std::string> Parser::convertToPostfix(const std::vector<std::string>& token_vector){

		std::vector<std::string> outputQueue;															//Holds the new postfix (RPN) format	
		std::vector<std::string> operatorStack;															//FILO stack, holds operators temporarily

		for(const std::string& token : token_vector){													//Main loop of the function, iterate through each token within the token_vector.

			if(std::isdigit(token[0]) || (token.length() > 1 && token[0] == '-' && std::isdigit(token[1])))
				outputQueue.push_back(token); 															//If the token is either a number or a negative number then add it to the output queue.
			else if(pemdas.find(token) != pemdas.end()){

				while(!operatorStack.empty() && pemdas.find(operatorStack.back()) != pemdas.end() && pemdas.at(operatorStack.back()) >= pemdas.at(token)){
						outputQueue.push_back(operatorStack.back()); 									//If the operatorStack isn't empty AND the operator on the top of the stack is an operator with a precedence that
						operatorStack.pop_back();														//is greater than or equal to the current operator, then pop the operator from the stack and add it to the outputQueue.
				}

				operatorStack.push_back(token); 														//Otherwise the stack has no operator, or the operator is less than the value of any operator on the stack currently.

			}else if(token == "(")																		//Open paren marks the beginning of a sub expression in RPN
				 operatorStack.push_back(token);														//add it to operatorStack.

			else if(token == ")"){																		//Closing paren mark the end of the sub expression

				while(!operatorStack.empty() && operatorStack.back() != "("){							//If the token is a closing paren, loop until the open paren is encountered or the stack is empty.
					outputQueue.push_back(operatorStack.back());										//get the operator ontop of the operatorStack, push it into the outputQueue.
					operatorStack.pop_back();															//Pop that operator from the stack.
				}


				if(!operatorStack.empty() && operatorStack.back() == "(")								//The last loop stopped after encountering an open paren, it didn't discard that open paren from the operatorStack
					operatorStack.pop_back();															//that's taken care of here.
				else
					throw std::invalid_argument("Mismatched parentheses in expression.");				//otherwise there was a mismatched paren.

			}else
				throw std::invalid_argument("Invalid token in expression: " + token);                   //handles any possibility of invalid tokens that somehow got parsed and passed to be arranged into RPN. 
		}

		while(!operatorStack.empty()){																    //If there are any operators left in the stack
			outputQueue.push_back(operatorStack.back());											    //push into ouputQueue and then pop it off the stack.
			operatorStack.pop_back();
		}

		return outputQueue; 
	}//convertToPostfix().


	const std::map<std::string, int> Parser::pemdas = {												    //This map houses the operators and their precedence values.							
        {"+", 2}, {"-", 2}, {"*", 3}, {"/", 3},
        {"^", 4}
    };

}//End of namespace parser.