#include <iostream>
#include <algorithm>

using namespace std;
struct Node
{
    int id;
    int val;
    Node *next;
    Node *before;
    bool operator<(Node b) const { return val < b.val; }
    bool operator<=(Node b) const { return val <= b.val; }
    bool operator>(Node b) const { return val > b.val; }
    bool operator>=(Node b) const { return val >= b.val; }
    bool operator==(Node b) const { return val == b.val; }
    Node(int id, int val) : id(id), val(val), next(nullptr), before(nullptr) {}
};

class LinkedList
{
    Node *Head;
    Node *Tail;

public:
    int length;
    LinkedList() : Head(new Node(0, 0)), Tail(new Node(0, 10001)), length(0)
    {
        Head->next = Tail;
        Tail->before = Head;
    }
    void insertHead(Node *node)
    {
        if (!length)
        {
            node->next = Tail;
            node->before = Head;
            Head->next = node;
            Tail->before = node;
            length++;
            return;
        }
        node->next = Head->next;
        node->before = Head;
        node->next->before = node;
        Head->next = node;
        length++;
    }
    Node *popHead()
    {
        Node *tmp = Head->next;
        cout << tmp->val << '\t';
        Head->next = Head->next->next;
        tmp->before = nullptr;
        tmp->next = nullptr;
        length--;
        cout << tmp->val << '\t';
        return tmp;
    }

    void insertTail(Node *node)
    {
        if (!length)
        {
            node->next = Tail;
            node->before = Head;
            Head->next = node;
            Tail->before = node;
            length++;
            return;
        }

        node->before = Tail->before;
        node->next = Tail;
        node->before->next = node;
        Tail->before = node;
        length++;
    }
    Node *popTail()
    {
        Node *tmp = Tail->before;
        Tail->before = tmp->before;
        Tail->before->next = Tail;
        tmp->before = nullptr;
        tmp->next = nullptr;
        length--;
        return tmp;
    }
    void insertSomeWhere(Node *node)
    {
        Node *Htmp = Head;
        Node *Ttmp = Tail;

        while (Htmp < Ttmp)
        {
            if ((*Htmp) < (*node) && (*node) < (*Htmp->next))
            {
                node->before = Htmp;
                node->next = Htmp->next;

                node->before->next = node;
                node->next->before = node;
                return;
            }
            if ((*Ttmp->before) < (*node) && (*node) < (*Ttmp))
            {
                node->before = Ttmp->before;
                node->next = Ttmp;
                node->before->next = node;
                node->next->before = node;
                return;
            }
            Htmp = Htmp->next;
            Ttmp = Ttmp->before;
        }
    }
    int maxVal()
    {
        return Tail->before->val;
    }
    int minVal()
    {
        return Head->next->val;
    }
};

class League
{
    LinkedList *left;
    LinkedList *right;

public:
    League() : left(new LinkedList()), right(new LinkedList())
    {
    }
    void balancing()
    {
        if (left->length == right->length + 1)
        {
            left->insertTail(right->popHead());
        }
        else if (left->length + 2 == right->length)
        {
            right->insertHead(left->popTail());
        }
    };
    void insertLeft(Node *node)
    {
        left->insertTail(node);
    }
    void insertRight(Node *node)
    {
        right->insertTail(node);
    }
    Node *popLeftHead()
    {
        Node *tmp = left->popHead();
        // this->balancing();
        return tmp;
    }
    Node *popRightTail()
    {
        Node *tmp = right->popTail();
        this->balancing();
        return tmp;
    }
    Node *popRightHead()
    {
        Node *tmp = right->popHead();
        this->balancing();
        return tmp;
    }
    void insertPlayer(Node *node)
    {
        if (left->maxVal() < node->val)
        {
            left->insertSomeWhere(node);
        }
        else
        {
            right->insertSomeWhere(node);
        }
        this->balancing();
    }
    int size()
    {
        return left->length + right->length;
    }
};

League *totalSeason[4000] = {};
int Teams = 0;

void init(int N, int L, int mAbility[])
{
    for (int i = 0; i < 4000; i++)
    {
        totalSeason[i] = new League();
    }

    Teams = L;
    Node *PlayerList[40000] = {};
    const int PlayerperLeague = N / L;

    for (int i = 0; i < L; i++)
    {
        for (int j = PlayerperLeague * i; j < PlayerperLeague * (i + 1); j++)
        {
            PlayerList[j] = new Node(j, mAbility[j]);
        }

        sort(PlayerList + (PlayerperLeague * i), PlayerList + (PlayerperLeague * (i + 1)), [](const Node *a, const Node *b)
             { return a->val < b->val; });

        // for (int k = 0; k < (PlayerperLeague * (i + 1)); k++)
        // {
        //     cout << PlayerList[k]->id << ' ' << PlayerList[k]->val << '\t';
        // }
        // cout << '\n';

        for (int j = PlayerperLeague * i; j < PlayerperLeague * (i + 1); j++)
        {
            if (j < PlayerperLeague / 2)
            {
                totalSeason[i]->insertLeft(PlayerList[j]);
            }
            else
            {
                totalSeason[i]->insertRight(PlayerList[j]);
            }
        }
    }
    return;
}

int move()
{
    int ans = 0;
    Node *leftReceive[4000];
    Node *rightReceive[4000];
    leftReceive[Teams - 1] = nullptr;
    rightReceive[0] = nullptr;
    for (int i = 0; i < Teams; i++)
    {
        if (i != 0)
        {
            leftReceive[i - 1] = totalSeason[i]->popLeftHead();
            ans += leftReceive[i - 1]->id;
        }
        if (i != Teams - 1)
        {
            rightReceive[i + 1] = totalSeason[i]->popRightTail();
            ans += rightReceive[i + 1]->id;
        }
    }
    for (int i = 0; i < Teams; i++)
    {
        if (leftReceive[i])
        {
            totalSeason[i]->insertPlayer(leftReceive[i]);
        }
        if (rightReceive[i])
        {
            totalSeason[i]->insertPlayer(rightReceive[i]);
        }
    }

    return ans;
}

int trade()
{
    int ans = 0;
    Node *receiveMiddle[4000];
    Node *receiveBest[4000];
    receiveBest[Teams - 1] = nullptr;
    receiveMiddle[0] = nullptr;
    for (int i = 0; i < Teams; i++)
    {
        if (i != 0)
        {
            receiveBest[i - 1] = totalSeason[i]->popRightTail();
            ans += receiveBest[i - 1]->id;
        }
        if (i != Teams - 1)
        {
            receiveMiddle[i + 1] = totalSeason[i]->popRightHead();
            ans += receiveMiddle[i + 1]->id;
        }
    }
    for (int i = 0; i < Teams; i++)
    {
        if (receiveBest[i])
        {
            totalSeason[i]->insertPlayer(receiveBest[i]);
        }
        if (receiveMiddle[i])
        {
            totalSeason[i]->insertPlayer(receiveMiddle[i]);
        }
    }
    return ans;
}

int main()
{
    for (int i = 0; i < 1; i++)
    {
        int mAbility[] = {1, 5, 6, 8, 7, 3, 2, 1, 4, 5, 9, 8, 7, 6, 1};
        init(15, 3, mAbility);
        // cout << move();

        for (int i = 0; i < 3; i++)
        {
            cout << totalSeason[i]->size() << '\t' << totalSeason[i]->popLeftHead()->val << '\t';
            cout << '\n';
        }

        // cout << move() << '\n';
    }
}