#include "Player.h"
#include <iostream>
using namespace std;

Player::Player(string n) : name(n), wins(0) // I couldn't figure it out so i had to ask blackbox for help
{

}

char Player::chooseDirection() 
{
    char direction;
    while (true) 
    {
        cout << "Choose direction (u - up, d - down, l - left, r - right): ";
        cin >> direction;
        if (direction == 'u' || direction == 'U' || direction == 'D' || direction == 'L' || direction == 'R' || direction == 'd' || direction == 'l' || direction == 'r') 
        {
            return direction;
        }
        cout << "Invalid direction, try again." << endl;
    }
}

void Player::placeShips() 
{
    int shipLengths[] = {4, 3, 2, 1};
    int shipCount[] = {1, 2, 3, 4};

    for (int r = 0; r < 4; r++) 
    {
        for (int i = 0; i < shipCount[r]; i++) 
        {
            char rowChar;
            int x, y;
            char direction;

            cout << "Placing a ship of length " << shipLengths[r] << endl;

            while (true) 
            {
                cout << "Enter starting coordinates (e.g., A1, B5): ";
                cin >> rowChar >> y;
                y--; 
                x = static_cast<int>(rowChar) - 'A';  // Convert char to index I am not going to lie I didn't know how to do it so I got it from ai

                direction = chooseDirection();

                if (board.canPlaceShip(x, y, shipLengths[r], direction)) 
                {
                    board.placeShip(x, y, shipLengths[r], direction);
                    board.displayBoard();
                    break;
                } 
                else 
                {
                    cout << "Cannot place ship there. Try again." << endl;
                }
            }
        }
    }
}
bool Player::shoot(Board &opponentBoard, int x, int y) 
{
    if (x < 0 || x >= BOARD_SIZE || y < 0 || y >= BOARD_SIZE) 
    {
        cout << "Invalid coordinates! Try again." << endl;
        return true; 
    }
    else if (opponentBoard.shotBoard[x][y] == HIT || opponentBoard.shotBoard[x][y] == MISS) 
    {
        cout << "You've already shot at this cell!" << endl;
        return true;
    }
    else if (opponentBoard.grid[x][y] == SHIP) 
    {
        cout << "Hit!" << endl;
        opponentBoard.grid[x][y] = HIT;
        opponentBoard.shotBoard[x][y] = HIT;
        return true;
    }
    cout << "You missed!Get out the chair!" << endl;
    opponentBoard.shotBoard[x][y] = MISS;
    return false;
}
void Player::resetBoard()
{
    board.resetBoard();
}