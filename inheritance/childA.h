//
// Created by Michał Zychowicz on 13/01/2024.
//

#ifndef CHILDA_H
#define CHILDA_H
#include "parent.h"
#include <iostream>


class childA : public parent{
    public:
    void virtualOperation(int a, int b) override;

};



#endif //CHILDA_H
