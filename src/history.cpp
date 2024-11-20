// history implementation file, for calculator. handles data structure for storing, retrieving indexes for reusability within expressions
// and displaying history of operations.

#include "../include/history.h"
#include <iostream>

namespace history{

    void History::display_history() const {
        for(const auto& entry : history_log){
            std::cout<<entry.index<<". "<<entry.expression<<" = "<<entry.result<<std::endl;
        }
    }

	void History::clear_history() { history_log.clear(); }

    void History::add_entry(std::string expression, double result){
        Entry record;
        record.expression = expression;
        record.result = result;
        record.index = history_log.size() + 1;
        history_log.push_back(record);
    }

	int History::use_previous_result(int index) const { return history_log[index].result; }


}