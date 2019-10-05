#include <iostream>
using namespace std;

class Gameboard {
    private:
        int rows, cols;
        int** board;
    public:
        Gameboard (int rows, int cols) {
            this->rows = rows;
            this->cols = cols;
            board = new int*[rows];
            for (int i = 0; i < rows; i++)
                board[i] = new int[cols];
            for (int j = 0; j < rows; j++) {
                for (int k = 0; k < cols; k++)
                    board[j][k] = 0;
            }
        }
        void print() {
            for (int j = 0; j < rows; j++) {
                for (int k = 0; k < cols; k++)
                    cout << board[j][k] << " ";
                cout << endl;
            }
        }
};



int main (void) {
    int rows, cols;
    cin >> rows >> cols;
    Gameboard mainboard {rows,cols};
    mainboard.print();
    return 0;
}