// calculator, main driver for my calculator program, handles math operations.

#ifndef CALCULATOR_H
#define CALCULATOR_H

#include <string>

namespace calculator {
    class Calculator{
        public: 
            void display_menu() const;

            double addition(double operand_a, double operand_b);

            double subtraction(double operand_a, double operand_b);

            double multiplication(double operand_a, double operand_b);

            double division(double operand_a, double operand_b);

            double exponentiation(double operand_a, double operand_b);

            /* Future implementation.
            ** double square_root(double expression) const;
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