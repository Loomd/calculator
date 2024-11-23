/*
** @brief Main file for the calculator program
** houses initialized objects, and handles program flow.
*/
#include "../include/calculator.h"
#include "../include/parser.h"
#include "../include/history.h"
#include <stdexcept>
#include <iostream>

int main(){
    /* 
    ** @brief Object initialization
    ** modular handling of functionality, implemented separate classes to handle 
    ** related operations, easier to maintain and implement extended functionality.
    */
    calculator::Calculator calculator;
    parser::Parser parser;
    history::History history;

    bool running{true};
    std::string user_input;
    double result{0.0};
    calculator.display_menu();

    while(running){
        try{
            std::cout<<"\033[35m>\033[0m";
            std::getline(std::cin, user_input);

            if(user_input == "exit"){
                running = false;
                continue;
            }else if(user_input == "menu"){
                calculator.display_menu();
                continue;
            }else if(user_input == "history"){
                history.display_history();
                continue;
            }else if(user_input == "clear"){
                history.clear_history();
                continue;
            }

            //Check if the user input contains "sqrt" within the string.
            if(user_input.find("sqrt") != std::string::npos) result = parser.evaluateSquareRoot(user_input, calculator, history, true);
            //Check and see if user wants to use a prior answer.
            else if(user_input.find("@") != std::string::npos) result = parser.usePriorAnswer(user_input, calculator, history, true);
            //Otherwise, evaluate a simple mathematical expression.
            else result = parser.evaluateSimpleExpression(user_input, calculator, history, true);

            std::cout<<result<<"\n";

        }catch(const std::invalid_argument& error){
            std::cout<<"\033[31mError: "<<error.what()<<"\033[0m\n";
        }
    }
return 0;
}