#include "history.h"

class DeleteDepartment: public Command {
private:
    std::string department_name;
    Department deleted_department;
public:
    DeleteDepartment(char file_name[], std::string name);
    DeleteDepartment(Company * cmp, std::string name);
    bool execute();
    void undo();
};

class DeleteEmployee: public Command {
private:
    std::string department_name;
    std::string employee_name;
    Employee deleted_employee;
public:
    DeleteEmployee(char file_name[], std::string dp_name, std::string emp_name);
    DeleteEmployee(Company * cmp, std::string dp_name, std::string emp_name);
    bool execute();
    void undo();
};

class AddDepartment: public Command {
private:
    std::string department_name;
public:
    AddDepartment(Company * cmp, std::string dp_name);
    bool execute();
    void undo();
};

class AddEmployee: public Command{
private:
    std::string department_name;
    std::string employee_name;
public:
    AddEmployee(Company * cmp, std::string dp_name, std::string emp_name);
    bool execute();
    void undo();
};

class ChangeDepartmentName: public Command {
private:
    std::string old_department_name;
    std::string new_department_name;
public:
    ChangeDepartmentName(Company * cmp, std::string old_name, std::string new_name);
    bool execute();
    void undo();
};

class ChangeEmployeeAttribute: public Command {
private:
    std::string department_name;
    std::string employee_name;
    std::string attribute_name;
    std::string new_attribute_value;
    std::string old_attribute_value;
public:
    ChangeEmployeeAttribute(Company * cmp, std::string dep_name, std::string emp_name, std::string attr_name, std::string attr_value);
    bool execute();
    void undo();
};


class Save: public Command {
    char * file_name;
public:
    Save(Company * cmp, char * file);
    bool execute();
    void undo();
};


class Print: public Command {
public:
    Print(char file_name[]);
    Print(Company * cmp);
    bool execute();
    void undo();
};

class Help: public Command {
public:
    bool execute();
    void undo();
};

class Undo: public Command {
private:
    History * history;
public:
    Undo(History * command_history);
    bool execute();
    void undo();
};
