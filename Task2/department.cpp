#include "department.h"



Department::Department() {

};
Department::Department(std::string name) {
    this->name = name;
};
Department::Department(tinyxml2::XMLElement * department) {
    this->name = department->FirstAttribute()->Value();
    std::map<std::string, std::map<std::string, std::string>> depart_map;
    tinyxml2::XMLElement * employments = department->FirstChildElement("employments");
    tinyxml2::XMLElement * employment = employments->FirstChildElement("employment");
    while(employment) {
        Employee new_employee(employment);
        std::pair<std::string, Employee> new_employment = std::pair<std::string, Employee>(new_employee.get_full_name(), new_employee);
        this->employees.insert(new_employment);
        employment = employment->NextSiblingElement("employment");
    }
};
std::string Department::get_name() {
    return this->name;
}
void Department::add_employee(Employee new_employee) {
    std::pair<std::string, Employee> employment = std::pair<std::string, Employee>(new_employee.get_full_name(), new_employee);
    this->employees.insert(this->employees.end(), employment);
};
bool Department::add_employee(std::string employee_name) {
    if(this->employees.count(employee_name) == 0) {
        Employee new_employee(employee_name);
        std::pair<std::string, Employee> employment = std::pair<std::string, Employee>(new_employee.get_full_name(), new_employee);
        this->employees.insert(this->employees.end(), employment);
        return true;
    }
    else {
        std::cout << "Сотрудник с именем " << employee_name << " уже существует" << std::endl;
    }
};

bool Department::delete_employee(std::string full_name, Employee * deleted_employee) {
    if(this->employees.count(full_name) != 0) {
        *deleted_employee = this->employees[full_name];
        this->employees.erase(full_name);
        return true;
    }
    else {
        std::cout << "Нет работника с именем " << full_name << std::endl;
        deleted_employee = NULL;
        return false;
    }
};

bool Department::delete_employee(std::string full_name) {
    if(this->employees.count(full_name) != 0) {
        this->employees.erase(full_name);
        return true;
    }
    else {
        std::cout << "Нет работника с именем " << full_name << std::endl;
        return false;
    }
};

bool Department::change_employee_attribute(std::string * emp_name, std::string attr_name, std::string attr_value, std::string * old_attr_value) {
    if(this->employees.count(*emp_name) != 0) {
        bool result;
        *old_attr_value = this->employees[*emp_name].get_attribute_value(attr_name);
        result = this->employees[*emp_name].set_attribute_value(attr_name, attr_value);
        if((attr_name == "surname" || attr_name == "name" || attr_name == "middlename") && result == true && *old_attr_value != "Error") {
            std::string new_name =  this->employees[*emp_name].get_full_name();
            auto employee_element = this->employees.extract(*emp_name);
            employee_element.key() = new_name;
            this->employees.insert(move(employee_element));
            *emp_name = new_name;
        }
        else if(result == false || *old_attr_value == "Error") {
            return false;
        }
        return true;
    }
    else {
        std::cout << "Нет работника с именем " << *emp_name << std::endl;
        return false;
    }
};

Employee Department::get_employee(std::string full_name) {
    return this->employees[full_name];
};


void Department::set_name(std::string new_name) {
    this->name = new_name;
};

tinyxml2::XMLElement * Department::to_xml(tinyxml2::XMLDocument * doc) {
    tinyxml2::XMLElement * department = doc->NewElement("department");
    department->SetAttribute("name", this->name.c_str());
    tinyxml2::XMLElement * employments = doc->NewElement("employments");
    std::map<std::string, Employee>::iterator it;
    for(it = this->employees.begin(); it != this->employees.end(); it++) {
        tinyxml2::XMLElement * employment = it->second.to_xml(doc);
        employments->InsertEndChild(employment);
    }
    department->InsertEndChild(employments);
    return department;
};

void Department::print() {
    std::cout << "    " << this->name <<std::endl;
    for(std::map<std::string, Employee>::iterator i = this->employees.begin(); i != this->employees.end(); i++) {
        i->second.print();
    }
};
