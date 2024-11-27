#ifndef CALCULATIONS_H
#define CALCULATIONS_H
#include <vector>
#include <string>

namespace calculations{

    class Calculations{

        public:

            double evaluatePostfix(const std::vector<std::string>& postfix_vector);
            std::string calculate(const std::string& operation, const std::string& operandA, const std::string& operandB);
    };

}//namespace calculations.
#endif