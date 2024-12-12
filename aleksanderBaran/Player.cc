#include "Player.h"
#include "Ship.h"
#include "Board.h"
#include <iostream>
using namespace std;

Player::Player(string n) : name(n), wins(0) {}

char Player::chooseDirection() 
{
    char direction;
    while (true) 
    {
        cout << "Choose direction (u - up, d - down, l - left, r - right): ";
        cin >> direction;
        if (direction == 'u' || direction == 'U' || direction == 'D' || direction == 'L' || direction == 'R' || direction == 'd' || direction == 'l' || direction == 'r') {
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
            char rowLetter;
            int x;
            int y;
            char direction;

            cout << "Placing a ship of length " << shipLengths[r] << endl;

            while (true)
            {
                cout << "Enter starting coordinates (A1, I10): ";
                cin >> rowLetter >> y;
                y--;
                rowLetter = toupper(rowLetter);
                x = static_cast<int>(rowLetter) - 'A';

                if (x < 0 || x >= BOARD_SIZE || y < 0 || y >= BOARD_SIZE) 
                {
                    cout << "Invalid coordinates! Please enter values within the range A1 to J10." << endl;
                    continue;
                }

                if (shipLengths[r] == 1) 
                {
                    if (!board.canPlaceShip(x, y, 1, 'r')) 
                    {
                        cout << "Out of bounds for a single ship. Try again." << endl;
                        continue;
                    }
                    board.placeShip(x, y, shipLengths[r], direction);
                    board.displayBoard();
                    break;     
                }

                direction = chooseDirection();

                if (direction != 'u' && direction != 'd' && direction != 'l' && direction != 'r') 
                {
                    cout << "Invalid direction! Please choose (u, d, l, r)." << endl;
                    continue;
                }

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
    if (opponentBoard.shotBoard[x][y] == HIT || opponentBoard.shotBoard[x][y] == MISS) 
    {
        cout << "You've already shot at this cell! Follow the instructions and try again!" << endl;
        return true;
    }
    if (opponentBoard.grid[x][y] == SHIP) 
    {
        cout << "Hit! You get another try! Follow the instructions and stay in the chair!" << endl;

        opponentBoard.grid[x][y] = HIT;
        opponentBoard.shotBoard[x][y] = HIT;

        for (int i = 0; i < opponentBoard.shipCount; i++) 
        {
            for (int j = 0; j < opponentBoard.ships[i].length; j++) 
            {
                if (opponentBoard.shipPositions[i][j].x == x && opponentBoard.shipPositions[i][j].y == y) 
                    {
                    opponentBoard.ships[i].hit();
                    if (opponentBoard.ships[i].isSunk()) 
                    {
                        cout << "Ship sunk!" << endl;
                        opponentBoard.markAroundShip(i);
                    }
                    break;
                }
            }
        }
        return true;
    }
    cout << "Miss! Get out of the chair after you press enter!" << endl;
    opponentBoard.grid[x][y] = MISS;
    opponentBoard.shotBoard[x][y] = MISS;
    return false;
}
void Player::resetBoard() 
{
    board.resetBoard();
}
