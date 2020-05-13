#ifndef _EMPLOYEE_
#define _EMPLOYEE_
#include<iostream>
#include<string>
#include <sstream>
#include <algorithm>
#include "tinyxml2.h"

class Employee {
private:
    std::string name; //Имя сотрудника
    std::string middlename; //Отчество сотрудника
    std::string surname; //Фамилия сотрудника
    std::string function; //Должность сотрудника
    int salary; // З/п сотрудника
public:
    Employee();
    Employee(std::string full_name);
    Employee(std::string snm, std::string midnm, std::string nm);
    Employee(tinyxml2::XMLElement * employment);
    Employee(const Employee &other_emp);

    std::string get_attribute_value(std::string attr_name); //Метод получения значения атрибута
    std::string get_full_name(); //Метод получения ФИО сотрудника
    bool set_attribute_value(std::string attr_name, std::string attr_value); //Метод изменения значений атрибутов сотрудника
    bool check_attribute_name(std::string attribute_name); //метод проверки наличия атрибута с данным названием
    tinyxml2::XMLElement * to_xml(tinyxml2::XMLDocument * doc); //Метод получения XML-объекта сотрудника
    void print(); //Метод вывода атрибутов сотрудника
};

#endif
