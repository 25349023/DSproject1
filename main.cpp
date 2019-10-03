#include <iostream>
#include <string>

#include "board.hpp"

using namespace std;

int main(){
    int rows, cols;
    cin >> rows >> cols;
    Board board(rows, cols);

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

        if (board.check_gameover()){
            break;
        }
        
        board.check_clear();
    }

    return 0;
}
