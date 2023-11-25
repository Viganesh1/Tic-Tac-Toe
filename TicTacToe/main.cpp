#include <iostream>
#include <string>
#include <random> 
#include <chrono> 

using namespace std;

char space[3][3] = { {'1', '2', '3'}, {'4', '5', '6'}, {'7', '8', '9'} }; // array representing the board
int row; // variable for row of the board
int column; //variable for column of the board
char currentPlayer = 'X'; // X or O

void printBoard();
void makeMove(string playerName);
void makeAIMove();

void showInstructions() { //instructions for the game
    cout << "Welcome to Tic-Tac-Toe!" << endl;
    cout << "To make a move, enter a number from 1 to 9 corresponding to the position on the board." << endl;
    cout << "The board is numbered as follows:" << endl;
    cout << " 1 | 2 | 3 " << endl;
    cout << "-----------" << endl;
    cout << " 4 | 5 | 6 " << endl;
    cout << "-----------" << endl;
    cout << " 7 | 8 | 9 " << endl;
    cout << "The first player to get three in a row (horizontally, vertically, or diagonally) wins!" << endl;
}

int main() { 
    int option; // Welcome screen
    cout << "Welcome to Tic-Tac-Toe!" << endl;
    cout << "1. Play Game" << endl;
    cout << "2. Instructions" << endl;
    cout << "3. Exit" << endl;
    cout << "Enter your option: ";
    cin >> option;

    switch (option) {
    case 1: { //in Play Game
        string n1, n2;
        cout << "Enter the name of the first player: ";
        cin.ignore();
        getline(cin, n1); // name of the first player
        cout << "Choose opponent:" << endl;
        cout << "1. Play against another player" << endl;
        cout << "2. Play against AI" << endl;
        int opponentOption;
        cout << "Enter your option: ";
        cin >> opponentOption;

        if (opponentOption == 1) { 
            cout << "Enter the name of the second player: ";
            cin.ignore();
            getline(cin, n2);// name of the second player
        }
        else if (opponentOption == 2) {
            n2 = "AI";
        }
        else {
            cout << "Invalid option. Exiting the game." << endl; //  other numbers chosen other than 2 
            return 1;
        }

        cout << n1 << " is player 1, so he/she will play first" << endl; // first turn
        printBoard();

        for (int move = 0; move < 9; move++) {
            if (move % 2 == 0) {
                makeMove(n1);
            }
            else {
                if (n2 == "AI") {
                    makeAIMove();
                }
                else {
                    makeMove(n2);
                }
            }

            printBoard();

            if (move >= 4) { 
                cout << "Checking for a win..." << endl; //finding the winner
                if (space[row][0] == space[row][1] && space[row][1] == space[row][2] ||
                    space[0][column] == space[1][column] && space[1][column] == space[2][column] ||
                    space[0][0] == space[1][1] && space[1][1] == space[2][2] ||
                    space[0][2] == space[1][1] && space[1][1] == space[2][0]) {
                    if (currentPlayer == 'X') {
                        cout << "Player " << " (" << n2 << ") wins!" << endl;
                    }
                    else {
                        if (n2 == "AI") {
                            cout << "AI wins!" << endl;
                        }
                        else if (currentPlayer == 'O') {
                            cout << "Player " << " (" << n1 << ") wins!" << endl;
                        }
                    }
                    return 0;
                }
            }
        }

        cout << "It's a draw! The board is full." << endl; // game ends in a draw if no one wins
        return 0;
    }

    case 2: {
        showInstructions(); //2. Instructions
        break;
    }

    case 3: {
        cout << "Exiting the game. Goodbye!" << endl; //3. Exit
        break;
    }

    default: {
        cout << "Invalid option. Exiting the game." << endl; //anyother number 
        return 1;
    }
    }

    return 0;
}

void printBoard() { //Board at default
    cout << " " << space[0][0] << " | " << space[0][1] << " | " << space[0][2] << endl;
    cout << "-----------" << endl;
    cout << " " << space[1][0] << " | " << space[1][1] << " | " << space[1][2] << endl;
    cout << "-----------" << endl;
    cout << " " << space[2][0] << " | " << space[2][1] << " | " << space[2][2] << endl;
}

void makeMove(string playerName) { // player's move
    int digit;
    cout << playerName << ", please enter a move (1-9): ";
    cin >> digit;

    if (digit < 1 || digit > 9) {
        cout << "Invalid input! Please enter a number between 1 and 9." << endl;
        makeMove(playerName);
        return;
    }

    row = (digit - 1) / 3;
    column = (digit - 1) % 3;

    if (space[row][column] == 'X' || space[row][column] == 'O') { // if cell already taken
        cout << "Invalid move! Cell already taken. Try again." << endl;
        makeMove(playerName);
        return;
    }

    space[row][column] = currentPlayer;
    currentPlayer = (currentPlayer == 'X') ? 'O' : 'X';
}

void makeAIMove() {
    cout << "AI is making a move..." << endl;
   
    //random number generator
    random_device rd;
    mt19937 gen(rd());
    uniform_int_distribution<int> distribution(1, 9);

    int digit;
    do {
        digit = distribution(gen);
        row = (digit - 1) / 3;
        column = (digit - 1) % 3;
    } while (space[row][column] == 'X' || space[row][column] == 'O');

    space[row][column] = currentPlayer;
    currentPlayer = (currentPlayer == 'X') ? 'O' : 'X';
}
