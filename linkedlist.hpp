#ifndef LINKEDLIST_HPP
#define LINKEDLIST_HPP


struct Node {
    int data;
    Node *next;

    Node(int d, Node *n = nullptr): data(d), next(n) {}
};

class LinkedList {
    int size_;
    Node *head;

public:
    LinkedList(): size_(0), head(nullptr) {}

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

    void append(int data);
    void remove(int key);

    bool insert(int data);
    Node* find(int key) const;
};

void LinkedList::append(int data){

}

void LinkedList::remove(int key){

}

bool LinkedList::insert(int data){
    if (head == nullptr){
        head = new Node(data);
        return true;
    }
    Node *prev = nullptr;
    for (Node *curr = head; curr != nullptr; curr = curr->next){
        if (curr->data == data){
            return false;
        }
        if (curr->data > data){
            Node *temp = new Node(data, curr);
            if (prev != nullptr){
                prev->next = temp;
            }
            else {
                head = temp;
            }
            return true;
        }
        prev = curr;
    }
    prev->next = new Node(data);
    return true;
}

Node* LinkedList::find(int key) const {
    for (Node *curr = head; curr != nullptr; curr = curr->next){
        if (curr->data == key){
            return curr;
        }
        else if (curr->data > key){
            return nullptr;
        }
    }
}


#endif