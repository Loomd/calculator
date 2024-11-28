#ifndef HISTORY_MANAGER_H
#define HISTORY_MANAGER_H
#include <vector>
#include <string>

namespace history_manager{

    class History_manager{

        public:

        struct Entry{
				int index;                  //Line number for reference
				std::string expression;     //The mathematical expression entered (user_input)
				char operation;             //The mathematical operator used
				std::string result;         //The calculated result
		};

        static std::vector<Entry> history;
    
        void add_entry(std::string& user_input, std::string result);
		void display_history();
		double use_previous_result(int index);
		void clear_history();
        std::string format_result(const std::string& result);
		void save_history();
		void load_history();

    };


}//namespace history_manager.
#endif