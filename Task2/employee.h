#ifndef _EMPLOYEE_
#define _EMPLOYEE_
#include<iostream>
#include<string>
#include <sstream>
#include <algorithm>
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

#endif
