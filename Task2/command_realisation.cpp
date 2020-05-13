#include "command_realisation.h"


DeleteDepartment::DeleteDepartment(Company * cmp): Command(cmp) {};


bool DeleteDepartment::set_data() {
    std::string dep_name;
    std::cout << "Введите название удаляемого департамента: " << std::endl;
    std::getline(std::cin, dep_name);
    if(this->company->check_department(dep_name)) {
        this->department_name = dep_name;
        return true;
    }
    else {
        return false;
    }
};

bool DeleteDepartment::execute() {
    Department * dlt_dp = new Department();
    if(this->company->delete_department(this->department_name, dlt_dp)) {
        deleted_department = *dlt_dp;
        delete dlt_dp;
        return true;
    }
    else {
        delete dlt_dp;
        return false;
    }
};


void DeleteDepartment::undo() {
    this->company->add_department(deleted_department);
};

DeleteDepartment::~DeleteDepartment() {

};


DeleteEmployee::DeleteEmployee(Company * cmp): Command(cmp) {};

bool DeleteEmployee::set_data() {
    std::string dep_name;
    std::string emp_name;
    std::cout << "Введите: " << std::endl;
    std::cout << "Название департамента удаляемого сотрудника: " << std::endl;
    std::getline(std::cin, dep_name);
    if(this->company->check_department(dep_name)) {
        this->department_name = dep_name;
        std::cout << "ФИО удаляемого сотрудника: " << std::endl;
        std::getline(std::cin, emp_name);
        if(this->company->check_employee(dep_name, emp_name)) {
            this->employee_name = emp_name;
            return true;
        }
        else {
            return false;
        }
    }
    else {
        return false;
    }
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

DeleteEmployee::~DeleteEmployee() {

};


AddDepartment::AddDepartment(Company * cmp): Command(cmp) {};


bool AddDepartment::set_data() {
    std::string dep_name;
    std::cout << "Введите название добавляемого департамента: " << std::endl;
    std::getline(std::cin, dep_name);
    this->department_name = dep_name;
    return true;
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

AddDepartment::~AddDepartment() {

};


AddEmployee::AddEmployee(Company * cmp): Command(cmp) {};

bool AddEmployee::set_data() {
    std::string dep_name;
    std::string emp_name;
    std::cout << "Введите: " << std::endl;
    std::cout << "Название департамента добавляемого сотрудника: " << std::endl;
    std::getline(std::cin, dep_name);
    if(this->company->check_department(dep_name)) {
        this->department_name = dep_name;
        std::cout << "ФИО добавляемого сотрудника: " << std::endl;
        std::getline(std::cin, emp_name);
        this->employee_name = emp_name;
        return true;
    }
    else {
        return false;
    }
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

AddEmployee::~AddEmployee() {

};


ChangeDepartmentName::ChangeDepartmentName(Company * cmp): Command(cmp) {};


bool ChangeDepartmentName::set_data() {
    std::string old_dep_name;
    std::string new_dep_name;
    std::cout << "Введите: " << std::endl;
    std::cout << "Название изменяемого департамента: " << std::endl;
    std::getline(std::cin, old_dep_name);
    if(this->company->check_department(old_dep_name)) {
        this->old_department_name = old_dep_name;
        std::cout << "Новое название департамента: " << std::endl;
        std::getline(std::cin, new_dep_name);
        this->new_department_name = new_dep_name;
        return true;
    }
    else {
        return false;
    }
};

bool ChangeDepartmentName::execute() {
    return this->company->change_department_name(old_department_name, new_department_name);
};

void ChangeDepartmentName::undo() {
    this->company->change_department_name(new_department_name, old_department_name);
};

ChangeDepartmentName::~ChangeDepartmentName() {

};


ChangeEmployeeAttribute::ChangeEmployeeAttribute(Company * cmp): Command(cmp) {};

bool ChangeEmployeeAttribute::set_data() {
    std::string dep_name;
    std::string emp_name;
    std::string attr_name;
    std::string attr_value;
    std::cout << "Введите: " << std::endl;
    std::cout << "Название департамента изменяемого сотрудника: " << std::endl;
    std::getline(std::cin, dep_name);
    if(this->company->check_department(dep_name)) {
        this->department_name = dep_name;
        std::cout << "ФИО изменяемого сотрудника: " << std::endl;
        std::getline(std::cin, emp_name);
        if(this->company->check_employee(dep_name, emp_name)) {
            this->employee_name = emp_name;
            std::cout << "Название изменяемого аттрибута: " << std::endl;
            std::getline(std::cin, attr_name);
            if(this->company->check_employee_attribute(dep_name, emp_name, attr_name)) {
                this->attribute_name = attr_name;
                std::cout << "Новое значение аттрибута: " << std::endl;
                std::getline(std::cin, attr_value);
                this->new_attribute_value = attr_value;
                return true;
            }
            else {
                return false;
            }
        }
        else {
            return false;
        }
    }
    else {
        return false;
    }
};

bool ChangeEmployeeAttribute::execute() {
    return this->company->change_employee_attribute(department_name, &employee_name, attribute_name, new_attribute_value, &old_attribute_value);
};

void ChangeEmployeeAttribute::undo() {
    this->company->change_employee_attribute(department_name, &employee_name, attribute_name, old_attribute_value, &new_attribute_value);
};

ChangeEmployeeAttribute::~ChangeEmployeeAttribute() {

};


Save::Save(Company * cmp): Command(cmp) {};


bool Save::set_data() {
    std::string save_name;
    std::cout << "Введите имя для сохраняемого файла" << std::endl;
    std::cout << "Расширение .xml будет добавлено автоматически" << std::endl;
    std::getline(std::cin, save_name);
    if(save_name.size() != 0) {
        save_name = save_name + ".xml";
        this->file_name = save_name;
        return true;
    }
    else {
        std::cout << "Введена пустая строка, сохранения не произведено" << std::endl;
        return false;
    }
};

bool Save::execute() {
    char save_file_name[file_name.size()];
    strcpy(save_file_name, this->file_name.c_str());
    company->save_doc(save_file_name);
    return false;
};
void Save::undo() {

};

Save::~Save() {

};


Print::Print(Company * cmp): Command(cmp) {

};

bool Print::set_data() {

};

bool Print::execute() {
    this->company->print();
    return false;
};

void Print::undo() {

};

Print::~Print() {

};


bool Help::set_data() {

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
    std::cout << "redo - возврат последней отменённой команды" << std::endl;
    std::cout << "save - сохранить изменения" << std::endl;
    std::cout << "help - вывод списка команд" << std::endl;
    return false;
};

void Help::undo() {

};

Help::~Help() {

};


Undo::Undo(History * command_history) {
    this->history = command_history;
};

bool Undo::set_data() {

};

bool Undo::execute() {
    this->history->undo_last_command();
    return false;
};

void Undo::undo() {

};

Undo::~Undo() {

};


Redo::Redo(History * command_history) {
    this->history = command_history;
};

bool Redo::set_data() {

};

bool Redo::execute() {
    this->history->redo_last_command();
    return false;
};

void Redo::undo() {

};

Redo::~Redo() {

};
