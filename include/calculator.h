/* @brief Calculator class header
** Defines calculator functionality and available operations.
*/

#ifndef CALCULATOR_H
#define CALCULATOR_H

#include <string>

namespace calculator{
    class Calculator{
        public:
            //Shows available operations
            void display_menu() const;

            //Basic math operations - each takes two numbers and returns result
            double addition(double operand_a, double operand_b);
            double subtraction(double operand_a, double operand_b);
            double multiplication(double operand_a, double operand_b);
            double division(double operand_a, double operand_b);
            
            //More operations
            double exponentiation(double operand_a, double operand_b);  //Raises a to power of b
            double squareRoot(double expression);                       //Finds square root

            /* Features for future updates:
            ** double logic_evaluation(std::string expression) const;
            ** const int pi{3.14159265358979323846264338327950288};
            ** double trigonometric_evaluation(std::string expression) const;
            ** double logarithmic_evaluation(std::string expression) const;
            ** double algebraic_evaluation(std::string expression) const;
            ** double factorial(double expression) const;
            */
    };
}
#endif