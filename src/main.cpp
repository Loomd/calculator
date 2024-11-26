#include "../include/parser.h"
#include "../include/ui.h"
#include "../include/calculations.h"
#include <iostream>

int main(){

    parser::Parser parser;
    ui::Ui ui;
    calculations::Calculations calc;

    bool running{true};
    std::string user_input{" "};

    ui.display_menu();

    while(running){

        try{
            std::cout<<"\033[35m>\033[0m";
            std::getline(std::cin, user_input);

            std::vector<std::string> postfix_vector = parser.convertToPostfix(parser.tokenizeExpression(user_input));
            for(const auto& token : postfix_vector){
                std::cout<<token<<" ";
            }
            std::cout<<"\n";
            //std::cout<<"\033[33m"<<calc.evaluatePostfix(postfix_vector)<<"\033[0m\n";

        }catch(const std::invalid_argument& error){
            std::cout<<"\033[31mError: "<<error.what()<<"\033[0m\n";
        }
    }

    return 0;
}