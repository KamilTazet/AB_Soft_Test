#ifndef _DEPARTMENT_
#define _DEPARTMENT_
#include <map>
#include "employee.h"


class Department {
private:
    std::string name; //Название департамента
    std::map<std::string, Employee> employees; //Хранит в себе сотрудников данного департамента. Ключём являеться ФИО сотрудника
public:
    Department();
    Department(std::string name);
    Department(tinyxml2::XMLElement * department);
    std::string get_name(); //метод получения названия департамента
    void add_employee(Employee new_employee); //Метод добавления созданного сотрудника в департамент
    bool add_employee(std::string employee_name); //Метод создания сотрудника с
    bool delete_employee(std::string full_name, Employee * deleted_employee); //Метод удаления сотрудника. В *deleted_employee сохраняеться удаляемый сотрудник
    bool delete_employee(std::string full_name); //Метод удаления сотрудника
    bool change_employee_attribute(std::string * emp_name, std::string attr_name, std::string attr_value, std::string * old_attr_value); //Метод изменения атрибута сотрудника
    bool check_employee(std::string employee_name); //Метод проверки существования сотрудника
    bool check_employee_attribute(std::string employee_name, std::string attribute_name); //Метод проверки существования атрибута сотрудника
    Employee get_employee(std::string full_name); //Метод получения сотрудника
    void set_name(std::string new_name); //Метод изменения имени департамента
    tinyxml2::XMLElement * to_xml(tinyxml2::XMLDocument * doc); //Метод получения XML-объекта департамента
    void print(); //Метод вывода департамента и находящихся в нём сотрудников
};

#endif
