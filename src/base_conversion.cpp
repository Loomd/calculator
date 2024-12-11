#include "../include/base_conversion.h"
#include <string>
#include <iostream>

namespace base_conversion {

    /*
     * base_conversion namespace is comprised of the actual conversion algorithms 
     * and handling a separate history which will be a feature integrated soon.
     * 
     * As of this version of the program can handle binary to decimal or decimal to binary translations.
     * In the future I plan on implementing hexadecimal and octal translations.
     * 
     * void get_base_info()
     *  - This is called within main.cpp when the user inputs the 'base' command; a base conversion.
     *  - Prompt to collect the base and the value.
     * int binary_to_base10(std::string& user_input)
     *  - Converts binary to decimal.
     * std::string base10_to_binary(std::string& user_input)
     *  - Converts decimal to binary.
     * ---NOT FULLY IMPLEMENTED---
     * void add_to_conversion_history(conversion& Conversion)
     *  - Adds the conversion to the conversion history.
     */

    void get_base_info(){
        //Prompt to collect the base and the value.
        std::cout<<"\033[32m=======================BINARY/DECIMAL CONVERTER=======================\n"
                 <<"- Format: <base> <number>\n"
                 <<"- Supported bases: 'bin' for binary, 'dec' for decimal\n"
                 <<"- Examples: bin 1010 -> 10 or dec 42 -> 101010\n"
                 <<"Enter conversion: \033[0m";

        //Collect the base and the value.
        std::string capture_data;
        getline(std::cin, capture_data);

        //If the user enters an empty string then return.
        if(capture_data.length() == 0) return;

        //Extract the base and the value from the user input.
        //User input is formatted as <base> <value> which is why the substrings start at index 0 and 4 respectively.
        std::string base{capture_data.substr(0, 3)};
        std::string value{capture_data.substr(4)};

        //If the base is binary then convert to decimal.
        //else if the base is decimal then convert to binary.
        //otherwise throw an error.
        if(base == "bin"){
            std::cout<<binary_to_base10(value)<<std::endl;
        }
        else if(base == "dec"){
            std::cout<<base10_to_binary(value)<<std::endl;
        }
        else{
            throw std::invalid_argument("Base not supported");
        }

    }


    int binary_to_base10(std::string& user_input){

        //Convert the binary string to an integer.
        int base10_representation{0};

        //Iterate through each bit in the binary string.
        for(auto& bit : user_input){
            //If the bit (character within the string) is 1 then shift the bits left 1 and add 1 to LSB.
            //Otherwise shift the bits left 1.
            bit == '1' ? base10_representation = (base10_representation << 1) | 1 : base10_representation = base10_representation << 1; 
        }

        //Create a new conversion object and add it to the conversion history.
        conversion new_conversion{user_input, base10_representation};
        add_to_conversion_history(new_conversion);

        return base10_representation;
    }


    std::string base10_to_binary(std::string& user_input){

        //Convert the decimal string to an integer.
        int base10{std::stoi(user_input)};

        //If the input is 0 then return 0.
        if(base10 == 0) return "0";

        //Initialize a string to hold the binary translation.
        //Also, an int variable to hold the original base10Value
        std::string binary{" "};
        int original_base10{base10};

        while(base10 != 0){                                             //While the input is not 0
            binary = (base10 & 1 ? '1' : '0') + binary;                 //If the lsb of the base10 number's binary representation is 1 then prepend 1 to the string, otherwise prepend 0
            base10 /= 2;                                                //Divide the input by 2 which shifts the bits right 1.
        }

        conversion new_conversion{binary, original_base10};
        add_to_conversion_history(new_conversion);

        return binary;
    }


    void add_to_conversion_history(conversion& Conversion){
        //Add the conversions to the conversion history.
        //Not yet implemented.
        conversion_history.push_back(Conversion);
    }
};