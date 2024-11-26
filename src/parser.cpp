#include "../include/parser.h"
#include <stdexcept>

namespace parser{

	std::vector<std::string> Parser::tokenizeExpression(const std::string& user_input){

		std::vector<std::string> output;
		std::string token_builder;

		for(unsigned i = 0; i < user_input.length(); i++){

			char token = user_input[i];

			if(std::isspace(token))
				continue;

			if(isdigit(token) || token == '.')
				token_builder += token;
			else{

				if(!(token_builder.empty())){
					output.push_back(token_builder);
					token_builder.clear();	
				}

				if(token == '(' || token == ')')
					output.push_back(std::string(1, token));
				else if(parser::Parser::pemdas.find(std::string(1, token)) != parser::Parser::pemdas.end()){

					if(token == '-' && (output.empty() || output.back() == "(" || parser::Parser::pemdas.find(output.back()) != parser::Parser::pemdas.end()))
						token_builder += token; 
					else
						output.push_back(std::string(1, token));

				}else{
					throw std::invalid_argument("Invalid character: " + std::string(1, token));
				}
			}
		}

		if(!(token_builder.empty()))
		 output.push_back(token_builder);

		return output;
	}


	std::vector<std::string> Parser::convertToPostfix(const std::vector<std::string>& token_vector){

		std::vector<std::string> outputQueue;
		std::vector<std::string> operatorStack;

		for(const std::string& token : token_vector){

			if(isdigit(token[0]) || (token.size() > 1 && token[0] == '-' && isdigit(token[1])))
				outputQueue.push_back(token); 
			else if(pemdas.find(token) != pemdas.end()){

				while(!operatorStack.empty() && pemdas.find(operatorStack.back()) != pemdas.end() && pemdas[operatorStack.back()] >= pemdas[token]){
						outputQueue.push_back(operatorStack.back());
						operatorStack.pop_back();
				}

				operatorStack.push_back(token); 	

			}else if(token == "(")
				 operatorStack.push_back(token);

			 else if(token == ")"){

				while(!operatorStack.empty() && operatorStack.back() != "("){
					outputQueue.push_back(operatorStack.back());
					operatorStack.pop_back();
				}

				if(!operatorStack.empty() && operatorStack.back() == "(")
					operatorStack.pop_back();
				else
					throw std::invalid_argument("Mismatched parentheses in expression.");

			}else
				throw std::invalid_argument("Invalid token in expression: " + token);
		}

		while(!operatorStack.empty()){
			outputQueue.push_back(operatorStack.back());
			operatorStack.pop_back();
		}

		return outputQueue; 
	}


}//End of namespace parser.