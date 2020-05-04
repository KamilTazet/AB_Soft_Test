#ifndef _DEPARTMENT_
#define _DEPARTMENT_
#include <map>
#include "employee.h"


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

#endif
