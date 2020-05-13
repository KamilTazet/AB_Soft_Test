#include "history.h"


void History::save_command(std::unique_ptr<Command> cmd) {
    this->history.push(std::move(cmd));
    while(!redo_history.empty()) { //При выполнении новой команды после отмены дркгих команд происходит очищение истории возврата команд  
        std::unique_ptr<Command> cmd = std::move(this->redo_history.top());
        redo_history.pop();
    }
};

void History::undo_last_command() {
    if(!history.empty()) {
        this->history.top()->undo();
        std::unique_ptr<Command> cmd(std::move(this->history.top()));
        this->redo_history.push(std::move(cmd));
        this->history.pop();
    }
    else {
        std::cout << "Нет операций для отмены" << std::endl;
    }
};
void History::redo_last_command() {
    if(!redo_history.empty()) {
        this->redo_history.top()->execute();
        std::unique_ptr<Command> cmd(std::move(this->redo_history.top()));
        this->history.push(std::move(cmd));
        this->redo_history.pop();
    }
    else {
        std::cout << "Нет операций для возврата" << std::endl;
    }
};
