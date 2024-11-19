// token based parser, for calculator. takes buffer and handles identifying and tokenizing commands, operands, operators,
// into a enum or struct. which ever data structure makes more sense and is more elegant.

#ifndef PARSER_H
#define PARSER_H
#include <sstream>
#include <iostream>
#include <string>
#include "../include/calculator.h"

namespace parser {
    class Parser {
        public:
            std::istringstream buffer(std::string user_input);
	        double evaluateSimpleExpression(const std::string& input, calculator::Calculator& calc);
    };
}
#endif