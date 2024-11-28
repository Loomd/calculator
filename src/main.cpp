#include "../include/parser.h"
#include "../include/ui.h"
#include "../include/calculations.h"
#include "../include/history_manager.h"
#include <iostream>

int main(){

    parser::Parser parser;
    ui::Ui ui;
    calculations::Calculations calc;
    history_manager::History_manager history;

    bool running{true};
    std::string user_input{" "};

    ui.display_menu();

    while(running){

        try{
            user_input.clear();
            std::cout<<"\033[35m>\033[0m";
            std::getline(std::cin, user_input);

            if(user_input == "exit"){
                running = false;
            }else if(user_input == "menu"){
                ui.display_menu();
            }else if(user_input == "help"){
                ui.display_help();
            }else if(user_input == "history"){
                history.display_history();
            }else if(user_input == "clear history"){
                history.clear_history();
            }else if(user_input == "save history"){
                history.save_history();
                std::cin.ignore(1);
            }else if(user_input == "load history"){
                history.load_history();
                std::cin.ignore(1);
            }else if(user_input.empty() || user_input.find_first_not_of(" \t\n") == std::string::npos){
                continue;
            }else{
                std::vector<std::string> postfix_vector = parser.convertToPostfix(parser.tokenizeExpression(user_input));
                history.add_entry(user_input, std::to_string(calc.evaluatePostfix(postfix_vector)));
                std::cout<<"\033[36m"<<calc.evaluatePostfix(postfix_vector)<<"\033[0m\n";
            }

        }catch(const std::invalid_argument& error){
            std::cout<<"\033[31mError: "<<error.what()<<"\033[0m\n";
        }
    }

    return 0;
}