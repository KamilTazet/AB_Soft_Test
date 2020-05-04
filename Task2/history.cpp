#include "history.h"


void History::save_command(Command * cmd) {
    this->history.push(cmd);
};

void History::undo_last_command() {
    if(!history.empty()) {
        this->history.top()->undo();
        Command * cmd = this->history.top();
        this->history.pop();
        delete cmd;
    }
    else {
        std::cout << "Нет операций для отмены" << std::endl;
    }
};
