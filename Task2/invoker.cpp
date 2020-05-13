#include "invoker.h"


Invoker::Invoker(char * file_name): company(file_name) {
    this->file_name = file_name;
};
int Invoker::listen() {
    std::string command_line;
    for(;;) {
        std::unique_ptr<Command> command;
        std::cout << "Введите команду (для завершения введите quit): " << std::endl;
        std::getline(std::cin, command_line);
        if(command_line == "delete_department") {
            std::unique_ptr<Command> del_dep(new DeleteDepartment(&(this->company)));
            if(del_dep->set_data()) {
                command = std::move(del_dep);
            }
            else {
                continue;
            }
        }
        else if(command_line == "delete_employee") {
            std::unique_ptr<Command> del_emp(new DeleteEmployee(&(this->company)));
            if(del_emp->set_data()) {
                command = std::move(del_emp);
            }
            else {
                continue;
            }
        }
        else if(command_line == "add_department") {
            std::unique_ptr<Command> add_dep(new AddDepartment(&(this->company)));
            if(add_dep->set_data()) {
                command = std::move(add_dep);
            }
            else {
                continue;
            }
        }
        else if(command_line == "add_employee") {
            std::unique_ptr<Command> add_emp(new AddEmployee(&(this->company)));
            if(add_emp->set_data()) {
                command = std::move(add_emp);
            }
            else {
                continue;
            }
        }
        else if(command_line == "change_department_name") {
            std::unique_ptr<Command> chng_dep(new ChangeDepartmentName(&(this->company)));
            if(chng_dep->set_data()) {
                command = std::move(chng_dep);
            }
            else {
                continue;
            }
        }
        else if(command_line == "change_employee_attribute") {
            std::unique_ptr<Command> chng_emp(new ChangeEmployeeAttribute(&(this->company)));
            if(chng_emp->set_data()) {
                command = std::move(chng_emp);
            }
            else {
                continue;
            }
        }
        else if(command_line == "save") {
            std::unique_ptr<Command> save_com(new Save(&(this->company)));
            if(save_com->set_data()) {
                command = std::move(save_com);
            }
            else {
                continue;
            }
        }
        else if(command_line == "print") {
            // Print * prnt_com = new Print(&(this->company));
            std::unique_ptr<Command> prnt_com(new Print(&(this->company)));
            // command = prnt_com;
            command = std::move(prnt_com);
        }
        else if(command_line == "undo") {
            std::unique_ptr<Command> undo_com(new Undo(&(this->history)));
            command = std::move(undo_com);
        }
        else if(command_line == "redo") {
            std::unique_ptr<Command> redo_com(new Redo(&(this->history)));
            command = std::move(redo_com);
        }
        else if(command_line == "help") {
            std::unique_ptr<Command> help_com(new Help());
            command = std::move(help_com);
        }
        else if(command_line == "quit"){
            return 0;
        }
        else {
            std::cout << "Неизвестная команда" << std::endl;
            continue;
        }
        if(command->execute()) { //В случае успешного выполнения команды она добваляеться в историю изменений
            history.save_command(std::move(command));
        }
    }
};
