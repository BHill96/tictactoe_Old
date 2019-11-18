/************************************************************
 Blake Hillier
 28 June 2018
 This program manages the life cycle of the tic-tac-toe game.
 ************************************************************/

#include "ticTacToe.h"
#include"ticTacToe.cpp"

using namespace std;

int main() {
    TicTacToe game;
    bool run; // Indicates wether the program should keep running
    srand(time(NULL));
  
    try { 
        do {
            char human; // Holds the players symbol
            char AI; // Holds the computers symbol

            // Asks the player which symbol they want
            cout << "X or O? ";
            cin >> human;
            // Relates the board to numbers for the user
            cout << "\nThe board is set up as\n1 2 3\n4 5 6\n7 8 9" << endl << endl;
            // Makes user's symbol capitalized and gives the computer the other symbol
            if (human == 'x' || human == 'X') {
                human = 'X';
                AI = 'O';
            } else if (human == 'o' || human == 'O') {
                human = 'O';
                AI = 'X';
            } else
                throw("Unkown data in variable 'human'.");

            // This loop manages the actual game
            do { 
                // Displays current game information each turn
                game.changeTurn();
                cout << game.currentTurn() << "'s turn:" << endl;
                game.display();
                cout << endl;

                // Calls the appropriate function depending on the active player
                if (game.currentTurn() == human)
                    game.playerTurn();
                else
                    game.AITurn();
            } while (game.gameStatus() == 'C');

            // Tells the user who won or the game was a draw
            switch (game.gameStatus()) {
                case 'W':
                    cout << game.currentTurn() << " won!" << endl;
                    game.display();
                    break;
                case 'D':
                    cout << "It's a draw!" << endl;
                    game.display();
                    break;
                case 'C':
                    game.display();
                    throw("Game loop ended while game was still in progress.");
                default:
                    throw("Unkown error with gameStatus after game loop.");
            }

            // Asks user if they want to play again
            char choice;
            cout << "Again? (y/n) ";
            cin >> choice;

            // Resets the board if the user wants to play
            if (choice == 'y') {
                game.reset();
                run = true;
            } else // Finish running the loop
                run = false;

        } while (run);

        cout << "Created by Blake Hillier.\nStarted on June 28, 2018." << endl;
    }
    catch (string message) {
        cout << "ERROR: " << message << "\nTerminating program";
    }
}
