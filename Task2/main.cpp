#include "company.h"

int main(int argc, char ** argv) {
    tinyxml2::XMLDocument file;
    // char file_name[] = "/home/kamil/AB_Soft/Task2/test.xml";
    // Company * cmpy = new Company(file_name);
    // Company * cmpy = new Company(argv[1]);
    // Invoker inv(file_name);
    Invoker inv(argv[1]);
    inv.listen();
}
