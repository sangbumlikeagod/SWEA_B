#include <iostream>
#include <stdio.h>
#include <vector>
#include <string>
#include <fstream>
#include <cstring>
#include <algorithm>
using namespace std;

int array[100001];
int segmentTree[(2 << 17) + 1];

int segmentSearch(int start, int end, int idx)
{
    if (start == end){
        segmentTree[idx] = array[start];
        return segmentTree[idx];
    }
    int mid = (start + end) / 2;
    segmentTree[idx] = segmentSearch(start, mid, idx * 2) + segmentSearch(mid + 1, end, idx * 2 + 1);
    return segmentTree[idx];
}

void updateSegment(int start, int end, int idx, int what, int value)
{
    // start, end 는 이 함수의 범위가 얘한테 할당 되는지를 묻는 과정이다
    if (what < start || what > end) {
        return;
    }
    // 관련이 있다면 전부 더해줘야한다
    segmentTree[idx] += value;
    if (start == end)
    {
        return;
    }
    // 구역을 그냥 반으로 나눠서 구하면됨. 
    int mid = (start + end) / 2;
    updateSegment(start, mid, idx * 2, what , value);
    updateSegment(mid + 1, end, idx * 2 + 1, what , value);
}

int prefixSum(int start, int end, int idx, int left, int right)
{
    // prefixSum을 구하려다보면 구간에 벗어난 놈들을 찾을 수도 있음 그럴때 처리해주는것
    if (left > end || right < start)
    {
        return 0;
    }

    if (left <= start && right >= end)
    {
        return segmentTree[idx];   
    }
    int mid = (start + end) / 2;
    return prefixSum(start, mid, idx * 2, left, right) + prefixSum(mid + 1, end, idx * 2 + 1, left, right); 
}

pair<int, int> getMinMax(int start, int end, int left, int right)
{
    if (end < left || start > right)
    {
        return make_pair(9999999, 0);
    } 
    if (start == end)
    {
        cout << segmentTree[start] << '\n';
        return make_pair(segmentTree[start], segmentTree[start]);
    }
    int mid = (start + end) / 2;
    pair<int, int> leftBook = getMinMax(start, mid, left, right);
    pair<int, int> rightBook = getMinMax(mid + 1, end, left, right);

    return make_pair(
            min(leftBook.first, rightBook.first)
        ,   max(leftBook.second, rightBook.second)
    );
}

// 최대값과 최소값의 차를 구하여라?
// 범위사이에서 제일 큰값을 구하는것과 어떻게 관계가 있을까?

int main()
{
    ios::sync_with_stdio(false), cin.tie(0);
    ifstream cin("codebattle34.txt", ios_base::in);
    
    int tc;
    cin >> tc;
    for (int i = 0; i < tc; i++)
    {
        int n, q;
        cin >> n >> q;
        int startidx = 2;
        while (n > startidx)
        {
            startidx *= 2;
        }
        cout << "#" << i + 1 << ' ';
        // for (int size1Idx = startidx + 1; size1Idx <= startidx + n; size1Idx++)
        // {
        //     cin >> segmentTree[size1Idx]; 
        // }
        for (int arrIdx = 0; arrIdx < n; arrIdx++)
        {
            cin >> array[arrIdx];
        }
        
        segmentSearch(0, n - 1, 1);
        
        for (int i = 1; i <= startidx + n; i++)
        {
            cout << segmentTree[i] << ' ';
        }
        cout << '\n';
        for (int query = 0; query < q; query++)
        {
            int isUpdate;
            cin >> isUpdate;

            if (!isUpdate)
            {
                int updateIdx, updateValue;
                cin >> updateIdx >> updateValue;

                updateSegment(0, n - 1, 1, updateIdx, updateValue);
            }
            else 
            {
                int start, end;
                cin >> start >> end;
                pair<int, int> ret = getMinMax(0, n - 1, start, end);
                cout << ret.second - ret.first << ' ';
                // 큰놈 안에 큰놈있다고 말할 수는 없음 
            }
        }
        cout << '\n';
    }
}