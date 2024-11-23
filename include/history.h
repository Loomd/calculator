// history manager, for calculator, handles data structure for storing, retrieving indexes for resusability within expressions
// and displaying history of operations.

#ifndef HISTORY_H
#define HISTORY_H
#include <vector>
#include <string>

namespace history{
	class History{
		public:
			struct Entry{
				int index;                       // Line number
				std::string expression;          // Full mathematical expression
				std::vector<double> operands;    // Operands used in the expression
				char operation;                  // Operator (e.g., '+', '*')
				double result;                   // Computation result
			};

			std::vector<Entry> history_log;

			void add_entry(std::string expression, double result, double result2);

			void add_entry(std::string expression, double result);

			void display_history() const;

			int use_previous_result(int index) const;

			void clear_history();
	};
}
#endif