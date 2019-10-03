#ifndef BOARD_HPP
#define BOARD_HPP

#include <iostream>
#include <string>

#include "linkedlist.hpp"

using std::string;
using std::ostream;

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


struct RowNode {
    LinkedList *data_list;
    RowNode *up, *down;

    RowNode(RowNode *down = nullptr): data_list(new LinkedList), up(nullptr), down(down) {}
    ~RowNode(){
        delete data_list;
    }
};

class Board {
    int rows, cols, height;
    RowNode *list_;

    RowNode* push_row();
    RowNode* insert_row_on(RowNode *base);
    void put_squares_on(RowNode **r, int a);
    void put_squares_on(RowNode **r, int a, int b);
    void clear_row(RowNode *r);
public:
    Board(int r = 0, int c = 0): rows(r), cols(c), height(0),
                                 list_(nullptr) {}

    ~Board() {
        while (list_ != nullptr){
            clear_row(list_);
        }
        std::cout << "destruct finish: height = " << height << std::endl;
    }

    void process_tetromino(string type, int ref_pt);
    void place_tetromino(string type, int ref_pt);
    bool validate_input(string type, int pt);
    void check_clear();
    bool check_gameover();
    void clear_exceed_rows();

    friend ostream& operator<< (ostream &out, const Board &b);
};


ostream& operator<< (ostream &out, const Board &b){
    for (int i = b.rows; i > b.height; i--){
        for (int j = 0; j < b.cols; j++){
            out << "0";
        } out << std::endl;
    }
    for (RowNode *crow = b.list_; crow != nullptr; crow = crow->down){
        int i = 0;
        for (Node *curr = crow->data_list->get_head(); curr != nullptr; curr = curr->next){
            for (; i < curr->data; i++){
                out << "0";
            }
            out << "1";
            i++;
        }
        for (; i < b.cols; i++){
            out << "0";
        } out << "  " << crow->data_list->size() << std::endl;
    }
    return out;
}


RowNode* Board::push_row(){
    RowNode *temp = new RowNode(list_);
    list_->up = temp;
    list_ = temp;
    height++;
    return temp;
}

RowNode* Board::insert_row_on(RowNode *base){
    RowNode *temp = new RowNode(base);
    base->up = temp;
    height++;
    return temp;
}

void Board::put_squares_on(RowNode **r, int a){
    if (*r == nullptr){
        *r = push_row();
    }
    (*r)->data_list->insert(a);
}

void Board::put_squares_on(RowNode **r, int a, int b){
    if (*r == nullptr){
        *r = push_row();
    }
    (*r)->data_list->insert(a, b);
}

void Board::clear_row(RowNode *r){
    std::cout << "clear one row" << std::endl;
    if (r->up != nullptr){
        r->up->down = r->down;
    }
    if (r->down != nullptr){
        r->down->up = r->up;
    }
    if (list_ == r){
        list_ = r->down;
    }
    height--;
    delete r;
}


