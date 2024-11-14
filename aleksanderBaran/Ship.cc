#include "Ship.h"
#include <iostream>
using namespace std;
Ship::Ship() : length(0), hits(0) {} //The same thing as the previous

void Ship::setShip(int len) 
{
    length = len;
    hits = 0;
}
bool Ship::isSunk() 
{
    return hits == length;
}