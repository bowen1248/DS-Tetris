#define DEBUG
#include <iostream>
#include <string>
using namespace std;

// generate block
class block {
    friend class Gameboard; // get access to board rows and cols
    private:
        int shape[4][2];    // shape[block index][0: x coord. 1: y coord.]
    public:
        // get shape of the block (x,y coordinate of 4 blocks)
        void setblock(int in_shape[], int col, int rows) {
            int ini_col = col - 1;
            for (int i = 0; i < 4; i++) {   // set initial 4 block coordinate
                shape[i][0] = (in_shape[i] % 4) + ini_col;
                shape[i][1] = (in_shape[i] / 4) + rows;
            }
        }
        // make block fall 1 row
        void block_drop() {
            for (int i = 0; i < 4; i++) 
                shape[i][1]--;
        }
};

// overall tetris process and management
class Gameboard {
    private:
        int rows, cols;
        int** board;
    public:
        Gameboard (int rows, int cols) {
            this->rows = rows;
            this->cols = cols;
            board = new int*[rows + 4];
            for (int i = 0; i < rows + 4; i++)
                board[i] = new int[cols];
            for (int j = 0; j < rows + 4; j++) {
                for (int k = 0; k < cols; k++)
                    board[j][k] = 0;
            }
        }
        // to test if block crash after block drop a tile 
        bool clash(block a) {
            for (int i = 0; i < 4; i++) {
                if ((a.shape[i][1] - 1) < 0) return true; 
                else if (board[(a.shape[i][1] - 1)] [a.shape[i][0]] == 1) return true;
            }
            return false;
        }
        // check if board formed a line and drop all block above it
        bool check_line () {
            bool disappear = false;
            for (int i = 0; i < rows + 4; i++) {
                bool form_line = true;
                if (disappear) {
                    form_line = true;
                    for (int k = 0; k < cols; k++)
                        board[i - 1][k] = board[i][k];
                }
                else { 
                    for (int k = 0; k < cols; k++)
                        if (board[i][k] == 0) form_line = false;
                }
                disappear = form_line;
            }
            return disappear;
        }
        // process block things
        bool block_fall(block a) {
            while (!clash(a)) {    // drop block until clash with others
                a.block_drop();
            }
            // record the block position
            for (int i = 0; i < 4; i++) 
                board [a.shape[i][1]] [a.shape[i][0]] = 1;
            // process if line is formed
            while (check_line()) {}
            // see if the block has stacked over border vertical height
            for (int i = 0; i < cols; i++)
                if(board[rows][i] == 1) return 1;   // terminate this game
            
            return 0;   // continue game
        }

        // print out matrix
        void print() {
            for (int j = (rows - 1); j >= 0; j--) {
                for (int k = 0; k < cols; k++)
                    cout << board[j][k];
                cout << endl;
            }
        }
};

int main (void) {
    #ifdef DEBUG    // open files
    freopen("Tetris.data", "r", stdin);
    freopen("Tetris.output", "w", stdout);
    #endif
    int rows, cols; // board total cols and rows
    int block_col;  // store block initial column
    int shape[4];   // 
    int shape_menu[19][4] = {   // record all block shape
        {1,4,5,6}, {1,4,5,9}, {0,1,2,5}, {0,4,5,8}, {0,1,4,8},
        {0,4,5,6}, {1,5,8,9}, {0,1,2,6}, {0,1,5,9}, {0,1,2,4},
        {0,4,8,9}, {2,4,5,6}, {0,1,5,6}, {1,4,5,8}, {1,2,4,5},
        {0,4,5,9}, {0,4,8,12}, {0,1,2,3}, {0,1,4,5}
    };
    string instring;    // get cols and rows
    cin >> rows >> cols;
    Gameboard mainboard {rows,cols};    // initialize matrix
    block b1;   // generate a block 
    bool gameover = false;
    // the loop continues until code terminate or gameover(block vertical > board rows)
    for (cin >> instring; instring.compare("End") && !gameover; cin >> instring) {
        int sel_shape;
        int ini_col;
        // judge the block shape by instring
        switch (instring[0]) {
            case 'T': {if (instring[1] == '1') sel_shape = 0;
                        else if (instring[1] == '2') sel_shape = 1;
                        else if (instring[1] == '3') sel_shape = 2;
                        else sel_shape = 3;
                    } break;
            case 'L': {if (instring[1] == '1') sel_shape = 4;
                        else if (instring[1] == '2') sel_shape = 5;
                        else if (instring[1] == '3') sel_shape = 6;
                        else sel_shape = 7;
                    } break;

            case 'J': {if (instring[1] == '1') sel_shape = 8;
                        else if (instring[1] == '2') sel_shape = 9;
                        else if (instring[1] == '3') sel_shape = 10;
                        else sel_shape = 11;
                    } break;

            case 'S': {if (instring[1] == '1') sel_shape = 12;
                        else sel_shape = 13;
                    } break;
            case 'Z': {if (instring[1] == '1') sel_shape = 14;
                        else sel_shape = 15;
                    } break;
            case 'I': {if (instring[1] == '1') sel_shape = 16;
                        else sel_shape = 17;
                    } break;
            case 'O': sel_shape = 18; break;
            default: sel_shape = 0; break;
        }
        // put shape into shape initializer
        for (int i = 0; i < 4; i++)
            shape[i] = shape_menu[sel_shape][i];
        cin >> ini_col;
        b1.setblock(shape, ini_col, rows);
        // drop the block
        gameover = mainboard.block_fall(b1);
}
    // print last result
    mainboard.print();
    return 0;
}