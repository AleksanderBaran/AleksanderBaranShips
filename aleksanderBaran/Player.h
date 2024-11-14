#ifndef PLAYER_H
#define PLAYER_H
#include "board.h"
#include <string>
#include <iostream>
using namespace std;

class Player {
public:
    string name;
    Board board;
    int wins;

    Player(string n);
    char chooseDirection();
    void placeShips();
    bool shoot(Board &opponentBoard, int x, int y);
    void resetBoard();
};

#endif