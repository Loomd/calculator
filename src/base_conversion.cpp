#include "../include/base_conversion.h"
#include <string>
#include <iostream>

namespace base_conversion {

    int binary_to_base10(std::string& user_input){

        int base10_representation{0};

        for(auto& bit : user_input){
            bit == '1' ? base10_representation = (base10_representation << 1) | 1 : base10_representation = base10_representation << 1;
        }

        conversion new_conversion{user_input, base10_representation};
        add_to_conversion_history(new_conversion);

        return base10_representation;
    }


    std::string base10_to_binary(std::string& user_input){

        int base10{std::stoi(user_input)};

        if(base10 == 0) return "0";

        std::string binary{" "};
        int original_base10{base10};

        while(base10 != 0){
            binary = (base10 & 1 ? '1' : '0') + binary;                 //If the lsb of the input is 1 then prepend 1 to the string, otherwise prepend 0
            base10 /= 2;                                                //Divide the input by 2, to shift right 1 bit.
        }

        conversion new_conversion{binary, original_base10};
        add_to_conversion_history(new_conversion);

        return binary;
    }


    void add_to_conversion_history(conversion& Conversion){

        conversion_history.push_back(Conversion);
    }
};