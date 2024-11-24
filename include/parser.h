/* @brief Parser header
** Handles tokenization of operands and operators for the calculator.
*/

#ifndef PARSER_H
#define PARSER_H
#include "../include/calculator.h"
#include "../include/history.h"
#include <string>
#include <map>

namespace parser {
    class Parser {
        public:
            
            //I felt keeping the pemdas map public was simple. Considering the scope of this program the potential overhead of a public member vs a static one I feel is negligible.
            //If you disagree, or feel i'm not appreciating this fact enough, i'd appreciate any mentoring on this topic.
            std::map<std::string, int> Parser::pemdas = {
                {"+", 1}, //'+' has lowest precedence
                {"-", 1}, //'-' has lowest precedence
                {"*", 2}, //'*' has a higher precedence
                {"/", 2}, //'/' has a higher precedence
                {"^", 3}  //'^' has the highest precedence
            };
            
            /*
            ** Shunting Yard Algorithm: "https://en.wikipedia.org/wiki/Shunting_yard_algorithm"
            ** 
            ** The Shunting Yard Algorithm is an algorithm which processes infix expressions. 
            ** In other words it converts a "normal" expression into a particular format called **postfix** (Reverse Polish Notation, RPN).
            **
            ** overview:
            ** Infix: "3 + 4 * (2 - 1)"        (how humans usually write math)
            ** Postfix (RPN): "3 4 2 1 - * +"  (expression after going through shunting yard algo)
            **
            ** How do I implement it:
            **
            **  std::vector<std::string> tokenizeExpression(const std::string& user_input);
            **  user_input is either a command or an expression
            **      - if user_input is an expression, I store all inputs initially as a string, tokens are parsed
            **        and added directly into a vector of strings, consider the expression "(1 + 2) + 3",
            **        the input is tokenized like so: ["(", "1", "+", "2", ")", "+", "3"]. 
            **        They are added into a vector in the order they were typed.
            **
            **  Once the user_input (if it's an expression) is parsed, any remaining "tokens" are placed in the vector.
            **
            ** Walthrough of an example: `3 + 4 * (2 - 1)`
            **
            ** Step 1: Start parsing, identify tokens (numbers, operators, or parentheses):
            **
            ** Parse user_input (the example in this case):
            ** token '3': it's a numeric value so place in vector -> vector state: ["3"]
            ** token '+': it's an operator within pemdas map, so place within vector -> vector state: ["3", "+"]
            ** token '4': it's a numeric value so place in vector -> vector state: ["3", "+", "4"]
            ** ...For brevity's sake the same process is repeated until the entire expression is parsed and added in the same manner.
            **
            ** Step 2: Convert to postfix (RPN):
            **
            */
            std::vector<std::string> tokenizeExpression(const std::string& user_input);
            std::vector<std::string> convertToPostfix(const std::vector<std::string>& token_vector);
            double evaluatePostfix(const std::vector<std::string>& postfix);

            double evaluateSimpleExpression(const std::string& input, calculator::Calculator& calculator, history::History& history, bool log_history = true);    //Handles basic arithmetic operations
            double evaluateSquareRoot(const std::string& input, calculator::Calculator& calculator, history::History& history, bool log_history = true);          //Processes square root calculations
            double usePriorAnswer(const std::string& user_input, calculator::Calculator& calculator, history::History& history, bool log_history);                //Reuses previous calculation results
    };
}
#endif