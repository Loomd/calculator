#include "../include/ui.h"
#include <iostream>

namespace ui
{
    void Ui::display_menu() const{
        std::cout<<"\033[32m==================CLI Calculator=================="<<std::endl
                 <<"Suported operations: "<<std::endl
                 <<" Addition '+'"<<std::endl
                 <<" Subtraction '-'"<<std::endl
                 <<" Multiplication '*'"<<std::endl
                 <<" Division  '/'"<<std::endl
                 <<" Exponentiation '^'\033[0m"<<std::endl;
    }

    void Ui::display_help() const{
        std::cout<<"\033[32m==================CLI Calculator=================="<<std::endl
                 <<"Supported operations: "<<std::endl
                 <<"\tAddition '+': a + b"<<std::endl
                 <<"\tSubtraction '-': a - b"<<std::endl
                 <<"\tMultiplication '*': a * b"<<std::endl
                 <<"\tDivision  '/': a / b"<<std::endl
                 <<"\tExponentiation '^': a ^ b"<<std::endl;
        std::cout<<"Supported commands: "<<std::endl
                 <<"\texit - Exits the program"<<std::endl
                 <<"\tmenu - Displays the menu"<<std::endl
                 <<"\thelp - Displays the help"<<std::endl
                 <<"\thistory - Displays the history"<<std::endl
                 <<"\tclear history - Clears the history"<<std::endl
                 <<"\t@ - Accesses a previous result: @[index]\033[0m"<<std::endl<<std::endl;
    }

}//namespace ui
