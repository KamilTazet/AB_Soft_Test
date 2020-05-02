
#include "company.h"




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
    std::cout << "            " << "Surname: " << this->surname << std::endl;
    std::cout << "            " << "Name: " << this->name << std::endl;
    std::cout << "            " << "Middlename: " << this->middlename << std::endl;
    std::cout << "            " << "Function: " << this->function << std::endl;
    std::cout << "            " << "Salary: " << this->salary << std::endl;
};

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
        else if(result == false || *old_attr_value != "Error") {
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
        std::cout << "Сохранение прошло успешно" << std::endl;
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





Command::Command() {

};
Command::Command(Company * cmp) {
    this->company = cmp;
}


void History::save_command(Command * cmd) {
    this->history.push(cmd);
};

void History::undo_last_command() {
    if(!history.empty()) {
        this->history.top()->undo();
        Command * cmd = this->history.top();
        this->history.pop();
        delete cmd;
    }
    else {
        std::cout << "Нет операций для отмены" << std::endl;
    }
};



DeleteDepartment::DeleteDepartment(Company * cmp, std::string name): Command(cmp) {
    this->department_name = name;
};

bool DeleteDepartment::execute() {
    Department * dlt_dp = new Department();
    if(this->company->delete_department(this->department_name, dlt_dp)) {
        deleted_department = *dlt_dp;
        return true;
    }
    else {
        return false;
    }
};

void DeleteDepartment::undo() {
    this->company->add_department(deleted_department);
};


DeleteEmployee::DeleteEmployee(Company * cmp, std::string dp_name, std::string emp_name): Command(cmp) {
    this->department_name = dp_name;
    this->employee_name = emp_name;
};

bool DeleteEmployee::execute() {
    Employee * dlt_emp = new Employee();
    if(this->company->delete_employee(department_name, employee_name, dlt_emp)) {
        deleted_employee = *dlt_emp;
        delete dlt_emp;
        return true;
    }
    else {
        delete dlt_emp;
        return false;
    }
};

void DeleteEmployee::undo() {
    this->company->add_employee(deleted_employee, department_name);
};


AddDepartment::AddDepartment(Company * cmp, std::string dp_name): Command(cmp) {
    this->department_name = dp_name;
};
bool AddDepartment::execute() {
    if(this->company->add_department(department_name)){
        return true;
    }
    else {
        return false;
    }
};
void AddDepartment::undo() {
    this->company->delete_department(department_name);
};


AddEmployee::AddEmployee(Company * cmp, std::string dp_name, std::string emp_name): Command(cmp) {
    this->department_name = dp_name;
    this->employee_name = emp_name;
};

bool AddEmployee::execute() {
    if(this->company->add_employee(department_name, employee_name)) {
        return true;
    }
    else {
        return false;
    }
};

void AddEmployee::undo() {
    this->company->delete_employee(department_name, employee_name);
};


ChangeDepartmentName::ChangeDepartmentName(Company * cmp, std::string old_name, std::string new_name): Command(cmp) {
    this->old_department_name = old_name;
    this->new_department_name = new_name;
};

bool ChangeDepartmentName::execute() {
    return this->company->change_department_name(old_department_name, new_department_name);
};

void ChangeDepartmentName::undo() {
    this->company->change_department_name(new_department_name, old_department_name);
};


ChangeEmployeeAttribute::ChangeEmployeeAttribute(Company * cmp, std::string dep_name, std::string emp_name, std::string attr_name, std::string attr_value): Command(cmp) {
    this->department_name = dep_name;
    this->employee_name = emp_name;
    this->attribute_name = attr_name;
    this->new_attribute_value = attr_value;
};

bool ChangeEmployeeAttribute::execute() {
    return this->company->change_employee_attribute(department_name, &employee_name, attribute_name, new_attribute_value, &old_attribute_value);
};

void ChangeEmployeeAttribute::undo() {
    this->company->change_employee_attribute(department_name, &employee_name, attribute_name, old_attribute_value, &new_attribute_value);
};


Save::Save(Company * cmp, char * file): Command(cmp) {
    this->file_name = file;
};
bool Save::execute() {
    company->save_doc(file_name);
    return false;
};
void Save::undo() {

};


Print::Print(Company * cmp): Command(cmp) {

};

bool Print::execute() {
    this->company->print();
    return false;
};

void Print::undo() {

};


bool Help::execute() {
    std::cout << "Список команд:" << std::endl;
    std::cout << "delete_department - удалить департамент" << std::endl;
    std::cout << "delete_employee - удалить сотрудника" << std::endl;
    std::cout << "add_department - добавить департамент" << std::endl;
    std::cout << "add_employee - добавить сотрудника" << std::endl;
    std::cout << "change_department_name - изменить название департамента" << std::endl;
    std::cout << "change_employee_attribute - изменить значение аттрибутов сотрудника (фамилию, имя, отчество, должность и зарплату)" << std::endl;
    std::cout << "print - вывести отделы, сотрудников и их аттрибуты в терминал" << std::endl;
    std::cout << "undo - отмена последней команды" << std::endl;
    std::cout << "save - сохранить изменения" << std::endl;
    std::cout << "help - вывод списка команд" << std::endl;
    return false;
};

void Help::undo() {

};


Undo::Undo(History * command_history) {
    this->history = command_history;
};

bool Undo::execute() {
    this->history->undo_last_command();
    return false;
};

void Undo::undo() {

};



Invoker::Invoker(char * file_name): company(file_name) {
    this->file_name = file_name;
};
int Invoker::listen() {
    std::string command_line;
    for(;;) {
        Command * command;
        std::cout << "Введите команду (для завершения введите quit): " << std::endl;
        std::getline(std::cin, command_line);
        if(command_line == "delete_department") {
            std::string department_name;
            std::cout << "Введите название удаляемого департамента: " << std::endl;
            std::getline(std::cin, department_name);
            DeleteDepartment * del_dep = new DeleteDepartment(&(this->company), department_name);
            command = del_dep;
        }
        else if(command_line == "delete_employee") {
            std::string department_name;
            std::string employee_name;
            std::cout << "Введите: " << std::endl;
            std::cout << "Название департамента удаляемого сотрудника: " << std::endl;
            std::getline(std::cin, department_name);
            std::cout << "ФИО удаляемого сотрудника: " << std::endl;
            std::getline(std::cin, employee_name);
            DeleteEmployee * del_emp = new DeleteEmployee(&(this->company), department_name, employee_name);
            command = del_emp;
        }
        else if(command_line == "add_department") {
            std::string department_name;
            std::cout << "Введите название добавляемого департамента: " << std::endl;
            std::getline(std::cin, department_name);
            AddDepartment * add_dep = new AddDepartment(&(this->company), department_name);
            command = add_dep;
        }
        else if(command_line == "add_employee") {
            std::string department_name;
            std::string employee_name;
            std::cout << "Введите: " << std::endl;
            std::cout << "Название департамента добавляемого сотрудника: " << std::endl;
            std::getline(std::cin, department_name);
            std::cout << "ФИО добавляемого сотрудника: " << std::endl;
            std::getline(std::cin, employee_name);
            AddEmployee * add_emp = new AddEmployee(&(this->company), department_name, employee_name);
            command = add_emp;
        }
        else if(command_line == "change_department_name") {
            std::string old_department_name;
            std::string new_department_name;
            std::cout << "Введите: " << std::endl;
            std::cout << "Название изменяемого департамента: " << std::endl;
            std::getline(std::cin, old_department_name);
            std::cout << "Новое название департамента: " << std::endl;
            std::getline(std::cin, new_department_name);
            ChangeDepartmentName * chng_dep = new ChangeDepartmentName(&(this->company), old_department_name, new_department_name);
            command = chng_dep;
        }
        else if(command_line == "change_employee_attribute") {
            std::string department_name;
            std::string employee_name;
            std::string attribute_name;
            std::string attribute_value;
            std::cout << "Введите: " << std::endl;
            std::cout << "Название департамента изменяемого сотрудника: " << std::endl;
            std::getline(std::cin, department_name);
            std::cout << "ФИО изменяемого сотрудника: " << std::endl;
            std::getline(std::cin, employee_name);
            std::cout << "Название изменяемого аттрибута: " << std::endl;
            std::getline(std::cin, attribute_name);
            std::cout << "Новое значение аттрибута: " << std::endl;
            std::getline(std::cin, attribute_value);
            ChangeEmployeeAttribute * chng_emp = new ChangeEmployeeAttribute(&(this->company), department_name, employee_name, attribute_name, attribute_value);
            command = chng_emp;
        }
        else if(command_line == "save") {
            Save * save_com = new Save(&(this->company), this->file_name);
            command = save_com;
        }
        else if(command_line == "print") {
            Print * prnt_com = new Print(&(this->company));
            command = prnt_com;
        }
        else if(command_line == "undo") {
            Undo * undo_com = new Undo(&(this->history));
            command = undo_com;
        }
        else if(command_line == "help") {
            Help * help_com = new Help();
            command = help_com;
        }
        else if(command_line == "quit"){
            return 0;
        }
        else {
            std::cout << "Неизвестная команда" << std::endl;
        }
        if(command->execute()) {
            history.save_command(command);
        }
    }
};
