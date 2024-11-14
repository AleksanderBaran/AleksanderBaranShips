#ifndef BOARD_H
#define BOARD_H
#include <iostream>
#include "Ship.h"
const int BOARD_SIZE = 10;
const char EMPTY = '.';
const char SHIP = 'S';
const char HIT = 'X';
const char MISS = 'O';
const char WATER = '~'; 

class Board 
{
public:
    char grid[BOARD_SIZE][BOARD_SIZE];  
    char shotBoard[BOARD_SIZE][BOARD_SIZE];  
    int shipCount;
    Ship ships[10];

    Board();
    void displayBoard();
    void displayOpponentBoard();
    void placeShip(int x, int y, int length, char direction);
    bool canPlaceShip(int startX, int startY, int length, char direction);
    bool allShipsDestroyed();
    void markAroundShip(int x, int y, int length, char direction);  // I tried it
    void resetBoard();
};

#endif