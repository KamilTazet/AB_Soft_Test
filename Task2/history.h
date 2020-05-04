#include <stack>
#include "command.h"


class History {
private:
    std::stack<Command *> history;
public:
    void save_command(Command * cmd);
    void undo_last_command();
};
