#include "displaysystem.h"

#include <iostream>

displaySystem::displaySystem()
{
    time = std::clock();
    systemSignature = bitmap("0000000000000001");
}

void displaySystem::execute()
{
    std::clock_t t1 = clock();
    if ((t1 - time) / (double) CLOCKS_PER_SEC > 2.0) {
        time = t1;
        std::cout << "Test" << std::endl;
    }

}
