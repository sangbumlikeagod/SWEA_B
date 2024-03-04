#include <iostream>
#include <stdio.h>
#include <vector>
#include <string>
#include <fstream>
#include <cstring>
using namespace std;


struct Node {
    int score;
    int idx;
    Node* next;
    Node* before;
    bool operator<(Node b) const { 
        if (score < b.score)
        {
            return score < b.score;
        }
        else if ( score == b.score )
        {
            return idx < b.idx; 
        }
        return score < b.score; 
    }
    bool operator<=(Node b) const { return score <= b.score; }
    bool operator>(Node b) const { return score > b.score; }
    bool operator>=(Node b) const { return score >= b.score; }
    bool operator==(Node b) const { return score == b.score; }
    Node(int score, int idx): score(score), idx(idx) {}
};

class LinkedList {
    Node* head;
    Node* tail;
    int size;

    public:
    LinkedList() : head(new Node(0, 0)), tail(new Node(10000, 50000)), size(0)
    {
        head->next = tail;
        tail->before = head;
    }; 

    int getSize() {
        return size;
    }

    Node* popHead() {
        Node* h_next = head->next;
        h_next->next->before = h_next->before;
        h_next->before->next = h_next->next;
        h_next->before = nullptr;
        h_next->next = nullptr;
        return h_next;
    }
    Node* popTail() {
        Node* t_next = tail->before;

    }
    void insertInorder(Node* node) {
        Node* tmpHead = head;

        while (tmpHead->next != nullptr)
        {
            /* code */
        }
        
    }

};

class SplitedSortedLinkedList {
    LinkedList* left;
    LinkedList* right;

};

int main(){
    ios::sync_with_stdio(false), cin.tie(0);
    ifstream cin("codebattle0002.txt", ios_base::in);
    
    
}