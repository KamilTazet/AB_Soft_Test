#include <stack>
#include <memory>
#include "command.h"


class History { //Класс истории изменений
private:
    std::stack<std::unique_ptr<Command>> history; //Стек изменений дляотмены
    std::stack<std::unique_ptr<Command>> redo_history; //Стек изменений для возврата после отмены
public:
    void save_command(std::unique_ptr<Command> cmd); //Сохранения команды для отмены
    void undo_last_command(); //Отмена последней команды
    void redo_last_command(); //Возврат отменённой команды
};
