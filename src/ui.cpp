#include "../include/ui.h"
#include <iostream>

namespace ui{

    /*
     * @function: display_menu()
     * @params: none
     * @brief: 
     * This function outputs to the screen the list of currently available operations the calculator
     * can perform.
     */
    void Ui::display_menu() const{
        std::cout<<"\033[32m=======================CLI Calculator========================"<<std::endl
                 <<"SUPPORTED OPERATIONS: "<<std::endl
                 <<"- Addition '+'"<<std::endl
                 <<"- Subtraction '-'"<<std::endl
                 <<"- Multiplication '*'"<<std::endl
                 <<"- Division  '/'"<<std::endl
                 <<"- Exponentiation '^'\033[0m"<<std::endl;
    }//display_menu().

    /*
     * @function: display_help()
     * @params: none
     * @brief: 
     * This function outputs to the screen a comprehensize list of commands and operations that the
     * calculator can perform. It also provides the syntax required for the user_input to be valid.
     */
    void Ui::display_help() const{
        std::cout<<"\033[32m==================CLI Calculator Help Screen=================="<<std::endl
                 <<"SUPPORTED OPERATIONS: "<<std::endl
                 <<"- Addition '+'                   : a + b"<<std::endl
                 <<"- Subtraction '-'                : a - b"<<std::endl
                 <<"- Multiplication '*'             : a * b"<<std::endl
                 <<"- Division '/'                   : a / b"<<std::endl
                 <<"- Exponentiation '^'             : a ^ b"<<std::endl
                 <<"- Format                         : a + b * (-c / d^e)"<<std::endl;
        std::cout<<"SUPPORTED COMMANDS: "<<std::endl
                 <<"- 'exit'                         : Exits the program"<<std::endl
                 <<"- 'menu'                         : Displays the menu"<<std::endl
                 <<"- 'help'                         : Displays the help screen"<<std::endl
                 <<"- 'history'                      : Displays the history"<<std::endl
                 <<"- 'clear history'                : Clears the history"<<std::endl
                 <<"- 'load history'                 : Loads the history from a file: load [filename]"<<std::endl
                 <<"- 'save history'                 : Saves the history to a file: save [filename]"<<std::endl
                 <<"- '@': Use a previous result     : @[index]\033[0m"<<std::endl<<std::endl;
    }//display_help().


}//namespace ui