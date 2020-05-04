#ifndef __COMPANY_
#define __COMPANY_
#include "department.h"




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

#endif
