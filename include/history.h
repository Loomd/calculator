// history manager, for calculator, handles data structure for storing, retrieving indexes for resusability within expressions
// and displaying history of operations.

#ifndef HISTORY_H
#define HISTORY_H
#include <vector>
#include <string>

namespace history {
    class History {
        public:
            std::vector<int, std::string> history_log;

            std::vector<int, std::string> display_history() const;

            int use_previous_result(int index) const;

            void clear_history() const;

            void save_history(int index, std::string expression) const;

    };
}

#endif