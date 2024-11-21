// token based parser, for calculator. takes buffer and handles identifying and tokenizing commands, operands, operators,
// into a enum or struct. which ever data structure makes more sense and is more elegant.

#ifndef PARSER_H
#define PARSER_H
#include "../include/calculator.h"
#include "../include/history.h"
#include <string>

namespace parser {
    class Parser {
        public:

	        double evaluateSimpleExpression(const std::string& input, calculator::Calculator& calculator, history::History& history);
            double evaluateSquareRoot(const std::string& input, calculator::Calculator& calculator, history::History& history);
            double usePriorAnswer(const std::string& input, calculator::Calculator& calcualtor, history::History& history);
    };
}
#endif