#include <iostream>
#include <vector>
#include <limits> // Required for input validation

using namespace std;

// Function to display the board
void displayBoard(const vector<char>& board) {
    cout << "\n";
    cout << " " << board[0] << " | " << board[1] << " | " << board[2] << " \n";
    cout << "---+---+---\n";
    cout << " " << board[3] << " | " << board[4] << " | " << board[5] << " \n";
    cout << "---+---+---\n";
    cout << " " << board[6] << " | " << board[7] << " | " << board[8] << " \n";
    cout << "\n";
}

// Function to check if a specific player has won
bool checkWin(const vector<char>& board, char player) {
    // Winning combinations: Rows, Columns, Diagonals
    const int winConditions[8][3] = {
        {0, 1, 2}, {3, 4, 5}, {6, 7, 8}, // Rows
        {0, 3, 6}, {1, 4, 7}, {2, 5, 8}, // Columns
        {0, 4, 8}, {2, 4, 6}             // Diagonals
    };

    for (int i = 0; i < 8; i++) {
        if (board[winConditions[i][0]] == player &&
            board[winConditions[i][1]] == player &&
            board[winConditions[i][2]] == player) {
            return true;
        }
    }
    return false;
}

// Function to check if the game is a draw
bool checkDraw(const vector<char>& board) {
    for (char cell : board) {
        if (cell == ' ') return false; // If empty space exists, not a draw
    }
    return true;
}

// Function to handle player input
int getPlayerMove(const vector<char>& board, char player) {
    int move;
    while (true) {
        cout << "Player " << player << ", enter your move (1-9): ";
        cin >> move;

        // Input validation: Check if input is a number
        if (cin.fail()) {
            cin.clear(); // Clear error flag
            cin.ignore(numeric_limits<streamsize>::max(), '\n'); // Discard invalid input
            cout << "Invalid input. Please enter a number.\n";
        }
        // Check range and availability
        else if (move >= 1 && move <= 9 && board[move - 1] == ' ') {
            return move - 1; // Convert 1-9 input to 0-8 index
        } else {
            cout << "Invalid move. Spot taken or out of range. Try again.\n";
        }
    }
}

int main() {
    char playAgain = 'y';

    while (playAgain == 'y' || playAgain == 'Y') {
        vector<char> board(9, ' '); // Initialize 3x3 board with spaces
        char currentPlayer = 'X';
        bool gameRunning = true;

        cout << "Welcome to Tic-Tac-Toe!\n";

        while (gameRunning) {
            displayBoard(board);

            // 1. Get Move
            int move = getPlayerMove(board, currentPlayer);

            // 2. Update Board
            board[move] = currentPlayer;

            // 3. Check Win
            if (checkWin(board, currentPlayer)) {
                displayBoard(board);
                cout << "Congratulations! Player " << currentPlayer << " wins!\n";
                gameRunning = false;
            }
            // 4. Check Draw
            else if (checkDraw(board)) {
                displayBoard(board);
                cout << "It's a draw!\n";
                gameRunning = false;
            }
            // 5. Switch Player
            else {
                currentPlayer = (currentPlayer == 'X') ? 'O' : 'X';
            }
        }

        cout << "Do you want to play again? (y/n): ";
        cin >> playAgain;
    }

    cout << "Thanks for playing!\n";
    return 0;
}
