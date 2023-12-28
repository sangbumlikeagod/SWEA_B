#include <memory.h>
#include <string>
#include <unordered_map>

using namespace ::std;

const int MAX_MAKE_LIST = 10;
const int MAX_LENGTH = 200000;
const int MAX_ADDRESS = 6000;
const int MAX_CHANGE = 110000;

int initNumber;  // 만들어진 배열의 개수
int initValue[MAX_MAKE_LIST + 1][MAX_LENGTH + 1];  // 초기 배열 정보

int addressNumber;  // 존재하는 배열의 개수
unordered_map<string, int> address;  // key: 배열 이름, value: 원본 배열의 번호

int changeNumber;  // 변화 개수
pair<int, int> changeLog[MAX_CHANGE + 1];  // 모든 변화 기록을 담는 배열
    // makeList         : (-1, 원본 배열 번호)
    // copyList         : (-1, -1) 정보 추가하기. (deepcopy를 의미함)
    // updateElement    : (인덱스, 값) ; 인덱스의 값을 변경했다.

int lastChange[MAX_ADDRESS + 1]; // lastChange[i] := i번 원본 배열의 마지막 변화 event 번호
int prevChange[MAX_CHANGE + 1];  // prevChange[i] := i번 변화의 직전 변화 event 번호


void init()
{
    initNumber = 0;

    addressNumber = 0;
    address.clear();

    changeNumber = 0;
}

void makeList(char mName[], int mLength, int mListValue[])
{
    memcpy(initValue[initNumber], mListValue, mLength * sizeof(int));

    address[string(mName)] = addressNumber;
    addressNumber++;

    changeLog[changeNumber] = {-1, initNumber};
    prevChange[changeNumber] = -1;
    lastChange[address[string(mName)]] = changeNumber;
    changeNumber++;

    initNumber++;
}

void copyList(char mDest[], char mSrc[], bool mCopy)  // O(1)
{
    if (mCopy)
    {
        address[string(mDest)] = addressNumber;
        addressNumber++;

        changeLog[changeNumber] = {-1, -1};
        prevChange[changeNumber] = lastChange[address[string(mSrc)]];
        lastChange[address[string(mDest)]] = changeNumber;
        changeNumber++;
    }
    else
    {
        address[string(mDest)] = address[string(mSrc)];
    } 
}

void updateElement(char mName[], int mIndex, int mValue)  // O(1)
{
    changeLog[changeNumber] = {mIndex, mValue};
    prevChange[changeNumber] = lastChange[address[string(mName)]];
    lastChange[address[string(mName)]] = changeNumber;
    changeNumber++;
}

int element(char mName[], int mIndex)  // O(update 횟수)
{
    int c = lastChange[address[string(mName)]];
    while (true)
    {
        if (prevChange[c] == -1)  // 이전 변화가 없다면, 최초 makeList이다.
        {
            return initValue[changeLog[c].second][mIndex];
        }
        if (changeLog[c].first == mIndex)  // mIndex 가 직접 update 된 적이 있다.
        {
            return changeLog[c].second;
        }
        c = prevChange[c];
    }
    return 0;
} 