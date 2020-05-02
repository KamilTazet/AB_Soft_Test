#include "company.h"

int main(int argc, char ** argv) {
    tinyxml2::XMLDocument file;
    Invoker inv(argv[1]);
    inv.listen();
}
