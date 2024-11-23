/* @brief Calculator implementation
** Implements mathematical operations and user interface.
*/

#include "../include/calculator.h"
#include <iostream>

namespace calculator{
    //Shows menu with available operations
    void Calculator::display_menu() const{
        std::cout<<"\033[32m==================CLI Calculator=================="<<std::endl
                 <<"Suported operations: "<<std::endl
                 <<" Addition '+'"<<std::endl
                 <<" Subtraction '-'"<<std::endl
                 <<" Multiplication '*'"<<std::endl
                 <<" Division  '/'"<<std::endl
                 <<" Exponentiation '^'\033[0m"<<std::endl;
    }

    //Basic math operations
    double Calculator::addition(double operand_a, double operand_b) { return operand_a + operand_b; }
    double Calculator::subtraction(double operand_a, double operand_b) { return operand_a - operand_b; }
    double Calculator::multiplication(double operand_a, double operand_b) { return operand_a * operand_b; }
    double Calculator::division(double operand_a, double operand_b){
        if(operand_b == 0) throw std::invalid_argument("\033[31mError: Division by zero\033[0m");
        return operand_a / operand_b;
    }

    //Raises a number to a power: a^b
    double Calculator::exponentiation(double operand_a, double operand_b){
        double result{1};
        if(operand_b == 0) return result;                //Anything to power 0 is 1
        else if(operand_a == 0) throw std::invalid_argument("\033[31mError: 0^x is undefined\033[0m");

        for(int i = 0; i < operand_b; i++) result *= operand_a;
        return result;
    }

    //Calculates square root using Newton's method
    double Calculator::squareRoot(double operand_a){
        if(operand_a < 0) throw std::invalid_argument("\033[31mError: Cannot compute square root of negative number\033[0m");
        if(operand_a == 0) return 0;

        //Newton-Raphson method: x = (x + a/x) / 2
        double result{operand_a / 2}, precision{0.00001};
        for(int i = 0; i < 100; i++){
            result = (result + operand_a / result) / 2;
            if(std::abs(operand_a - result * result) <= precision) return result;
        }
        throw std::invalid_argument("\033[31mError: Could not compute square root\033[0m");
    }
}