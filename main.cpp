#include <iostream>
#include <string>

using namespace std;

class Board {
    int rows, cols;


    void clear_row(int);
public:
    Board(int r = 0, int c = 0): rows(r), cols(c) {
        // TODO: initialize linked list or stack
    }

    void place_tetromino(string, int);
    void check_clear();
    bool check_gameover();
};

void Board::place_tetromino(string kind, int ref_pt){
    
}

void Board::check_clear(){
    // TODO: check if any row should be cleared

    
}

bool Board::check_gameover(){
    
}

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

        board.place_tetromino(currentShape, ref_point);

        if (board.check_gameover()){
            break;
        }
        
        board.check_clear();
    }

    return 0;
}
