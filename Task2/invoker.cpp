#include "invoker.h"


Invoker::Invoker(char * file_name): company(file_name) {
    this->file_name = file_name;
};
int Invoker::listen() {
    std::string command_line;
    for(;;) {
        Command * command;
        std::cout << "Введите команду (для завершения введите quit): " << std::endl;
        std::getline(std::cin, command_line);
        if(command_line == "delete_department") {
            std::string department_name;
            std::cout << "Введите название удаляемого департамента: " << std::endl;
            std::getline(std::cin, department_name);
            DeleteDepartment * del_dep = new DeleteDepartment(&(this->company), department_name);
            command = del_dep;
        }
        else if(command_line == "delete_employee") {
            std::string department_name;
            std::string employee_name;
            std::cout << "Введите: " << std::endl;
            std::cout << "Название департамента удаляемого сотрудника: " << std::endl;
            std::getline(std::cin, department_name);
            std::cout << "ФИО удаляемого сотрудника: " << std::endl;
            std::getline(std::cin, employee_name);
            DeleteEmployee * del_emp = new DeleteEmployee(&(this->company), department_name, employee_name);
            command = del_emp;
        }
        else if(command_line == "add_department") {
            std::string department_name;
            std::cout << "Введите название добавляемого департамента: " << std::endl;
            std::getline(std::cin, department_name);
            AddDepartment * add_dep = new AddDepartment(&(this->company), department_name);
            command = add_dep;
        }
        else if(command_line == "add_employee") {
            std::string department_name;
            std::string employee_name;
            std::cout << "Введите: " << std::endl;
            std::cout << "Название департамента добавляемого сотрудника: " << std::endl;
            std::getline(std::cin, department_name);
            std::cout << "ФИО добавляемого сотрудника: " << std::endl;
            std::getline(std::cin, employee_name);
            AddEmployee * add_emp = new AddEmployee(&(this->company), department_name, employee_name);
            command = add_emp;
        }
        else if(command_line == "change_department_name") {
            std::string old_department_name;
            std::string new_department_name;
            std::cout << "Введите: " << std::endl;
            std::cout << "Название изменяемого департамента: " << std::endl;
            std::getline(std::cin, old_department_name);
            std::cout << "Новое название департамента: " << std::endl;
            std::getline(std::cin, new_department_name);
            ChangeDepartmentName * chng_dep = new ChangeDepartmentName(&(this->company), old_department_name, new_department_name);
            command = chng_dep;
        }
        else if(command_line == "change_employee_attribute") {
            std::string department_name;
            std::string employee_name;
            std::string attribute_name;
            std::string attribute_value;
            std::cout << "Введите: " << std::endl;
            std::cout << "Название департамента изменяемого сотрудника: " << std::endl;
            std::getline(std::cin, department_name);
            std::cout << "ФИО изменяемого сотрудника: " << std::endl;
            std::getline(std::cin, employee_name);
            std::cout << "Название изменяемого аттрибута: " << std::endl;
            std::getline(std::cin, attribute_name);
            std::cout << "Новое значение аттрибута: " << std::endl;
            std::getline(std::cin, attribute_value);
            ChangeEmployeeAttribute * chng_emp = new ChangeEmployeeAttribute(&(this->company), department_name, employee_name, attribute_name, attribute_value);
            command = chng_emp;
        }
        else if(command_line == "save") {
            Save * save_com = new Save(&(this->company), this->file_name);
            command = save_com;
        }
        else if(command_line == "print") {
            Print * prnt_com = new Print(&(this->company));
            command = prnt_com;
        }
        else if(command_line == "undo") {
            Undo * undo_com = new Undo(&(this->history));
            command = undo_com;
        }
        else if(command_line == "help") {
            Help * help_com = new Help();
            command = help_com;
        }
        else if(command_line == "quit"){
            return 0;
        }
        else {
            std::cout << "Неизвестная команда" << std::endl;
        }
        if(command->execute()) {
            history.save_command(command);
        }
    }
};
