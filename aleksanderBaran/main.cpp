#include "Player.cc"
#include "Ship.cc"
#include "Board.cc"
#include <iostream>
#include <cstdlib>
#include <thread>
#include <chrono>
using namespace std;
void clearConsole() 
{
    cout << "Press enter to continue:";
    cin.ignore(); 
    cin.get();
    this_thread::sleep_for(chrono::seconds(1));
    system("cls");
}
int main() 
{
    cout << "Welcome to the game of Ships" << endl;
    
    int player1Wins = 0;
    int player2Wins = 0;

    while (true) 
    {
        Player player1("Player 1");
        Player player2("Player 2");

        cout << "Player 1 place your ships" << endl;
        player1.placeShips();
        cout << "You have placed all your ships. Get out the chair!" << endl;
        clearConsole();

        cout << "Player 2 place your ships" << endl;
        player2.placeShips();
        cout << "You have placed all your ships. Get out the chair!" << endl;
        clearConsole();

        // I cound figure it out with reference variables so i used pointers to easier use funciton swap
        Player* currentPlayer = &player1;
        Player* opponent = &player2;

        while (!player1.board.allShipsDestroyed() && !player2.board.allShipsDestroyed()) 
        {
            cout << currentPlayer->name << " it's your turn now" << endl;
            currentPlayer->board.displayBoard();
            opponent->board.displayOpponentBoard();

            char rowLetter;
            int y;

            cout << "\nEnter coordinates to shoot (A1, B2, etc): ";
            cin >> rowLetter >> y;

            y--;
            //i did so that it will also work with lower case letters
            rowLetter = toupper(rowLetter);
            int x = static_cast<int>(rowLetter) - 'A';

            

            if (currentPlayer->shoot(opponent->board, x, y)) 
            {
                if (opponent->board.allShipsDestroyed()) 
                {
                    cout << currentPlayer->name << " wins!" << endl;
                    if (currentPlayer == &player1) 
                    {
                        player1Wins++;
                    } 
                    else
                    {
                        player2Wins++;
                    }
                    break; 
                }
                clearConsole();
                continue;
            } 
            clearConsole();
            swap(currentPlayer, opponent);
        }

        cout << "Current Scores: Player 1 - " << player1Wins << " | Player 2 - " << player2Wins << endl;

        char playAgain;
        cout << "Do you want to play again? (y/n): ";
        cin >> playAgain;
        if (playAgain != 'y' && playAgain != 'Y') 
        {
            clearConsole();
            break;
        }
        clearConsole();

        player1.board.resetBoard();
        player2.board.resetBoard();
    }

    cout << "Final Scores: Player 1 - " << player1Wins << ", Player 2 - " << player2Wins << endl;
    cout << "Thanks for playing!" << endl;

    return 0;
}
