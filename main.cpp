#include <iostream>
#include <string>

using namespace std;

int get_width(string type){
    if (type == "T1" || type == "T3" || type == "L2" || type == "L4" ||
        type == "J2" || type == "J4" || type == "S1" || type == "Z1"){
        return 3;
    }
    if (type == "T2" || type == "T4" || type == "L1" || type == "L3" ||
        type == "J1" || type == "J3" || type == "S2" || type == "Z2" ||
        type == "O"){
        return 2;
    }
    if (type == "I1"){
        return 1;
    }
    if (type == "I2"){
        return 4;
    }
    throw "input type error";
}

class Board {
    int rows, cols;


    void clear_row(int r);
    void place_one_square(int r, int c);
public:
    Board(int r = 0, int c = 0): rows(r), cols(c) {
        // TODO: initialize linked list or stack
    }

    ~Board() {

    }

    void place_tetromino(string type, int ref_pt);
    bool validate_input(string type, int pt);
    void check_clear();
    bool check_gameover();
};

void Board::place_tetromino(string type, int ref_pt){
    
}

void Board::check_clear(){
    // TODO: check if any row should be cleared

    
}

bool Board::check_gameover(){
    
}

bool Board::validate_input(string type, int pt){
    int width;
    try {
        width = get_width(type);
    }
    catch (const char *e){
        cerr << e << endl;
        return false;
    }
    if (pt + width > cols){
        return false;
    }
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
