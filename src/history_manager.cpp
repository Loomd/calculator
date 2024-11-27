#include "../include/history_manager.h"
#include <iostream>
#include <iomanip>
#include <sstream>
#include <cmath>

namespace history_manager{

    std::vector<History_manager::Entry> History_manager::history;
    

    void History_manager::add_entry(std::string& user_input, std::string result){
        Entry new_entry;
        new_entry.index = history.size() + 1;
        new_entry.expression = user_input;
        new_entry.result = format_result(result);
        history.push_back(new_entry);
    }
    

    void History_manager::clear_history(){
        History_manager::history.clear();
    }
    

    double History_manager::use_previous_result(int index){
        return std::stod(History_manager::history[index - 1].result);
    }


    void History_manager::display_history(){
  
        for(auto& entry : History_manager::history){
            std::cout<<entry.index<<". "<<entry.expression<<" = "<<entry.result<<std::endl;
        }
    }


    std::string History_manager::format_result(const std::string& result){

        std::stringstream formatted_result;
        double value = std::stod(result);

        if(value == std::floor(value)){
        formatted_result<<std::fixed<<std::setprecision(0)<<value;
        }else{
            formatted_result<<std::defaultfloat<<value;
        }

        return formatted_result.str();
    }


}//namespace history_manager.