#ifndef BASE_CONVERSION_H
#define BASE_CONVERSION_H

#include <string>
#include <vector>

namespace base_conversion{

    struct conversion{
        std::string binary_representation;
        int decimal_representation;
    };

    static std::vector<conversion> conversion_history;

    int binary_to_base10(std::string& user_input);
    std::string base10_to_binary(std::string& user_input);
    void add_to_conversion_history(conversion& Conversion);
    void get_base_info();
};

#endif