#include <iostream>
#include <fstream>
#include <vector>
#include <queue>
#include <map>
#include <string>
using namespace std;


int MAXLISTNUM[11][200000];
int arrayIndex = 1;

class ArrayNode{
public:
    int isRoot;
    int version;
    int parentversion;
    bool isDeep;
    map<pair<int, int>, int> NodeMap; 
    ArrayNode* parent;
    ArrayNode(int Root, bool Deep) : isRoot(Root), isDeep(Deep), parent(nullptr), version(1), parentversion(0){};
    ArrayNode(int Root, bool Deep, ArrayNode* parent, int parentversion) : isRoot(Root), isDeep(Deep), parent(parent), version(1), parentversion(parentversion){};
    void debug(){
        cout << isRoot << '\n';
        cout << isDeep << '\n';
        cout << NodeMap.size() << '\n';
        cout << parent << '\n';
        cout << version << '\t' << parentversion << '\n';
    }
};
map<string, ArrayNode*> ArrayTree;

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
    if (!(parentNode->isDeep || parentNode->isRoot)){
        parentNode = parentNode->parent;
    }
    ArrayTree[mDest] = new ArrayNode(0, mCopy, parentNode, parentNode->version);
};

void updateElement(char mName[20], int mIndex, int mValue){
    ArrayNode* currentNode = ArrayTree[mName];
    // 본인이 깊은복사면 무조건 update는 내맘대로임
    if (!(currentNode->isDeep || currentNode->isRoot)){
        currentNode->parentversion++;
        currentNode = currentNode->parent;      
    }
    if (currentNode->isRoot)
    {
        currentNode->NodeMap[make_pair(currentNode->version, mIndex)] = MAXLISTNUM[currentNode->isRoot][mIndex];
        currentNode->version++;
        MAXLISTNUM[currentNode->isRoot][mIndex] = mValue;
    } 
    else if (currentNode->isDeep)
    {
        currentNode->version++;
        currentNode->NodeMap[make_pair(currentNode->version, mIndex)] = mValue;
    }

};
     
int element(char mName[20], int mIndex){
    ArrayNode* currentNode = ArrayTree[mName];

    if (!(currentNode->parent))
    {
        return MAXLISTNUM[currentNode->isRoot][mIndex];
    }
    if (!(currentNode->isDeep || currentNode->isRoot)){
        currentNode = currentNode->parent; 
        if (currentNode->isRoot) {return MAXLISTNUM[currentNode->isRoot][mIndex];}
        int versiontmp = currentNode->version;
        while (versiontmp > 1)
        {
            if (currentNode->NodeMap.find(make_pair(versiontmp, mIndex)) != currentNode->NodeMap.end()){
                return currentNode->NodeMap[make_pair(versiontmp, mIndex)];
            }     
            versiontmp--;
        }
        
    }

    while (!(currentNode->parent->isRoot))
    {
        int versiontmp = currentNode->parentversion;
        while (versiontmp > 1)
        {
            if (currentNode->parent->NodeMap.find(make_pair(versiontmp, mIndex)) != currentNode->parent->NodeMap.end()){
                return currentNode->parent->NodeMap[make_pair(versiontmp, mIndex)];
            }     
            versiontmp--;
        }
        currentNode = currentNode->parent;
    }

    int versiontmp = currentNode->parentversion;
    while (versiontmp >= 1)
    {
        if (currentNode->parent->NodeMap.find(make_pair(versiontmp, mIndex)) != currentNode->parent->NodeMap.end()){
            return currentNode->parent->NodeMap[make_pair(versiontmp, mIndex)];
        }     
        versiontmp--;
    }

    if (currentNode->parent->NodeMap.find(make_pair(currentNode->parentversion, mIndex)) != currentNode->parent->NodeMap.end())
    {
        return currentNode->parent->NodeMap[make_pair(currentNode->parentversion, mIndex)];
    }

    
    else 
    {
        return MAXLISTNUM[currentNode->parent->isRoot][mIndex];
    }
};

int main(){
    ios::sync_with_stdio(false), cin.tie(0), cin.tie(0);
    ifstream cin("codebattle17.txt", ios_base::in);    
    
    // int testcase;
    // cin >> testcase;
    // int N;
    // int res;
    // for (int tc = 1; tc <= testcase; tc++){
    //     cin >> N;
    //     res = 1;
    //     cout << '#' << tc << ' ' << N * (res - 1) << '\n';
    // }
    	
    init();
    int py[5] = {24524, 24580, 6350, 19398, 15849};
    char s1[2] = "a";
    makeList(s1, 5, py);
    ArrayTree[s1]->debug();

    cout << element(s1, 4) << '\n';
    char s2[2] = "b";
    copyList(s2, s1, false);
    updateElement(s2, 1, 23);
    cout << element(s1, 1) << '\n';
    char s3[2] = "c";
    copyList(s3, s2, true);
    updateElement(s3, 3, 12345);
    cout << element(s1, 3) << '\n';
    updateElement(s1, 0, 99);
    cout << element(s3, 0) << '\n';
    cout << element(s3, 1) << '\n' << '\n';
    ArrayTree[s1]->debug();
    ArrayTree[s3]->debug();
}