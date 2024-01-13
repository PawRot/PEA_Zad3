//
// Created by Michał Zychowicz on 13/01/2024.
//

#ifndef PARENT_H
#define PARENT_H



class parent {
public:
    int a = 2;
    int b = 3;

    void operation();

    virtual void virtualOperation(int a, int b) = 0;

};



#endif //PARENT_H
