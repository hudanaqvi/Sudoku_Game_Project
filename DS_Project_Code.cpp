#include <iostream>
using namespace std;

class Sudoku {
private:
    int board[9][9];

public:

    //constructor
    Sudoku() {
        int temp[9][9] = {
            {0,0,9, 4,2,0, 0,0,0},
            {0,0,0, 0,0,6, 2,0,1},
            {0,5,0, 0,3,0, 4,0,6},

            {5,0,0, 6,0,0, 0,8,4},
            {0,0,4, 7,5,8, 1,0,0},
            {8,7,0, 0,0,1, 0,5,3},

            {4,9,5, 0,0,0, 0,0,0},
            {0,1,7, 0,0,0, 5,2,0},
            {0,0,0, 0,0,0, 0,0,7}
        };

        for(int i=0;i<9;i++){
            for(int j=0;j<9;j++){
                board[i][j] = temp[i][j];
            }
        }
    }

    //getter
    int getCell(int r, int c) {
        return board[r][c];
    }

    //setter
    void setCell(int r, int c, int value) {
        board[r][c] = value;
    }

    //print board
    void printBoard() {
        cout << "\nCurrent Sudoku Board:\n\n";
        for (int i = 0; i < 9; i++) {
            if(i % 3 == 0) cout << "-------------------------------\n";
            for (int j = 0; j < 9; j++) {
                if(j % 3 == 0) cout << "| ";
                if (board[i][j] == 0)
                    cout << ". ";
                else
                    cout << board[i][j] << " ";
            }
            cout << "|\n";
        }
        cout << "-------------------------------\n";
    }

    //Set difference for checking duplicates
    bool elementInRow(int r, int num) {
        for(int j=0;j<9;j++){
            if(board[r][j] == num) return true;
        }
        return false;
    }

    bool elementInCol(int c, int num) {
        for(int i=0;i<9;i++){
            if(board[i][c] == num) return true;
        }
        return false;
    }

    bool elementInGrid(int r, int c, int num) {
        int sr = r - r % 3;
        int sc = c - c % 3;

        for(int i=sr;i<sr+3;i++){
            for(int j=sc;j<sc+3;j++){
                if(board[i][j] == num) return true;
            }
        }
        return false;
    }

    //Union + Intersection Logic
    bool isValidMove(int r, int c, int num) {
        //AND operator (all conditions must be true)
        bool rowOK = !elementInRow(r, num);
        bool colOK = !elementInCol(c, num);
        bool gridOK = !elementInGrid(r, c, num);

        return rowOK && colOK && gridOK;
    }
};


int main() {
    Sudoku game;
    int row, col, num;

    cout << "=== Sudoku Validity Checker ===\n";

    while(true) {

        try {
            game.printBoard();

            cout << "\nEnter Row (1-9) or 0 to Exit: ";
            cin >> row;
            if(row == 0) break;

            cout << "Enter Column (1-9): ";
            cin >> col;

            cout << "Enter Number (1-9): ";
            cin >> num;

            if(cin.fail()) {
                throw "Invalid Input! Only numbers allowed.";
            }

            //convert to index
            row--; col--;

            if(row<0 || col<0 || row>8 || col>8 || num<1 || num>9) {
                throw "Input out of range!";
            }

            //check validity using discrete logic
            if(game.isValidMove(row, col, num)) {
                game.setCell(row, col, num);
                cout << "\nResult: VALID MOVE \n";
            } else {
                cout << "\nResult: INVALID MOVE \n";
            }
        }

        catch(const char* msg) {
            cout << "\nError: " << msg << "\n";
            cin.clear();
            cin.ignore(1000, '\n');
        }
    }

    cout << "\nProgram Ended.\n";
    return 0;
}


