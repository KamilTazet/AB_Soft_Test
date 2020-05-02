#include <iostream>
#include <algorithm>
#include <string>
#include <map>
#include <stack>
#include <sstream>
#include "tinyxml2.h"



class Employee {
private:
    std::string name;
    std::string middlename;
    std::string surname;
    std::string function;
    int salary;
public:
    Employee();
    Employee(std::string full_name);
    Employee(std::string snm, std::string midnm, std::string nm);
    Employee(tinyxml2::XMLElement * employment);
    Employee(const Employee &other_emp);

    std::string get_attribute_value(std::string attr_name);
    std::string get_full_name();
    bool set_attribute_value(std::string attr_name, std::string attr_value);
    tinyxml2::XMLElement * to_xml(tinyxml2::XMLDocument * doc);
    void print();
};


class Department {
private:
    std::string name;
    std::map<std::string, Employee> employees;
public:
    Department();
    Department(std::string name);
    Department(tinyxml2::XMLElement * department);
    std::string get_name();
    void add_employee(Employee new_employee);
    bool add_employee(std::string employee_name);
    bool delete_employee(std::string full_name, Employee * deleted_employee);
    bool delete_employee(std::string full_name);
    bool change_employee_attribute(std::string * emp_name, std::string attr_name, std::string attr_value, std::string * old_attr_value);
    Employee get_employee(std::string full_name);
    void set_name(std::string new_name);
    tinyxml2::XMLElement * to_xml(tinyxml2::XMLDocument * doc);
    void print();
};

class Company {
private:
    std::map<std::string, Department> departments;
public:
    Company(char * file_name);
    void add_department(Department new_department);
    bool add_department(std::string department_name);
    void add_employee(Employee deleted_employee, std::string department_name);
    bool add_employee(std::string department_name, std::string employee_name);
    bool delete_department(std::string name, Department * deleted_department);
    bool delete_department(std::string name);
    Department get_department(std::string name);
    bool delete_employee(std::string department_name, std::string employee_name, Employee * deleted_employee);
    bool delete_employee(std::string department_name, std::string employee_name);
    bool change_department_name(std::string department_name, std::string new_name);
    bool change_employee_attribute(std::string dep_name, std::string * emp_name, std::string attr_name, std::string attr_value, std::string * old_attr_value);
    void save_doc(char * file_name);
    void print();
};



class Command {
protected:
    Company * company;
public:
    Command();
    Command(Company * cmp);
    Command(char file_name[]);
    virtual bool execute() = 0;
    virtual void undo() = 0;
};

class History {
private:
    std::stack<Command *> history;
public:
    void save_command(Command * cmd);
    void undo_last_command();
};

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



class Invoker {
private:
    History history;
    Company company;
    // std::string file_name;
    char * file_name;
public:
    Invoker(char * file_name);
    int listen();
};
