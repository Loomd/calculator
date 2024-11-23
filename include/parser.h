/* @brief Parser header
** Handles tokenization of operands and operators for the calculator.
*/

#ifndef PARSER_H
#define PARSER_H
#include "../include/calculator.h"
#include "../include/history.h"
#include <string>

namespace parser {
    class Parser {
        public:
            //Parsing functions for different types of expressions
            double evaluateSimpleExpression(const std::string& input, calculator::Calculator& calculator, history::History& history, bool log_history = true);    //Handles basic arithmetic operations
            double evaluateSquareRoot(const std::string& input, calculator::Calculator& calculator, history::History& history, bool log_history = true);          //Processes square root calculations
            double usePriorAnswer(const std::string& user_input, calculator::Calculator& calculator, history::History& history, bool log_history);                //Reuses previous calculation results
    };
}
#endif