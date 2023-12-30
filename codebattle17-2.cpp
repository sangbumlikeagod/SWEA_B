#include <iostream>
#include <vector>
#include <queue>
#include <map>
#include <unordered_map>
#include <string>
#include <cstring>
using namespace std;


int MAXLISTNUM[11][200000];
int arrayIndex = 1;

class ArrayNode{
public:
    int isRoot;
    int version;
    int parentversion;
    bool isDeep;
    unordered_map<int, pair<int, int>> NodeMap; 
    ArrayNode* parent;
    ArrayNode(int Root, bool Deep) : isRoot(Root), isDeep(Deep), parent(nullptr), version(1), parentversion(0){};
    ArrayNode(int Root, bool Deep, ArrayNode* parent, int parentversion) : isRoot(Root), isDeep(Deep), parent(parent), version(1), parentversion(parentversion){};
};
unordered_map<string, ArrayNode*> ArrayTree;

void init(){
    // 먼저 초기화를 해야될 것
    ArrayTree.clear();
    arrayIndex = 1;
    for (int i = 1; i < 11; i++){
        memset(MAXLISTNUM[i], 0, sizeof(MAXLISTNUM[i]));
    }
};
void makeList(char mName[20], int mLength, int mListValue[200000]){
    memcpy(MAXLISTNUM[arrayIndex], mListValue, mLength * sizeof(int));
    ArrayTree[mName] = new ArrayNode(arrayIndex++, false);
};

void copyList(char mDest[20], char mSrc[20], bool mCopy){
    ArrayNode* parentNode = ArrayTree[mSrc];
    if (mCopy)
    {
        ArrayTree[mDest] = new ArrayNode(0, mCopy, parentNode, parentNode->version);
    }
    else 
    {
        ArrayTree[mDest] = parentNode;
    }
};


void updateElement(char mName[20], int mIndex, int mValue){
    ArrayNode* currentNode = ArrayTree[mName];
    // 본인이 깊은복사면 무조건 update는 내맘대로임

    if (currentNode->isRoot)
    {
        currentNode->version++;
        currentNode->NodeMap[currentNode->version] = make_pair(mIndex, mValue);
    } 
    else if (currentNode->isDeep)
    {
        currentNode->version++;
        currentNode->NodeMap[currentNode->version] = make_pair(mIndex, mValue);
    }

};
     
int element(char mName[20], int mIndex){
    ArrayNode* currentNode = ArrayTree[mName];


    int versiontmp = currentNode->version;
    while (versiontmp > 1)
    {
        // if (currentNode->NodeMap.find(make_pair(versiontmp, mIndex)) != currentNode->NodeMap.end()){
        if (currentNode->NodeMap.find(versiontmp) != currentNode->NodeMap.end() && currentNode->NodeMap[versiontmp].first == mIndex){
            return currentNode->NodeMap[versiontmp].second;
        }     
        versiontmp--;
    }
    if (currentNode->isRoot){
        return MAXLISTNUM[currentNode->isRoot][mIndex];
    }

    while (currentNode->parent)
    {
        int versiontmp = currentNode->parentversion;
        while (versiontmp > 1)
        {
            if (currentNode->parent->NodeMap.find(versiontmp) != currentNode->parent->NodeMap.end() && currentNode->parent->NodeMap[versiontmp].first == mIndex){
                return currentNode->parent->NodeMap[versiontmp].second;
            }     
            versiontmp--;
        }
        if (currentNode->parent->isRoot){
            return MAXLISTNUM[currentNode->parent->isRoot][mIndex];
        }
        currentNode = currentNode->parent;
    }
};