#ifndef __COMPANY_
#define __COMPANY_
#include "department.h"




class Company {
private:
    std::map<std::string, Department> departments; //Хранит в себе департаменты компании, ключём служит название департамента
public:
    Company(char * file_name);
    void add_department(Department new_department); //Метод добавления созданного департамента
    bool add_department(std::string department_name); //Метод добавления нового департамента
    void add_employee(Employee deleted_employee, std::string department_name); //Метод добавления созданного сотрудника
    bool add_employee(std::string department_name, std::string employee_name); //Метод добавления нового сотрудника
    bool delete_department(std::string name, Department * deleted_department); //Метод удаления департамента. В объект, на который ссылаеться указатель deleted_department сохраняется удаляемый департамент
    bool delete_department(std::string name); //Метод удаления департаменты
    Department get_department(std::string name); //Метод получения департамента по имени
    bool delete_employee(std::string department_name, std::string employee_name, Employee * deleted_employee); //Метод удаления сотрудника. В объект, на который ссылаеться указатель deleted_demployee сохраняется удаляемый сотрудник
    bool delete_employee(std::string department_name, std::string employee_name); //Метод удаления сотрудника
    bool change_department_name(std::string department_name, std::string new_name); //Метод  изменения названия департамента
    bool change_employee_attribute(std::string dep_name, std::string * emp_name, std::string attr_name, std::string attr_value, std::string * old_attr_value); //Метод изменения значения атрибута сотрудника
    bool check_department(std::string department_name); //Метод проверки существования департамента
    bool check_employee(std::string department_name, std::string employee_name); //Метод проверки существования сотрудника
    bool check_employee_attribute(std::string department_name, std::string employee_name, std::string attribute_name); //Метод проверки существования атрибута
    void save_doc(char * file_name); //Метод сохранения данных в XML-файл
    void print(); //Метод вывода компании
};

#endif
