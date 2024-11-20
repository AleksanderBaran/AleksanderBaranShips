#ifndef SHIP_H
#define SHIP_H
#include <iostream>
class Ship 
{
public:
    int length;
    int hits;
    Ship();
    void setShip(int len);
    bool isSunk();
    void hit();
};

#endif
