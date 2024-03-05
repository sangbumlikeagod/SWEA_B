#ifndef _CRT_SECURE_NO_WARNINGS
#define _CRT_SECURE_NO_WARNINGS
#endif

#include <stdio.h>
#include <cstring>
#include <iostream>
#include <string>
#define CMD_INIT 100
#define CMD_INSERT 200
#define CMD_MOVECURSOR 300
#define CMD_COUNT 400

extern void init(int H, int W, char mStr[]);
extern void insert(char mChar);
extern char moveCursor(int mRow, int mCol);
extern int countCharacter(char mChar);

/////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////
using namespace std;
struct node
{
    char val;
    node *before;
    node *next;
    node(char v) : val(v), before(nullptr), next(nullptr){};
};

int mH;
int mW;


class LinkedList
{
private:
    int index;
    int counts[26];
    int size;
    node *head;
    node *tail;

public:
    LinkedList(int idx) : index(idx), counts(), size(0), head(new node(' ')), tail(new node(' '))
    {
        head->next = tail;
        tail->before = head;
        for (int i = 0; i < 26; i++)
        {
            counts[i] = 0;
        }
    };
    void insertHead(node *newbie)
    {
        size++;
        counts[newbie->val - 'a']++;
        head->next->before = newbie;
        newbie->next = head->next;
        newbie->before = head;
        head->next = newbie;

        // if (size == mW + 1)
        // {
        //     node *tmp = this->popTail();
        //     counts[tmp->val - 'a']--;
        //     size--;
        //     memo[index + 1]->insertHead(tmp);
        // }
    };
    void insertTail(node *newbie)
    {
        size++;
        counts[newbie->val - 'a']++;
        tail->before->next = newbie;
        newbie->before = tail->before;
        newbie->next = tail;
        tail->before = newbie;

        // if (size == mW + 1)
        // {
        //     node *tmp = this->popTail();
        //     counts[tmp->val - 'a']--;
        //     size--;
        //     memo[index + 1]->insertHead(tmp);
        // }
    };
    void addCall(char c)
    {
        size++;
        counts[c - 'a']++;

        // if (size == mW + 1)
        // {
        //     node *tmp = this->popTail();
        //     counts[tmp->val - 'a']--;
        //     size--;
        //     memo[index + 1]->insertHead(tmp);
        // }
    }
    node* popTail()
    {
        size--;
        node *re = tail->before;
        // cout << re->val << '\n';
        tail->before = tail->before->before;
        tail->before->next = tail;
        re->before = nullptr;
        re->next = nullptr;
        counts[re->val - 'a']--;
        return re;
    };

    // void debug()
    // {
    //     node *tmp = head->next;
    //     while (tmp != tail)
    //     {
    //         cout << tmp->val << ' ';
    //         tmp = tmp->next;
    //     }
    //     cout << '\n';
    // };
    node *getIthNode(int y)
    {
        node *tmp = head;
        for (int i = 0; i < y; i++)
        {
            tmp = tmp->next;
        }
        return tmp;
    };
    int getCount(char c)
    {
        return counts[c - 'a'];
    };
    int getSize()
    {
        return size;
    }
    bool getIsExceed()
    {
        return size > mW;
    }
};

LinkedList *memo[301];



struct cursor
{
    int x;
    int y;
    node *pointer;
    cursor(int x, int y) : x(x), y(y), pointer(nullptr)
    {
        pointer = memo[x]->getIthNode(y);
    }
};
cursor *cur;
void init(int H, int W, char mStr[])
{
    // x와 y다
    mH = H;
    mW = W;
    string Sk = mStr;
    // cout << Sk;
    for (int i = 1; i <= mH; i++)
    {
        memo[i] = new LinkedList(i);
    }
    int mS = Sk.length();
    // cout << mS << '\n'; 
    int s = 0;
    while (s < mS)
    {
        int inserti = 0;
        if (s + mW < mS)
        {
            inserti = mW;
        }
        else
        {
            inserti = mS - s;
        }

        for (int j = 0; j < inserti; j++)
        {
            memo[s / mW + 1]->insertTail(new node(Sk[s + j]));
        }
        s += inserti;
        // cout << s << '\t';
    }
    // int k = 1;
    // while (memo[k]->getSize())
    // {
    //     memo[k]->debug();
    //     k++;
    // }
    
    cur = new cursor(1, 1);
    // memo[1]->debug();
    // memo[2]->debug();
    // cout << '\n';
    // cout << cur->pointer->val;

    // cout << '\n' << '\n';

}

