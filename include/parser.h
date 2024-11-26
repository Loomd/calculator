#ifndef PARSER_H
#define PARSER_H
#include <map>
#include <string>
#include <vector>

namespace parser{

    class Parser{

        public:

            std::map<std::string, int> pemdas = {
                {"+", 2}, {"-", 2}, {"*", 3}, {"/", 3},
                {"^", 4}
            };

            std::vector<std::string> tokenizeExpression(const std::string& user_input);
            std::vector<std::string> convertToPostfix(const std::vector<std::string>& token_vector);

    };

}//namespace parser
#endif