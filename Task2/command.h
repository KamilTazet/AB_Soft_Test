#include "company.h"

class Command {
protected:
    Company * company;
public:
    Command();
    Command(Company * cmp);
    Command(char file_name[]);
    virtual bool execute() = 0;
    virtual void undo() = 0;
};
