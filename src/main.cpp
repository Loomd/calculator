#include "../include/parser.h"
#include "../include/ui.h"
#include "../include/calculations.h"
#include "../include/history_manager.h"
#include "../include/base_conversion.h"
#include <iostream>

/* Program entry point:
 * I utilize a boolean variable along with a main while loop to execute program logic
 * 
 * Project Purpose:
 * This program was an attempt to learn and gain pratical knowledge of: 
 *  - user-defined classes, modular (files and folders) design, and a practical application of 
 *    namesapces.
 * 
 * Core Functionality:
 * - The program's functionality is housed within objects/classes and namespaces.
 * 1. Parser:
 *    - Contains a PEMDAS map (operators as keys, precedence as values) for handling precedence.
 *    - Handles input validation and sanitization with tokenizing user input.
 *    - Converts infix expressions into postfix (RPN) expressions.
 * 2. UI:
 *    - Houses help and display menus.
 *    - All future menus should be eventually extracted to here.
 * 3. History_manager: 
 *    - The history_manager class houses the file i/o functionality.
 *    - Provides functionality to display, save, and clear history.
 * 4. Calculations:
 *    - 
 */

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
            std::cout<<"\033[35m>\033[0m";
            std::getline(std::cin, user_input);

            if(user_input.empty() || user_input.find_first_not_of(" \t\n") == std::string::npos)
                continue;

            if(user_input == "exit"){
                running = false;
            }else if(user_input == "menu"){
                ui.display_menu();
            }else if(user_input == "help"){
                ui.display_help();
            }else if(user_input == "base"){
                base_conversion::get_base_info();
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