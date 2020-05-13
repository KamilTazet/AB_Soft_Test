#include <cstring>
#include "history.h"

class DeleteDepartment: public Command { //Класс команды удаления департамента
private:
    std::string department_name; //Название удаляемого департамента
    Department deleted_department; //Удалённый департамент. Нужен для восстановаления дпертамента в случае отмены удаления
public:
    DeleteDepartment(Company * cmp);
    bool set_data();
    bool execute();
    void undo();
    ~DeleteDepartment();
};

class DeleteEmployee: public Command { //Класс команды удаления сотрудника
private:
    std::string department_name; //Название департамента
    std::string employee_name; //ФИО удаляемого сотрудника
    Employee deleted_employee; //Удалённый сотрудник. Нужен для восстановления сотрудника в случае отмены команды
public:
    DeleteEmployee(Company * cmp);
    bool set_data();
    bool execute();
    void undo();
    ~DeleteEmployee();
};

class AddDepartment: public Command { //Класс команды добавления департамента
private:
    std::string department_name; //Нзвания добавляемого департамента
public:
    AddDepartment(Company * cmp);
    bool set_data();
    bool execute();
    void undo();
    ~AddDepartment();
};

class AddEmployee: public Command{ //Класс команды добавления сотрудника
private:
    std::string department_name; //Название департмента
    std::string employee_name; //ФИО добавляемого сотрудника
public:
    AddEmployee(Company * cmp);
    bool set_data();
    bool execute();
    void undo();
    ~AddEmployee();
};

class ChangeDepartmentName: public Command { //Класс команды изменения имени департамента
private:
    std::string old_department_name; //Изначальное название изменяемого и департамента
    std::string new_department_name; //Новое название департамента
public:
    ChangeDepartmentName(Company * cmp);
    bool set_data();
    bool execute();
    void undo();
    ~ChangeDepartmentName();
};

class ChangeEmployeeAttribute: public Command { //Класс команды изменения значения аттрибута сотрудника
private:
    std::string department_name; //Название департамента
    std::string employee_name; //ФИО сотрудника
    std::string attribute_name; //Название атрибута
    std::string new_attribute_value; //Новое значение атрибута
    std::string old_attribute_value; //Старое значение атрибута. Нужно для отмены команды
public:
    ChangeEmployeeAttribute(Company * cmp);
    bool set_data();
    bool execute();
    void undo();
    ~ChangeEmployeeAttribute();
};


class Save: public Command { //Класс команды сохранения
    std::string file_name; //Название файла сохранения
public:
    Save(Company * cmp);
    bool set_data();
    bool execute();
    void undo();
    ~Save();
};


class Print: public Command { //Класс команды вывода состава компании
public:
    Print(char file_name[]);
    Print(Company * cmp);
    bool set_data();
    bool execute();
    void undo();
    ~Print();
};

class Help: public Command { //Класс команды вывода списка команд с кратким пояснением
public:
    bool set_data();
    bool execute();
    void undo();
    ~Help();
};

class Undo: public Command { //Класс команды отмены действия
private:
    History * history; //Указатель на объект истории изменений
public:
    Undo(History * command_history);
    bool set_data();
    bool execute();
    void undo();
    ~Undo();
};

class Redo: public Command { //Класс команды возврата отменённого действия
private:
    History * history; //Указатель на объект истории изменений
public:
    Redo(History * command_history);
    bool set_data();
    bool execute();
    void undo();
    ~Redo();
};
