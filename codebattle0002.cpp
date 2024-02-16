#include <iostream>
#include <algorithm>

struct Node{
    int id;
    int val;
    Node* next;
    Node* before;
    bool operator()(Node a, Node b) const { return a.val < b.val; }
    Node(int id, int val) : id(id), val(val), next(nullptr), before(nullptr) {} 
};

class LinkedList
{   
    Node* Head;
    Node* Tail;
    public:
    int length;
    LinkedList() : Head(new Node(0, 0)), Tail(new Node(0, 10001)), length(0){
        Head->next = Tail;
    }
    void 

};



class League
{
    LinkedList left;
    LinkedList right;

    public:
    void balancing()
    {
        if (left.length < right.length)
        {

        }
    };
};

void init(int N, int L, int mAbility[])
{
    
}


int move()
{

}


int trade()
{

}