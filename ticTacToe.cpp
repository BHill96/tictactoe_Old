/***************************************************************
 Blake Hillier
 28 June 2018
 This file contains all member functions of the TicTacToe class.
 ***************************************************************/

#ifndef ticTacToe_cpp
#define ticTacToe_cpp

#include "ticTacToe.h"
#include <iostream>
#include <algorithm>
#include <limits>
#include <stdlib.h>
#include <time.h>
#include <vector>

using namespace std;

// Creates the array and fills it with '#' as a blank space.
TicTacToe::TicTacToe() {
    turn = 'O';
    for (int i = 0; i < 9; i++)
        board[i] = '#';
}

// Returns true if there is empty space, or false.
bool TicTacToe::areTurnsLeft() {
    for (int i = 0; i < 9; i++) {
        if (board[i] == '#') {
            return true;
        }
    }
    return false;
}

// Tells the main program if the game is over.
char TicTacToe::gameStatus() {
    if ((board[0] == turn && board[1] == turn && board[2] == turn) ||
       (board[3] == turn && board[4] == turn && board[5] == turn) ||
       (board[6] == turn && board[7] == turn && board[8] == turn) ||
       (board[0] == turn && board[3] == turn && board[6] == turn) ||
       (board[1] == turn && board[4] == turn && board[7] == turn) ||
       (board[2] == turn && board[5] == turn && board[8] == turn) ||
       (board[0] == turn && board[4] == turn && board[8] == turn) ||
       (board[2] == turn && board[4] == turn && board[6] == turn)) {
        return 'W';
    } else {
        changeTurn();
        if ((board[0] == turn && board[1] == turn && board[2] == turn) ||
            (board[3] == turn && board[4] == turn && board[5] == turn) ||
            (board[6] == turn && board[7] == turn && board[8] == turn) ||
            (board[0] == turn && board[3] == turn && board[6] == turn) ||
            (board[1] == turn && board[4] == turn && board[7] == turn) ||
            (board[2] == turn && board[5] == turn && board[8] == turn) ||
            (board[0] == turn && board[4] == turn && board[8] == turn) ||
            (board[2] == turn && board[4] == turn && board[6] == turn)) {
            changeTurn();
            return 'L';
        } else if (!areTurnsLeft()) {
            changeTurn();
            return 'D';
        } else {
            changeTurn();
            return 'C';
        }
    }
}

// Manages the players turn in the game.
void TicTacToe::playerTurn() {
    // Ask the user where they want to play, and subtract one for index
    int index;
    cout << "Enter the index of an empty square to play your piece (1-9): ";
    cin >> index;
    index = index - 1;

    // Check if space is blank
    while (board[index] != '#') { 
        cout << "\nERROR: SPACE NOT EMPTY!" << endl;
        cout << "Enter the index of an empty square to play your piece (1-9): ";
        cin >> index;
        index = index - 1;
    } 
    
    board[index] = turn;
}

// Displays the board on the screen.
void TicTacToe::display() {
    cout << board[0] << " " << board[1] << " " << board[2] << endl;
    cout << board[3] << " " << board[4] << " " << board[5] << endl;
    cout << board[6] << " " << board[7] << " " << board[8] << endl;
}

// Sets every index to '#'.
void TicTacToe::reset() {
    turn = 'O';
    for (int i = 0; i < 9; i++)
        board[i] = '#';
}

// Determines the best move by minimizing the opponents returns
int TicTacToe::minimax(char * newBoard, bool isMaximizer, int depth, int alpha, int beta) {
    // Checks if game is at a final position
    char status = gameStatus();

    // If it is the computer's turn
    if (isMaximizer) {
        if (status == 'W') // AI won
            return 10 - depth;
        else if (status == 'L') // User won
            return -10 + depth;
        else if (status == 'D') // Draw
            return depth;
        else { // No final position
            int bestVal = numeric_limits<int>::min();

            // If the spot is empty, check all possible positions based on that spot
            // Then set the spot back to empty
            for (int i = 0; i < 9; i++) {
                if (newBoard[i] == '#') {
                    newBoard[i] = currentTurn();
	            changeTurn();
		    bestVal = max(bestVal, minimax(newBoard, false, depth + 1, alpha, beta));
	            newBoard[i] = '#';
                    changeTurn();
                    
                    // Find the smallest potential value for the parent node
                    // If it's smaller than alpha, stop searching sibling nodes 
                    alpha = max(bestVal, alpha);
                    if (beta <= alpha)
                        break;
                }
            }
            return bestVal;
        }
    // If it is the user's turn
    } else {
        if (status == 'W') // User won
            return -10 + depth;
        else if (status == 'L') // AI won
            return 10 - depth;
        else if (status == 'D') // Draw
            return depth;
        else { // No final position
            int bestVal = numeric_limits<int>::max();
            
            // If the spot is empty, check all possible positions based on that spot
            // Then set the spot back to empty
            for (int i = 0; i < 9; i++) {
                if (newBoard[i] == '#') {
                    newBoard[i] = currentTurn();
	            changeTurn();
                    bestVal = min(bestVal, minimax(newBoard, true, depth + 1, alpha, beta));
	            newBoard[i] = '#';
                    changeTurn();
                   
                    // Find the smallest potential value for the parent node
                    // If it's smaller than alpha, stop searching sibling nodes 
                    beta = min(bestVal, beta);
                    if (beta <= alpha)
                        break;
                }
            }
            return bestVal;
        }
    }
}

// Manages the computer's turn
void TicTacToe::AITurn() {
   // Parallel arrays tracking the best moves by score and index
    vector<int> bestVals;
    vector<int> indices;
    bestVals.push_back(numeric_limits<int>::min());
    indices.push_back(-1);

    // If the spot is empty, check all possible positions based on that spot
    // If that spot contains the best score, store the score and index
    // Set the spot back to enpty
    for (int i = 0; i < 9; i++) {
        if (board[i] == '#') {
            board[i] = currentTurn();
            changeTurn();
            int score = minimax(board, false, 1, numeric_limits<int>::min(), 
                                numeric_limits<int>::max());
            if (score > bestVals.front()) {
                // Reset bestVal and index
                bestVals.clear();
                indices.clear();
                // Add score and it's index
                bestVals.push_back(score);
                indices.push_back(i);
            } else if (score == bestVals.front()) {
                // Add score and index
                bestVals.push_back(score);
                indices.push_back(i);
            }
            board[i] = '#';
            changeTurn();
        }
    }

    // picks a random move from the list of best moves
    int index = rand() % bestVals.size();
    board[indices.at(index)] = currentTurn();
}

// Changes the active piece on the board.
void TicTacToe::changeTurn() {
    if (turn == 'X')
        turn = 'O';
    else
        turn = 'X';
}
#endif
