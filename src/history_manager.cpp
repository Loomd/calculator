#include "../include/history_manager.h"
#include <iostream>
#include <iomanip>
#include <sstream>
#include <cmath>
#include <fstream>

namespace history_manager{


    std::vector<History_manager::Entry> History_manager::history;
    

    void History_manager::add_entry(std::string& user_input, std::string result){
        Entry new_entry;
        new_entry.index = history.size() + 1;
        new_entry.expression = user_input;
        new_entry.result = format_result(result);
        history.push_back(new_entry);
    }//add_entry().
    

    void History_manager::clear_history(){
        History_manager::history.clear();
    }//clear_history().
    

    double History_manager::use_previous_result(int index){
        return std::stod(History_manager::history[index - 1].result);
    }//use_previous_result().


    void History_manager::display_history(){
  
        for(auto& entry : History_manager::history){
            std::cout<<entry.index<<". "<<entry.expression<<" = "<<entry.result<<std::endl;
        }
    }//display_history().


    std::string History_manager::format_result(const std::string& result){

        std::stringstream formatted_result;
        double value = std::stod(result);

        if(value == std::floor(value)){
        formatted_result<<std::fixed<<std::setprecision(0)<<value;
        }else{
            formatted_result<<std::defaultfloat<<value;
        }

        return formatted_result.str();
    }//format_result().


    void History_manager::save_history(){

        std::ofstream output;
        std::string filename;
        std::cout<<"Enter filename: ";
        std::cin>>filename;

        output.open(filename);
        
        for(auto& entry : History_manager::history){
            output<<entry.index<<". "<<entry.expression<<" = "<<entry.result<<std::endl;
        }

        output.close();
        std::cout<<"History saved to "<<filename<<std::endl;

    }//save_history().


    void History_manager::load_history(){

        std::cout<<"Enter file name: ";
        std::string filename;
        std::cin>>filename;

        std::ifstream file(filename);
        History_manager::clear_history();

        if(!file)
            throw std::invalid_argument("Unable to open file " + filename);

        std::string line;

        while(std::getline(file, line)){

            Entry entry;
            std::istringstream line_stream(line);

            line_stream>>entry.index;
            line_stream.ignore(2);
            std::getline(line_stream, entry.expression, '=');
            entry.expression.erase(entry.expression.find_last_not_of(" \t") + 1);
            line_stream.ignore(1);
            line_stream>>entry.result;

            history.push_back(entry);

        }

        file.close();

    }//load_history().


}//namespace history_manager.