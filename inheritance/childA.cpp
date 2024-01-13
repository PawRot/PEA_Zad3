//
// Created by Michał Zychowicz on 13/01/2024.
//

#include "childA.h"

void childA::virtualOperation(int a, int b) {
    int temp = a*b;
    std::cout << "childA: " << temp << std::endl;
}