void Board::place_tetromino(string type, int ref_pt){
    using std::cout;
    if (list_ == nullptr){
        list_ = new RowNode;
        height = 1;
    }
    
    RowNode *curr = list_, *ins_row = nullptr;
    if (type == "T1"){
        while ((curr != nullptr && curr->data_list->empty_between(ref_pt + 1, ref_pt + 1)) && 
               (curr->up == nullptr || curr->up->data_list->empty_between(ref_pt, ref_pt + 2)) ){
            ins_row = curr;
            curr = curr->down;
        }
        
        put_squares_on(&ins_row, ref_pt + 1);
        ins_row = ins_row->up;
        put_squares_on(&ins_row, ref_pt, ref_pt + 2);
    }
    else if (type == "T2"){
        while ((curr != nullptr && curr->data_list->empty_between(ref_pt + 1, ref_pt + 1)) && 
               (curr->up == nullptr || curr->up->data_list->empty_between(ref_pt, ref_pt + 1)) ){
            ins_row = curr;
            curr = curr->down;
        }

        put_squares_on(&ins_row, ref_pt + 1);
        ins_row = ins_row->up;
        put_squares_on(&ins_row, ref_pt, ref_pt + 1);
        ins_row = ins_row->up;
        put_squares_on(&ins_row, ref_pt + 1);
    }
    else if (type == "T3"){
        while (curr != nullptr && 
               curr->data_list->empty_between(ref_pt, ref_pt + 2)){
            ins_row = curr;
            curr = curr->down;
        }

        put_squares_on(&ins_row, ref_pt, ref_pt + 2);
        ins_row = ins_row->up;
        put_squares_on(&ins_row, ref_pt + 1);

    }
    else if (type == "T4"){
        while ((curr != nullptr && curr->data_list->empty_between(ref_pt, ref_pt)) && 
               (curr->up == nullptr || curr->up->data_list->empty_between(ref_pt, ref_pt + 1)) ){
            ins_row = curr;
            curr = curr->down;
        }
        
        put_squares_on(&ins_row, ref_pt);
        ins_row = ins_row->up;
        put_squares_on(&ins_row, ref_pt, ref_pt + 1);
        ins_row = ins_row->up;
        put_squares_on(&ins_row, ref_pt);

    }
    else if (type == "L1"){
        while (curr != nullptr && curr->data_list->empty_between(ref_pt, ref_pt + 1)){
            ins_row = curr;
            curr = curr->down;
        }
        
        put_squares_on(&ins_row, ref_pt, ref_pt + 1);
        ins_row = ins_row->up;
        put_squares_on(&ins_row, ref_pt);
        ins_row = ins_row->up;
        put_squares_on(&ins_row, ref_pt);

    }
    else if (type == "L2"){
        while ((curr != nullptr && curr->data_list->empty_between(ref_pt, ref_pt)) && 
               (curr->up == nullptr || curr->up->data_list->empty_between(ref_pt, ref_pt + 2)) ){
            ins_row = curr;
            curr = curr->down;
        }
        
        put_squares_on(&ins_row, ref_pt);
        ins_row = ins_row->up;
        put_squares_on(&ins_row, ref_pt, ref_pt + 2);
    }
    else if (type == "L3"){
        while ((curr != nullptr && curr->data_list->empty_between(ref_pt + 1, ref_pt + 1)) && 
               (curr->up == nullptr || curr->up->up == nullptr ||
                curr->up->up->data_list->empty_between(ref_pt, ref_pt + 1)) ){
            ins_row = curr;
            curr = curr->down;
        }
        
        put_squares_on(&ins_row, ref_pt + 1);
        ins_row = ins_row->up;
        put_squares_on(&ins_row, ref_pt + 1);
        ins_row = ins_row->up;
        put_squares_on(&ins_row, ref_pt, ref_pt + 1);

    }
    else if (type == "L4"){
        while (curr != nullptr && curr->data_list->empty_between(ref_pt, ref_pt + 2)){
            ins_row = curr;
            curr = curr->down;
        }

        put_squares_on(&ins_row, ref_pt, ref_pt + 2);
        ins_row = ins_row->up;
        put_squares_on(&ins_row, ref_pt + 2);
    }
    else if (type == "J1"){
        while (curr != nullptr && curr->data_list->empty_between(ref_pt, ref_pt + 1)){
            ins_row = curr;
            curr = curr->down;
        }

        put_squares_on(&ins_row, ref_pt, ref_pt + 1);
        ins_row = ins_row->up;
        put_squares_on(&ins_row, ref_pt + 1);
        ins_row = ins_row->up;
        put_squares_on(&ins_row, ref_pt + 1);
    }
    else if (type == "J2"){
        while (curr != nullptr && curr->data_list->empty_between(ref_pt, ref_pt + 2)){
            ins_row = curr;
            curr = curr->down;
        }

        put_squares_on(&ins_row, ref_pt, ref_pt + 2);
        ins_row = ins_row->up;
        put_squares_on(&ins_row, ref_pt);
    }
    else if (type == "J3"){
        while ((curr != nullptr && curr->data_list->empty_between(ref_pt, ref_pt)) && 
               (curr->up == nullptr || curr->up->up == nullptr ||
                curr->up->up->data_list->empty_between(ref_pt, ref_pt + 1)) ){
            ins_row = curr;
            curr = curr->down;
        }

        put_squares_on(&ins_row, ref_pt);
        ins_row = ins_row->up;
        put_squares_on(&ins_row, ref_pt);
        ins_row = ins_row->up;
        put_squares_on(&ins_row, ref_pt, ref_pt + 1);

    }
    else if (type == "J4"){
        while ((curr != nullptr && curr->data_list->empty_between(ref_pt + 2, ref_pt + 2)) && 
               (curr->up == nullptr || curr->up->data_list->empty_between(ref_pt, ref_pt + 2)) ){
           ins_row = curr;
            curr = curr->down;
        }

        put_squares_on(&ins_row, ref_pt + 2);
        ins_row = ins_row->up;
        put_squares_on(&ins_row, ref_pt, ref_pt + 2);
    }
    else if (type == "S1"){
        while ((curr != nullptr && curr->data_list->empty_between(ref_pt, ref_pt + 1)) && 
               (curr->up == nullptr || curr->up->data_list->empty_between(ref_pt + 1, ref_pt + 2)) ){
            ins_row = curr;
            curr = curr->down;
        }

        put_squares_on(&ins_row, ref_pt, ref_pt + 1);
        ins_row = ins_row->up;
        put_squares_on(&ins_row, ref_pt + 1, ref_pt + 2);
    }
    else if (type == "S2"){
        while ((curr != nullptr && curr->data_list->empty_between(ref_pt + 1, ref_pt + 1)) && 
               (curr->up == nullptr || curr->up->data_list->empty_between(ref_pt, ref_pt + 1)) ){
            ins_row = curr;
            curr = curr->down;
        }

        put_squares_on(&ins_row, ref_pt + 1);
        ins_row = ins_row->up;
        put_squares_on(&ins_row, ref_pt, ref_pt + 1);
        ins_row = ins_row->up;
        put_squares_on(&ins_row, ref_pt);
    }
    else if (type == "Z1"){
        while ((curr != nullptr && curr->data_list->empty_between(ref_pt + 1, ref_pt + 2)) && 
               (curr->up == nullptr || curr->up->data_list->empty_between(ref_pt, ref_pt + 1)) ){
            ins_row = curr;
            curr = curr->down;
        }

        put_squares_on(&ins_row, ref_pt + 1, ref_pt + 2);
        ins_row = ins_row->up;
        put_squares_on(&ins_row, ref_pt, ref_pt + 1);
    }
    else if (type == "Z2"){
        while ((curr != nullptr && curr->data_list->empty_between(ref_pt, ref_pt)) && 
               (curr->up == nullptr || curr->up->data_list->empty_between(ref_pt, ref_pt + 1)) ){
            ins_row = curr;
            curr = curr->down;
        }

        put_squares_on(&ins_row, ref_pt);
        ins_row = ins_row->up;
        put_squares_on(&ins_row, ref_pt, ref_pt + 1);
        ins_row = ins_row->up;
        put_squares_on(&ins_row, ref_pt + 1);

    }
    else if (type == "I1"){
        while (curr != nullptr && curr->data_list->empty_between(ref_pt, ref_pt)){
            ins_row = curr;
            curr = curr->down;
        }

        put_squares_on(&ins_row, ref_pt);
        ins_row = ins_row->up;
        put_squares_on(&ins_row, ref_pt);
        ins_row = ins_row->up;
        put_squares_on(&ins_row, ref_pt);
        ins_row = ins_row->up;
        put_squares_on(&ins_row, ref_pt);
    }
    else if (type == "I2"){
        while (curr != nullptr && curr->data_list->empty_between(ref_pt, ref_pt + 3)){
            ins_row = curr;
            curr = curr->down;
        }

        put_squares_on(&ins_row, ref_pt, ref_pt + 3);
    }
    else if (type == "O"){
        while (curr != nullptr && curr->data_list->empty_between(ref_pt, ref_pt + 1)){
            ins_row = curr;
            curr = curr->down;
        }

        put_squares_on(&ins_row, ref_pt, ref_pt + 1);
        ins_row = ins_row->up;
        put_squares_on(&ins_row, ref_pt, ref_pt + 1);
    }
}


void Board::process_tetromino(string type, int ref_pt){
    if (list_ == nullptr){
        place_tetromino(type, ref_pt);
        
    }


}

void Board::check_clear(){
    // TODO: check if any row should be cleared
    for (RowNode *curr = list_; curr != nullptr; ){
        RowNode *temp = curr;
        curr = curr->down;
        if (temp->data_list->size() == cols){
            clear_row(temp);
        }
    }
}

bool Board::check_gameover(){
    return height > rows;
}

void Board::clear_exceed_rows(){
    if (height <= rows) {
        return;
    }
    int ex = height - rows;
    for (int i = 0; i < ex; i++){
        clear_row(list_);
    }
}

bool Board::validate_input(string type, int pt){
    int width;
    try {
        width = get_width(type);
    }
    catch (const char *e){
        std::cerr << e << std::endl;
        return false;
    }
    if (pt + width > cols){
        return false;
    }
    return true;
}

#endif