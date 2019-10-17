#ifndef LINKEDLIST_HPP
#define LINKEDLIST_HPP


struct Node {
    int data;
    Node *next;

    Node(int d, Node *n = nullptr): data(d), next(n) {}
};

class Board;

class LinkedList {
    friend Board;

    int size_;
    Node *head;
    bool in_board;

public:
    LinkedList(bool inb = false): size_(0), head(nullptr), in_board(inb) {}

    ~LinkedList(){
        for (Node *curr = head; curr != nullptr;){
            Node *temp = curr;
            curr = curr->next;
            delete temp;
        }
    }

    int size() const {
        return size_;
    }

    Node* get_head(){
        return head;
    }

    void insert(int data);
    void insert(int a, int b);
    bool empty_between(int a, int b);
};


void LinkedList::insert(int data){
    size_++;
    if (head == nullptr){
        head = new Node(data);
        return;
    }
    Node *prev = nullptr;
    for (Node *curr = head; curr != nullptr; curr = curr->next){
        if (curr->data > data){
            Node *temp = new Node(data, curr);
            if (prev != nullptr){
                prev->next = temp;
            }
            else {
                head = temp;
            }
            return;
        }
        prev = curr;
    }
    prev->next = new Node(data);
}

void LinkedList::insert(int a, int b){
    size_ += (b - a + 1);
    if (head == nullptr || head->data > b){
        Node *old_head = head;
        head = new Node(a);
        Node *temp = head;
        for (int i = a + 1; i <= b; i++, temp = temp->next){
            temp->next = new Node(i);
        }
        temp->next = old_head;
        return;
    }
    Node *prev = nullptr;
    for (Node *curr = head; ; curr = curr->next){
        if (curr == nullptr || curr->data > b){
            Node *temp = prev;
            for (int i = a; i <= b; i++, temp = temp->next){
                temp->next = new Node(i);
            }
            temp->next = curr;
            return;
        }
        prev = curr;
    }
}

bool LinkedList::empty_between(int a, int b){
    for (Node *curr = head; curr != nullptr; curr = curr->next){
        if (a <= curr->data && curr->data <= b){
            return false;
        }
        else if (curr->data > b){
            return true;
        }
    }
    return true;
}

#endif