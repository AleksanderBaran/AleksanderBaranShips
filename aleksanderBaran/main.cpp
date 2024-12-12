#include "Player.cc"
#include "Ship.cc"
#include "Board.cc"
#include <iostream>
#include <cstdlib>
#include <thread>
#include <chrono>
using namespace std;
void clearConsoleV2()
{
    cout << "Press enter to continue, but only if its your turn!";
    cin.get();
    system("cls");
}
void clearConsole() 
{
    cout << "Press enter to continue:";
    cin.ignore(numeric_limits<streamsize>::max(), '\n');
    cin.get();
    this_thread::sleep_for(chrono::milliseconds(500));
    system("cls");
}
int main() 
{
    cout << "Welcome to the game of Ships" << endl;
    
    int player1Wins = 0;
    int player2Wins = 0;

    while (true) 
    {
        Board emptyBoard;
        Player player1("Player 1");
        Player player2("Player 2");

        cout << "Player 1 place your ships" << endl;
        emptyBoard.displayBoard();
        cout << "This is how the board looks"<<endl;
        player1.placeShips();
        cout << "You have placed all your ships. After you press enter get out the chair!" << endl;
        clearConsole();
        clearConsoleV2();

        cout << "Player 2 place your ships" << endl;
        emptyBoard.displayBoard();
        cout << "This is how the board looks"<<endl;
        player2.placeShips();
        cout << "You have placed all your ships. After you press enter get out the chair!" << endl;
        clearConsole();
        clearConsoleV2();

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
                clearConsoleV2();
                continue;
            } 
            clearConsole();
            clearConsoleV2();
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
