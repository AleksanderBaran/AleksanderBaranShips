#include "Board.h"
#include "Ship.h"
#include <iostream>
using namespace std;

Board::Board() 
{
    for (int i = 0; i < BOARD_SIZE; i++) 
    {
        for (int j = 0; j < BOARD_SIZE; j++) 
        {
            grid[i][j] = EMPTY;
            shotBoard[i][j] = WATER;
        }
    }
    shipCount = 0;
}
void Board::displayBoard() 
{
    cout << "  ";

    for (int i = 0; i < BOARD_SIZE; i++) 
    {
        cout << char('A' + i) << " ";
    }
    cout << endl;

    for (int y = 0; y < BOARD_SIZE; y++) 
    {
        cout << y + 1 << " ";

        for (int x = 0; x < BOARD_SIZE; x++) 
        {
            if (grid[x][y] == SHIP) 
            {
                cout << "S "; 
            } 
            else if (grid[x][y] == HIT) 
            {
                cout << "X "; 
            } 
            else if (grid[x][y] == MISS) 
            {
                cout << "O "; 
            } 
            else 
            {
                cout << "~ "; 
            }
        }
        cout << endl;
    }
}

void Board::displayOpponentBoard() 
{
    cout << "  ";
    for (int i = 0; i < BOARD_SIZE; i++) 
    {
        cout << char('A' + i) << " ";
    }
    cout << endl;

    for (int y = 0; y < BOARD_SIZE; y++) 
    {
        cout << y + 1 << " ";

        for (int x = 0; x < BOARD_SIZE; x++) 
        {
            if (shotBoard[x][y] == HIT) 
            {
                cout << "X ";
            } 
            else if (shotBoard[x][y] == MISS) 
            {
                cout << "O ";
            } 
            else 
            {
                cout << "~ ";
            }
        }
        cout << endl;
    }
}
void Board::placeShip(int x, int y, int length, char direction) 
{
    if (!canPlaceShip(x, y, length, direction)) 
    {
        cout << "Cannot place ship here!" << endl;
        return; // return beacuase i cant return 0 bc its void
    }

    int directionX = 0;
    int directionY = 0;

    if (direction == 'r' || direction == 'R')
    {
        directionX = 1;
    } 
    else if (direction == 'l' || direction == 'L') 
    {
        directionX = -1;
    }
    else if (direction == 'u' || direction == 'U') 
    {
        directionY = -1;
    } 
    else if (direction == 'd' || direction == 'D') 
    {
        directionY = 1;
    }

    for (int i = 0; i < length; i++) 
    {
        int nx = x + i * directionX;
        int ny = y + i * directionY;
        grid[nx][ny] = SHIP;
    }

    //I created a pointer here for the nex available ship in the array
    Ship* newShip = &ships[shipCount];
    newShip->setShip(length);
    
    //here im "storaging" ship postitions (idk if i wrote it right)
    for (int i = 0; i < length; i++) 
    {
        int nx = x + i * directionX;
        int ny = y + i * directionY;
        grid[nx][ny] = SHIP;
        shipPositions[shipCount][i].x = nx;
        shipPositions[shipCount][i].y = ny;
    } 
    shipCount++;
    cout << "Ship placed successfully!" << endl;
}
bool Board::canPlaceShip(int startX, int startY, int length, char direction) 
{
    int directionX = 0;
    int directionY = 0;

    if (direction == 'r' || direction == 'R') 
    {
        directionX = 1;  
        directionY = 0;
    } 
    else if (direction == 'd' || direction == 'D') 
    {
        directionX = 0;
        directionY = 1;  
    } 
    else if (direction == 'u' || direction == 'U') 
    {
        directionX = 0;
        directionY = -1;
    } 
    else if (direction == 'l' || direction == 'L') 
    {
        directionX = -1;
        directionY = 0;
    }
    else 
    {
        return false;
    }

    for (int i = 0; i < length; i++) 
    {
        int currentX = startX + i * directionX;
        int currentY = startY + i * directionY;

        if (currentX < 0 || currentX >= BOARD_SIZE || currentY < 0 || currentY >= BOARD_SIZE) 
        {
            return false;
        }
        else if (grid[currentX][currentY] != EMPTY) 
        {
            return false;
        }
        for (int dx = -1; dx <= 1; dx++)
        {
            for (int dy = -1; dy <= 1; dy++) 
            {
                int checkX = currentX + dx;
                int checkY = currentY + dy;

                if (checkX >= 0 && checkX < BOARD_SIZE && checkY >= 0 && checkY < BOARD_SIZE) 
                {
                    if (grid[checkX][checkY] != EMPTY) 
                    {
                        return false; 
                    }
                }
            }
        }
    }

    return true; 
}
bool Board::allShipsDestroyed() 
{
    for (int i = 0; i < BOARD_SIZE; i++)
     {
        for (int j = 0; j < BOARD_SIZE; j++)
         {
            if (grid[i][j] == SHIP) 
            {
                return false;
            }
        }
    }
    return true;  
}
void Board::resetBoard() 
{
    for (int i = 0; i < BOARD_SIZE; i++) 
    {
        for (int j = 0; j < BOARD_SIZE; j++) 
        {
            grid[i][j] = EMPTY;
            shotBoard[i][j] = WATER;
        }
    }
    shipCount = 0;
}
void Board::markMiss(int x, int y) 
{
    shotBoard[x][y] = MISS;
}
void Board::markAroundShip(int shipIndex) 
{
    for (int i = 0; i < ships[shipIndex].length; i++) 
    {
        int shipX = shipPositions[shipIndex][i].x;
        int shipY = shipPositions[shipIndex][i].y;
        
        for (int dx = -1; dx <= 1; dx++) 
        {
            for (int dy = -1; dy <= 1; dy++) 
            {
                int checkX = shipX + dx;
                int checkY = shipY + dy;
                
                if (checkX >= 0 && checkX < BOARD_SIZE && 
                    checkY >= 0 && checkY < BOARD_SIZE) 
                    {
                    if (grid[checkX][checkY] != HIT) 
                    {
                        grid[checkX][checkY] = MISS;
                        shotBoard[checkX][checkY] = MISS;
                    }
                }
            }
        }
    }
}



