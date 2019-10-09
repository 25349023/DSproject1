#include <iostream>
#include <string>
#include <fstream>

#include "board.hpp"

using namespace std;

int main(){
    int rows, cols;
    ifstream fin("tetris.data");
    if (!fin){
        cerr << "failed to open tetris.data for reading" << endl;
        return 1;
    }

    fin >> rows >> cols;
    Board board(rows, cols);
    cout << board << endl;
    string currentShape;
    while (fin >> currentShape){
        if (currentShape == "End"){
            break;
        }

        int ref_point;
        fin >> ref_point;
        ref_point -= 1;
        if (!board.validate_input(currentShape, ref_point)){
            cerr << "Input invalid." << endl;
            break;
        }

        board.place_tetromino(currentShape, ref_point);
        board.check_clear();

        cout << board << endl;
        if (board.check_gameover()){
            board.clear_exceed_rows();
            cout << "game over" << endl;
            break;
        }
    }
    fin.close();
    
    cout << board << endl;

    ofstream fout("tetris.final");
    if (!fout){
        cerr << "failed to open tetris.final for writing" << endl;
    }
    fout << board;
    fout.close();

    return 0;
}
