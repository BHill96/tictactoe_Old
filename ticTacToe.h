/*****************************************************************************
 Blake Hillier
 28 June 2017
 This file outlines the member variables and functions of the TicTacToe class.
 *****************************************************************************/

#ifndef ticTacToe_h
#define ticTacToe_h

class TicTacToe {
    char board[9];
    char turn; // Tracks the current players turn by their symbol

    public:
        /*********************************************************
         Constructor
         Input: None
         Returns: None
         Creates the array and fills it with '#' as a blank space.
         *********************************************************/
        TicTacToe();
        
        /****************************************
         currentTurn
         Input: None
         Returns: char turn as current player
         Returns 'X' or 'O' as the active player.
         ****************************************/
        char currentTurn() { return turn; };
     
        /*****************************
         areTurnsLeft
         Input: None
         Returns: true if '#' is found
                  false otherwise 
         *****************************/
        bool areTurnsLeft();

        /**************************************************
         isGameOver
         Input: None
         Returns: W if the current player won
                  L if the current player lost
                  T if the game tied
                  C if the current game is still continuing
         Tells the main program if the game is over.
         **************************************************/
         char gameStatus();
      
        /*************************************
         playerTurn
         Input: None
         Returns: None
         Manages the players turn in the game.
         *************************************/
        void playerTurn();

        /*********************************
         display
         Input: None
         Returns: None
         Displays the board on the screen.
         *********************************/
        void display();
        
        /************************
         reset
         Input: None
         Returns: None
         Sets every index to '#'.
         ************************/
        void reset();

        /****************************************************************
         minimax
         Input: char * newBoard - pointer to the current game board
                bool isMaximizer - true if looking to maximize turn
                                   false if looking to minimize turn
                int depth - distance from the root node
                int alpha - best value for the parent node
                int beta - smallest value for the parent node
         Returns: the best score for the current node.
         Calculates the best score for each move at the current node.
         The child node of the root with the best score is used in AITurn
         ****************************************************************/
        int minimax(char * newBoard, bool isMaximizer, int depth, int alpha, int beta);

        /**********************
         AITurn
         Input: None
         Returns: None
         Manages the AI's turn.
         **********************/
        void AITurn();

        /**************************************
         changeTurn
         Input: None
         Returns: None
         Changes the active piece on the board.
         **************************************/
        void changeTurn();
};

#endif
