#include "company.h"
#include "command_realisation.h"



class Invoker {
private:
    History history; //Объект истории изменений
    Company company; //Объект компании
    char * file_name; //Название выбранного для считывания XML-файла
public:
    Invoker(char * file_name);
    int listen(); //Метод считывания введёных команд и создания соответсвующих объектов команд 
};
