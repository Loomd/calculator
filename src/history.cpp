/* @brief History implementation
** Implements functionality for tracking and managing calculation history.
** Handles storage, retrieval, and display of calculation history.
*/

#include "../include/history.h"
#include <iostream>
#include <iomanip>
#include <sstream>
#include <cmath>

namespace history{
    //Shows all previous calculations
    void History::display_history() const{
        for(auto& entry : history_log){
            std::cout<<entry.index<<". "<<entry.expression<<" = "<<formatNumber(entry.result)<<std::endl;
        }
    }

    //Removes all saved calculations
    void History::clear_history(){ history_log.clear(); }

    //Saves a new calculation to history
    void History::add_entry(std::string expression, double result){
        Entry record;
        record.expression = expression;         //What the user typed
        record.result = result;                 //The answer
        record.index = history_log.size() + 1;  //Number them starting at 1
        history_log.push_back(record);          //Add to our list
    }

    //Gets a previous answer by its number
    //NOTE: UPGRADE THIS TO UTILIZE TWO ANSWERS FOR AN EXPRESSION.
    double History::use_previous_result(int index) const { return history_log[index - 1].result; }

    //Formats numbers look nice (e.g., 2.00 -> 2)
    std::string History::formatNumber(double num) const{
        std::ostringstream stream;                      //Initialize output stream
        stream<<std::fixed;                             //Make output stream use fixed point notation
        if(num == std::floor(num)) stream<<std::setprecision(0);
        else stream<<std::setprecision(2);
        stream<<num;                                    //Insert number into stream
        return stream.str();                            //Return formatted stream
    }
}