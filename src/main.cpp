/* @brief Main program entry point
** Initializes components and coordinates between calculator components.
*/

//Include components
#include "../include/calculator.h"    //Math operations
#include "../include/parser.h"        //Input processing
#include "../include/history.h"       //Calculation history
#include <stdexcept>                  //For error handling
#include <iostream>                   //For input/output

int main(){
    //Initialize objects for calculator, parser, and history tracking
    calculator::Calculator calculator;
    parser::Parser parser;
    history::History history;

    //Initialize variables
    bool running{true};                //Controls program loop
    std::string user_input;            //Stores user's input
    double result{0.0};                //Holds calculation result
    calculator.display_menu();         //Show available operations

    //Main program loop
    while(running){
        try{
            std::cout<<"\033[35m>\033[0m";        //Purple prompt symbol
            std::getline(std::cin, user_input);   //Get user input

            //Handle commands
            if(user_input == "exit"){             //Exit program
                running = false;
                continue;
            }else if(user_input == "menu"){       //Show menu
                calculator.display_menu();
                continue;
            }else if(user_input == "history"){    //Show calculation history
                history.display_history();
                continue;
            }else if(user_input == "clear"){      //Clear history
                history.clear_history();
                continue;
            }

            //Figure out what type of calculation to do
            if(user_input.find("sqrt") != std::string::npos)          //Square root
                result = parser.evaluateSquareRoot(user_input, calculator, history, true);
            else if(user_input.find("@") != std::string::npos)        //Use previous answer
                result = parser.usePriorAnswer(user_input, calculator, history, true);
            else                                                       //Basic math
                result = parser.evaluateSimpleExpression(user_input, calculator, history, true);

            //Show the formatted result
            std::cout<<history.formatNumber(result)<<"\n";

        }catch(const std::invalid_argument& error){
            std::cout<<"\033[31mError: "<<error.what()<<"\033[0m\n";
        }
    }
    return 0;
}