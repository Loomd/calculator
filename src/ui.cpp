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

}//namespace ui
