/* @brief History management header
** Defines the History class for storing and managing calculation history.
*/

#ifndef HISTORY_H
#define HISTORY_H
#include <vector>
#include <string>
#include <iomanip>

namespace history{
	class History{
		public:
			//Structure to hold individual calculation records
			struct Entry{
				int index;                  //Sequential line number for reference
				std::string expression;     //The mathematical expression entered
				char operation;             //The mathematical operator used
				double result;              //The calculated result
			};

			std::vector<Entry> history_log; //Container for all calculation records

			//History management functions
			void add_entry(std::string expression, double result);
			void display_history() const;
			double use_previous_result(int index) const;
			void clear_history();

			//Function for number formatting
			std::string formatNumber(double num) const;
	};
}
#endif