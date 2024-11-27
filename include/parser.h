#ifndef PARSER_H
#define PARSER_H
#include <map>
#include <string>
#include <vector>

namespace parser{

    class Parser{

        public:

            static const std::map<std::string, int> pemdas;

            std::vector<std::string> tokenizeExpression(const std::string& user_input);
            std::vector<std::string> convertToPostfix(const std::vector<std::string>& token_vector);

    };

}//namespace parser
#endif