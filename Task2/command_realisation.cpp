#include "command_realisation.h"


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
