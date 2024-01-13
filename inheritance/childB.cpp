//
// Created by Michał Zychowicz on 13/01/2024.
//

#include "childB.h"
#include <iostream>

void childB::virtualOperation(int a, int b) {
    int temp = a-b;
    std::cout << "childB: " << temp << std::endl;
}