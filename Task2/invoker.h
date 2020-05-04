#include "company.h"
#include "command_realisation.h"



class Invoker {
private:
    History history;
    Company company;
    // std::string file_name;
    char * file_name;
public:
    Invoker(char * file_name);
    int listen();
};
