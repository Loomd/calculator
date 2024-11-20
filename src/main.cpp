// Entry point for calculator program.
#include "../include/calculator.h"
#include "../include/parser.h"
#include "../include/history.h"
#include <stdexcept>

int main(){
    calculator::Calculator calculator;
    parser::Parser parser;
    history::History history;

    bool running{true};
    std::string user_input;
	//int index{1};
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
            }

            double result = parser.evaluateSimpleExpression(user_input, calculator, history);
            //history.add_entry(index, user_input, result);
            std::cout<<result<<"\n";


            //index++;
        }catch(const std::invalid_argument& error){
            std::cout<<"\033[31mError: "<<error.what()<<"\033[0m\n";
        }
    }
return 0;
}