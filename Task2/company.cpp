
#include "company.h"






Company::Company(char * file_name) {
    tinyxml2::XMLDocument xml_file;
    if (xml_file.LoadFile(file_name) == tinyxml2::XML_SUCCESS) {
        tinyxml2::XMLElement * company = xml_file.RootElement();
        if(company != NULL) {
            tinyxml2::XMLElement *department = company->FirstChildElement("department");
            while(department) {
                Department new_department(department);
                std::pair<std::string, Department>  department_map_element = std::pair<std::string, Department>(new_department.get_name(), new_department);
                departments.insert(department_map_element);
                department = department->NextSiblingElement("department");
            }
        }
    }
    else {
        std::cout << "Ошибка при открытии файла. Завершение программы" << std::endl;
        exit(-1);
    }
};

void Company::add_department(Department new_department) {
    std::pair<std::string, Department> department = std::pair<std::string, Department>(new_department.get_name(), new_department);
    this->departments.insert(this->departments.end(), department);
}
bool Company::add_department(std::string department_name) {
    if(this->departments.count(department_name) == 0) {
        Department new_department(department_name);
        std::pair<std::string, Department> department = std::pair<std::string, Department>(new_department.get_name(), new_department);
        this->departments.insert(this->departments.end(), department);
        return true;
    }
    else {
        std::cout << "Департамент с именем " << department_name << " уже существует" << std::endl;
        return false;
    }
};
void Company::add_employee(Employee deleted_employee, std::string department_name) {
    this->departments[department_name].add_employee(deleted_employee);
};
bool Company::add_employee(std::string department_name, std::string employee_name) {
    if(this->departments.count(department_name) != 0) {
        return this->departments[department_name].add_employee(employee_name);
    }
    else {
        std::cout << "Нет департамента с названием " << department_name << std::endl;
        return false;
    }
};
bool Company::delete_department(std::string name, Department * deleted_department) {
    if(this->departments.count(name) != 0) {
        *deleted_department = this->departments[name];
        this->departments.erase(name);
        return true;
    }
    else {
        std::cout << "Нет департамента с названием " << name << std::endl;
        deleted_department = 0;
        return false;
    }
}
bool Company::delete_department(std::string name) {
    if(this->departments.count(name) != 0) {
        this->departments.erase(name);
        return true;
    }
    else {
        std::cout << "Нет департамента с названием " << name << std::endl;
        return false;
    }
};

Department Company::get_department(std::string name) {
    return this->departments[name];
};

bool Company::delete_employee(std::string department_name, std::string employee_name, Employee * deleted_employee) {
    if(this->departments.count(department_name) != 0) {
        return this->departments[department_name].delete_employee(employee_name, deleted_employee);
    }
    else {
        std::cout << "Нет департамента с названием " << department_name << std::endl;
        return false;
    }
};

bool Company::delete_employee(std::string department_name, std::string employee_name) {
    if(this->departments.count(department_name) != 0) {
        return this->departments[department_name].delete_employee(employee_name);
    }
    else {
        std::cout << "Нет департамента с названием " << department_name << std::endl;
        return false;
    }
};
bool Company::change_department_name(std::string department_name, std::string new_name) {
    if(this->departments.count(department_name) != 0) {
        this->departments[department_name].set_name(new_name);
        auto departments_element = this->departments.extract(department_name);
        departments_element.key() = new_name;
        this->departments.insert(move(departments_element));
        return true;
    }
    else {
        std::cout << "Нет департамента с названием " << department_name << std::endl;
        return false;
    }
};

bool Company::change_employee_attribute(std::string dep_name, std::string * emp_name, std::string attr_name, std::string attr_value, std::string * old_attr_value) {
    if(this->departments.count(dep_name) != 0) {
        return this->departments[dep_name].change_employee_attribute(emp_name, attr_name, attr_value,  old_attr_value);
    }
    else {
        std::cout << "Нет департамента с названием " << dep_name << std::endl;
        return false;
    }
};

bool Company::check_department(std::string department_name) {
    if(this->departments.count(department_name) != 0) {
        return true;
    }
    else {
        std::cout << "Нет департамента с названием " << department_name << std::endl;
        return false;
    }
};

bool Company::check_employee(std::string department_name, std::string employee_name) {
    if(this->check_department(department_name)) {
        return this->departments[department_name].check_employee(employee_name);
    }
    else {
        return false;
    }
};

bool Company::check_employee_attribute(std::string department_name, std::string employee_name, std::string attribute_name) {
    if(this->check_department(department_name)) {
        return this->departments[department_name].check_employee_attribute(employee_name, attribute_name);
    }
    else {
        return false;
    }
};

void Company::save_doc(char * file_name) {
    tinyxml2::XMLDocument doc;
    tinyxml2::XMLDeclaration * declaration =  doc.NewDeclaration();
    doc.InsertFirstChild(declaration);
    tinyxml2::XMLElement * departments = doc.NewElement("departments");
    std::map<std::string, Department>::iterator it;
    for(it = this->departments.begin(); it != this->departments.end(); it++) {
        tinyxml2::XMLElement * department = it->second.to_xml(&doc);
        departments->InsertEndChild(department);
    }
    doc.InsertEndChild(departments);
    if (doc.SaveFile(file_name) == tinyxml2::XML_SUCCESS) {
        std::cout << "Сохранение прошло успешно. Имя файла - " << file_name << std::endl;
    }
    else {
        std::cout << "Произошла ошибка при сохранении" << std::endl;
    }
};

void Company::print() {
    for(std::map<std::string, Department>::iterator i = this->departments.begin(); i != this->departments.end(); i++) {
        i->second.print();
    }
};
