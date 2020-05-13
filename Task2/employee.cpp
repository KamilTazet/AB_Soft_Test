#include "employee.h"


Employee::Employee() {
    this->salary = 0;
};
Employee::Employee(std::string full_name) {
    std::string strings[3];
    std::istringstream f(full_name);
    std::string s;
    int i = 0;
    while (getline(f, s, ' ') && i < 3) {
        strings[i] = s;
        i++;
    }
    this->surname = strings[0];
    this->name = strings[1];
    this->middlename = strings[2];
    this->salary = 0;
};
Employee::Employee(tinyxml2::XMLElement * employment) {
    this->surname = employment->FirstChildElement("surname")->GetText();
    this->name = employment->FirstChildElement("name")->GetText();
    this->middlename = employment->FirstChildElement("middleName")->GetText();
    this->function = employment->FirstChildElement("function")->GetText();
    this->salary = atoi(employment->FirstChildElement("salary")->GetText());
};
Employee::Employee(const Employee &other_emp) {
    this->name = other_emp.name;
    this->middlename = other_emp.middlename;
    this->surname = other_emp.surname;
    this->function = other_emp.function;
    this->salary = other_emp.salary;
};

std::string Employee::get_attribute_value(std::string attr_name) {
    if(attr_name == "surname") {
      return this->surname;
    }
    else if(attr_name == "name") {
      return this->name;
    }
    else if(attr_name == "middlename") {
      return this->middlename;
    }
    else if(attr_name == "function") {
      return this->function;
    }
    else if(attr_name == "salary") {
      return std::to_string(this->salary);
    }
    else {
      std::cout << "Нет атрибута с именем " << attr_name << std::endl;
      return "Error";
    }
};
std::string Employee::get_full_name() {
    std::string full_name = this->surname + " " + this->name + " " + this->middlename;
    return full_name;
}
bool Employee::set_attribute_value(std::string attr_name, std::string attr_value) {
    if(attr_name == "surname") {
        this->surname = attr_value;
        return true;
    }
    else if(attr_name == "name") {
        this->name = attr_value;
        return true;
    }
    else if(attr_name == "middlename") {
        this->middlename = attr_value;
        return true;
    }
    else if(attr_name == "function") {
        this->function = attr_value;
        return true;
    }
    else if(attr_name == "salary") {
        if(std::all_of(attr_value.begin(), attr_value.end(), ::isdigit)) {
            this->salary = std::stoi(attr_value);
            return true;
        }
        else {
            std::cout << "Неправильный формат значения аттрибута salary" << std::endl;
            return false;
        }
    }
    else {
      // std::cout << "Нет атрибута с именем " << attr_name << std::endl;
      return false;
    }
};

bool Employee::check_attribute_name(std::string attribute_name) {
    if(attribute_name == "surname") {
        return true;
    }
    else if(attribute_name == "name") {
        return true;
    }
    else if(attribute_name == "middlename") {
        return true;
    }
    else if(attribute_name == "function") {
        return true;
    }
    else if(attribute_name == "salary") {
        return true;
    }
    else {
      std::cout << "Нет атрибута с именем " << attribute_name << std::endl;
      return false;
    }
};

tinyxml2::XMLElement * Employee::to_xml(tinyxml2::XMLDocument * doc) {
    tinyxml2::XMLElement * employment = doc->NewElement("employment");
    tinyxml2::XMLElement * surname = doc->NewElement("surname");
    surname->SetText(this->surname.c_str());
    employment->InsertEndChild(surname);
    tinyxml2::XMLElement * name = doc->NewElement("name");
    name->SetText(this->name.c_str());
    employment->InsertEndChild(name);
    tinyxml2::XMLElement * middleName = doc->NewElement("middleName");
    middleName->SetText(this->middlename.c_str());
    employment->InsertEndChild(middleName);
    tinyxml2::XMLElement * function = doc->NewElement("function");
    function->SetText(this->function.c_str());
    employment->InsertEndChild(function);
    tinyxml2::XMLElement * salary = doc->NewElement("salary");
    salary->SetText(this->salary);
    employment->InsertEndChild(salary);
    return employment;
};

void Employee::print() {
    std::cout << "        " << this->surname << " " << this->name  << " " << this->middlename << std::endl;
    std::cout << "            " << "surname: " << this->surname << std::endl;
    std::cout << "            " << "name: " << this->name << std::endl;
    std::cout << "            " << "middlename: " << this->middlename << std::endl;
    std::cout << "            " << "function: " << this->function << std::endl;
    std::cout << "            " << "salary: " << this->salary << std::endl;
};
