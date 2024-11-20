#include "Ship.h"
#include "Board.h"
#include <iostream>
using namespace std;

Ship::Ship() : length(0), hits(0) {}

void Ship::setShip(int len) 
{
    length = len;
    hits = 0;
}
bool Ship::isSunk() 
{
    return hits >= length;
}
void Ship::hit()
{
    hits++;
}




