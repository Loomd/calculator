// main implementation file for calculator, handles math operations.

#include "../include/calculator.h"
#include <iostream>

namespace calculator {
    void Calculator::display_menu() const {
        std::cout<<"\033[32m==================CLI Calculator=================="<<std::endl
                 <<"Suported operations: "<<std::endl
                 <<" Addition '+'"<<std::endl
                 <<" Subtraction '-'"<<std::endl
                 <<" Multiplication '*'"<<std::endl
                 <<" Division  '/'"<<std::endl
                 <<" Exponentiation '^'\033[0m"<<std::endl;
    }

    double Calculator::addition(double operand_a, double operand_b) { return operand_a + operand_b; }

    double Calculator::subtraction(double operand_a, double operand_b) { return operand_a - operand_b; }

    double Calculator::multiplication(double operand_a, double operand_b) { return operand_a * operand_b; }

    double Calculator::division(double operand_a, double operand_b) { 
        if(operand_b == 0) throw std::invalid_argument("\033[31mError: Division by zero\033[0m");
        return operand_a / operand_b; 
    }

    double Calculator::exponentiation(double operand_a, double operand_b) {
        double result{1};
        if(operand_b == 0) return result;
        else if(operand_a == 0) throw std::invalid_argument("\033[31mError: 0^x is undefined\033[0m");
        for(int i = 0; i < operand_b; i++){ result *= operand_a; }
        return result;
    }
}