#ifndef FEUP_DA_PROJ2_MENU_H
#define FEUP_DA_PROJ2_MENU_H

#include <iostream>
#include <string>
#include "Printer.h"

class Menu {
public:
    Menu();
    void run();
private:
    Printer readSelectedFile();
    bool isShippingGraph = false;
    Printer printer;
};
#endif //FEUP_DA_PROJ2_MENU_H
