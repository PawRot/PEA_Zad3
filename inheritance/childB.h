//
// Created by Michał Zychowicz on 13/01/2024.
//

#ifndef CHILDB_H
#define CHILDB_H
#include "parent.h"


class childB : public parent {
public:
    void virtualOperation(int a, int b) override;
};



#endif //CHILDB_H
