#include <iostream>
#include <string>

#include "board.hpp"

using namespace std;

int main(){
    int rows, cols;
    cin >> rows >> cols;
    Board board(rows, cols);
    cout << board;
    string currentShape;
    while (cin >> currentShape){
        if (currentShape == "End"){
            break;
        }

        int ref_point;
        cin >> ref_point;
        ref_point -= 1;
        if (!board.validate_input(currentShape, ref_point)){
            cerr << "Input invalid." << endl;
            break;
        }

        board.place_tetromino(currentShape, ref_point);
        board.check_clear();

        cout << board << endl << endl;
        if (board.check_gameover()){
            board.clear_exceed_rows();
            cout << "game over" << endl;
            break;
        }
    }
    cout << board << endl;

    return 0;
}
