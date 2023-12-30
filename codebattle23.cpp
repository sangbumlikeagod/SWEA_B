#include <iostream>
#include <fstream>
#include <vector>
#include <queue>
#include <unordered_map>
#include <algorithm>
#include <string>
#include <map>

using namespace std;

int JOKERNUM;
int LEFTMOST = 0;
int RIGHTMOST = 0;
unordered_map<int, int>DEQUE;
map<int, int> calculationStore[5][20];
int fortest[4];

void init(int mJoker, int mNumbers[5]){
    LEFTMOST = 0;
    RIGHTMOST = 0;
    DEQUE.clear();
    JOKERNUM = mJoker;
    for (int i = 0; i < 5; i++)
    {
        for (int j = 0; j < 20; j++)
        {
            calculationStore[i][j].clear();
        }
    }
    int isJoker = 0;
    int tmpSum = 0;
    for (int i = 0; i < 4; i++)
    {
        if (mNumbers[i] == -1){
            isJoker++;
        }
        else{
            tmpSum += mNumbers[i];
        }
    }
    for (int k = 0; k < 5; k++)
    {
        DEQUE[LEFTMOST * 5 + k] = mNumbers[k];
        if (!k)
        {
            calculationStore[isJoker][tmpSum % 20][0] = 1;
        }
        if (k == 1){
            if (mNumbers[0] == -1)
            {
                isJoker--;
            }
            else {
                tmpSum -= mNumbers[0];
            }
            if (mNumbers[4] == -1)
            {
                isJoker++;
            }
            else{
                tmpSum += mNumbers[4];
            }
            calculationStore[isJoker][tmpSum % 20][1] = 1;
        }
        
    }

    
};


void putCards(int mDir, int mNumbers[5]){
    if(mDir)
    {
        RIGHTMOST++;
        int tmpSum = DEQUE[RIGHTMOST * 5 - 4] + DEQUE[RIGHTMOST * 5 - 3] + DEQUE[RIGHTMOST * 5 - 2] + DEQUE[RIGHTMOST * 5 - 1];
        int isJoker = (DEQUE[RIGHTMOST * 5 - 4] == -1) + (DEQUE[RIGHTMOST * 5 - 3] == -1) + (DEQUE[RIGHTMOST * 5 - 2] == -1) + (DEQUE[RIGHTMOST * 5 - 1] == -1);
        tmpSum += isJoker;
        for (int i = 0; i < 5; i++)
        {
            DEQUE[RIGHTMOST * 5 + i] = mNumbers[i];
            if (DEQUE[RIGHTMOST * 5 + i - 4] == -1)
            {
                isJoker--;
            }
            else{
                tmpSum -= DEQUE[RIGHTMOST * 5 + i - 4];
            }
            if (mNumbers[i] == -1)
            {
                isJoker++;
            }
            else
            {
                tmpSum += mNumbers[i];
            }
            calculationStore[isJoker][tmpSum % 20][RIGHTMOST * 5 + i - 3] = 1;
        }
    }
    else
    {
        LEFTMOST--;
        int tmpSum = mNumbers[0] + mNumbers[1] + mNumbers[2] + mNumbers[3];
        int isJoker = (mNumbers[0] == -1) + (mNumbers[1] == -1) + (mNumbers[2] == -1) + (mNumbers[3] == -1);
        int rightend = 1;
        tmpSum += isJoker;

        for (int i = 0; i < 5; i++)
        {
            DEQUE[LEFTMOST * 5 + i] = mNumbers[i];
            calculationStore[isJoker][tmpSum % 20][LEFTMOST * 5 + i] = 1;
            if (mNumbers[i] == -1)
            {
                isJoker--;
            }
            else
            {
                tmpSum -= mNumbers[i];
            }

            if (!i) {
                rightend = mNumbers[4];
            } else {
                rightend = DEQUE[LEFTMOST * 5 + i + 4];
            }
            if (rightend == -1)
            {
                isJoker++;
            }
            else {
                tmpSum += rightend;
            }
            
        }
        
    }
};


int findNumber(int mNum, int mNth, int ret[4]){
    map<int, int>::iterator container[5];
    map<int, int>::iterator end_container[5];
    int size = 0;
    
    for (int i = 0; i < 5; i++)
    {   
        int addNum = (i * JOKERNUM) % 20;

        if (mNum + 20 - addNum <= 19){

            container[i] = calculationStore[i][mNum + 20 - addNum].begin();
            end_container[i] = calculationStore[i][mNum + 20 - addNum].end();
            size += calculationStore[i][mNum + 20 - addNum].size();
        }
        else {

            container[i] = calculationStore[i][mNum - addNum].begin();
            end_container[i] = calculationStore[i][mNum - addNum].end();
            size += calculationStore[i][mNum - addNum].size();
        }
    }

    if (size < mNth){
        return 0;
    }

    int ans = 0;

    for (int i = 0; i < mNth; i++)
    {
        int tmpAns = 60000;
        int tmpidx = -1;
        for (int j = 0; j < 5; j++)
        {
            if ((container[j] != end_container[j]) && container[j] -> first < tmpAns)
            {   
                tmpAns = container[j] -> first;
                tmpidx = j;
            }
        }
        ans = tmpAns;
        container[tmpidx]++;
    }

    for (int z = 0; z < 4; z++)
    {
        ret[z] = DEQUE[ans + z];
    }

    
    return 1;
};


void changeJoker(int mValue){
    JOKERNUM = mValue;
};

int main(){
    ios::sync_with_stdio(false), cin.tie(0), cin.tie(0);
    ifstream cin("codebattle23.txt", ios_base::in);    
    int testcase = 0;
    int C = 0;
    cin >> testcase >> C;

    int N;
    int res;
    for (int tc = 1; tc <= testcase; tc++){
        cin >> N;
        cout << N <<'\n';
        for(int i = 0; i < N; i++){
            int command;
            cin >> command;
            if (command == 400)
            {
                int val;
                cin >> val;
                changeJoker(val);
            }
            else if(command == 100 || command == 200)
            {
                int pre;
                int inp[5];
                cin >> pre >> inp[0] >> inp[1] >> inp[2] >> inp[3] >> inp[4];
                if (command == 100)
                {
                    init(pre, inp);
                }
                else{
                    putCards(pre, inp);
                }   
            }
            else {
                int mNum;
                int mNth;
                int result_ans;
                int ret[4];
                int result_ret[4];
                cin >> mNum >> mNth >> result_ans;
                if (result_ans)
                {cin >> result_ret[0] >> result_ret[1] >> result_ret[2] >> result_ret[3];}
                int ans = findNumber(mNum, mNth, ret);
                if (result_ans != ans){
                     cout << mNum << '\t' << mNth << '\n';
                }
                if (result_ans && ans != result_ans){
                    cout << mNum << '\t' << mNth << '\n';
                    for (int i = 0; i < 4; i++)
                    {
                        cout << ret[i] << ' ' << result_ret[i] << '\t';
                    }
                    cout << '\n';
                };

            }
        }

    }


}