void insert(char mChar)
{
    // cout << "insert" << '(' << cur->x << ' ' << cur->y << ')' << '\n';

    cur->y++;
    node *newbie = new node(mChar);
    cur->pointer->before->next = newbie;
    newbie->before = cur->pointer->before;
    newbie->next = cur->pointer;
    cur->pointer->before = newbie;
    memo[cur->x]->addCall(mChar);

    int mayBeExceed = cur->x;
    while (memo[mayBeExceed]->getIsExceed())
    {
        // cout << '\t' << '\t' <<mayBeExceed << cur->y << '\t';
        // memo[mayBeExceed]->debug();
        node* tmp = memo[mayBeExceed]->popTail();
        memo[mayBeExceed + 1]->insertHead(tmp);
        // cout << '\t' << '\t';
        // memo[mayBeExceed]->debug();
        mayBeExceed++;
    }
    // cout << '\t';
    // memo[cur->x]->debug();
    // cout << '\n';
    if (cur->y > mW)
    {
        cur->x++;
        cur->y = 1;
        moveCursor(cur->x, cur->y);
    }
}

char moveCursor(int mRow, int mCol)
{
    // cout << "moveCursor" << '(' << cur->x << ' ' << cur->y << ')' << '\n';

    if (memo[mRow]->getSize() < mCol)
    {
        while (memo[mRow]->getSize() == 0)
        {
            mRow--;
        }
        cur->x = mRow;
        cur->y = memo[mRow]->getSize() + 1;
        cur->pointer = memo[mRow]->getIthNode(cur->y);
        // cout << '(' << cur->x << ' ' << cur->y << ')' << '\n';

        // cout << '$' << '\n';
        return '$';
    }
    else
    {
        cur->x = mRow;
        cur->y = mCol;
        cur->pointer = memo[mRow]->getIthNode(cur->y);
        // cout << '(' << cur->x << ' ' << cur->y << ')' << '\n';

        // cout << cur->pointer->val << '\n';
        return cur->pointer->val;
    }
}

int countCharacter(char mChar)
{
    // cout << "countCharacter" << '(' << cur->x << ' ' << cur->y << ')' << '\n';
    int ans = 0;
    node *tmp = cur->pointer;
    // cout << tmp->val;
    while (tmp->next != nullptr)
    {
        if (tmp->val == mChar)
        {
            ans++;
        }
        tmp = tmp->next;
    }
    int iX = cur->x + 1;
    while (iX <= mH && memo[iX]->getSize())
    {
        // cout << iX << '\n';
        ans += memo[iX]->getCount(mChar);
        iX++;
    }
    // cout << '\t' << ans << '\n';
    
    return ans;
}

static bool run()
{
    bool correct = false;
    int queryCnt;
    scanf("%d", &queryCnt);
    int H, W;
    char mChar;
    static char mStr[90001];

    while (queryCnt--)
    {
        int cmd;
        scanf("%d", &cmd);

        if (cmd == CMD_INIT)
        {
            scanf("%d %d %s", &H, &W, mStr);
            init(H, W, mStr);
            correct = true;
        }
        else if (cmd == CMD_INSERT)
        {
            scanf(" %c", &mChar);
            insert(mChar);
        }
        else if (cmd == CMD_MOVECURSOR)
        {
            int mRow, mCol;
            scanf("%d %d", &mRow, &mCol);

            char ret = moveCursor(mRow, mCol);

            char ans;
            scanf(" %c", &ans);
            if (ret != ans)
            {
                // cout << ans << '\t' << ret << '\n';
                correct = false;
            }
        }
        else if (cmd == CMD_COUNT)
        {
            scanf(" %c", &mChar);

            int ret = countCharacter(mChar);

            int ans;
            scanf("%d", &ans);
            if (ret != ans)
            {
                correct = false;
            }
        }
    }
    return correct;
}

int main()
{
    setbuf(stdout, NULL);
    freopen("sample_input.txt", "r", stdin);

    int T, MARK;
    scanf("%d %d", &T, &MARK);

    for (int tc = 1; tc <= T; tc++)
    {
        int score = run() ? MARK : 0;
        printf("#%d %d\n", tc, score);
    }
    return 0;
}