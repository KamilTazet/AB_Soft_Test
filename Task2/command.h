#include "company.h"

class Command {
protected:
    Company * company; //Указатель на объект компании, содержащий департаменты
public:
    Command();
    Command(Company * cmp);
    Command(char file_name[]);
    virtual bool set_data() = 0; //Метод заполнения данных
    virtual bool execute() = 0; //Метод выполнения команды
    virtual void undo() = 0; //Метод отмены команды
    virtual ~Command() = 0;
};
