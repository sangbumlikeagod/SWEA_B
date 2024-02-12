#include <unordered_map>
#include <vector>
#include <string>
#include <iostream>
using namespace std;
unordered_map<string, int> indexing;

class Union
{
public:
    int anti[625];
    int recruit;
    vector<int> child;

    Union(int c) : recruit(0), anti({0})
    {
        child.push_back(c);
    }
};

int maxN;
int Soilders[625] = {0};
int monarchUnion[625] = {0};
int dx[8] = {-1, -1, -1, 0, 0, 1, 1, 1};
int dy[8] = {-1, 0, 1, -1, 1, -1, 0, 1};

Union *unionList[625] = {};

void init(int N, int mSoldier[25][25], char mMonarch[25][25][11])
{
    indexing.clear();
    maxN = N;
    int initIndex = 0;
    for (int i = 0; i < N; i++)
    {
        for (int j = 0; j < N; j++)
        {
            Soilders[i * N + j] = mSoldier[i][j];
        }
    }

    for (int i = 0; i < N; i++)
    {
        for (int j = 0; j < N; j++)
        {
            indexing[mMonarch[i][j]] = initIndex++;
        }
    }
    for (int i = 0; i < N * N; i++)
    {
        monarchUnion[i] = i;
        unionList[i] = new Union(i);
    }
}

void destroy()
{
}

int ally(char mMonarchA[11], char mMonarchB[11])
{
    int indexA = indexing[mMonarchA];
    int indexB = indexing[mMonarchB];
    int unionA = monarchUnion[indexA];
    int unionB = monarchUnion[indexB];

    if (unionA == unionB)
    {
        return -1;
    }
    if (unionA > unionB)
    {
        swap(unionA, unionB);
    }
    if ((unionList[unionA]->anti)[unionB] = 1)
    {
        return -2;
    }
    Union *uA = unionList[unionA];
    Union *uB = unionList[unionB];
    int recruitAbs = uB->recruit - uA->recruit;
    for (int child : uB->child)
    {
        Soilders[child] += recruitAbs;
        monarchUnion[child] = unionA;
        (uA->child).push_back(child);
    }
    return 1;
}

int attack(char mMonarchA[11], char mMonarchB[11], char mGeneral[11])
{
    int indexA = indexing[mMonarchA];
    int indexB = indexing[mMonarchB];
    int unionA = monarchUnion[indexA];
    int unionB = monarchUnion[indexB];
    if (unionA == unionB)
    {
        return -1;
    }
    (unionList[unionA]->anti)[unionB] = 1;
    (unionList[unionB]->anti)[unionA] = 1;

    bool isThereEnemy = false;
    int x = indexA / maxN;
    int y = indexA % maxN;
    for (int i = 0; i < 8; i++)
    {
        int nx = x + dx[i];
        int ny = y + dy[i];
        if (0 <= nx && nx < maxN && 0 <= ny && ny < maxN)
        {
            if (monarchUnion[nx * maxN + ny] == unionA)
            {
                isThereEnemy = true;
                break;
            }
        }
    }
    if (!isThereEnemy)
    {
        return -2;
    }

    int offense = 0;
    int defense = unionList[unionB]->recruit + Soilders[indexB];
    for (int i = 0; i < 8; i++)
    {
        int nx = x + dx[i];
        int ny = y + dy[i];
        if (monarchUnion[nx * maxN + ny] == unionA)
        {
            int half = (Soilders[nx * maxN + ny] + unionList[unionA]->recruit) / 2;
            Soilders[nx * maxN + ny] -= half;
            offense += half;
        }
        else if (monarchUnion[nx * maxN + ny] == unionA)
        {
            int half = (Soilders[nx * maxN + ny] + unionList[unionB]->recruit) / 2;
            Soilders[nx * maxN + ny] -= half;
            defense += half;
        }
    }
    Union *uB;
    if (offense > defense)
    {
        indexing.erase(mMonarchB);
        indexing[mGeneral] = indexB;
        monarchUnion[indexB] = unionA;
        Soilders[indexB] = offense - defense - unionList[unionA]->recruit;
        (unionList[unionA]->child).push_back(indexB);
        for (int i = 0; i < (uB->child).size(); i++)
        {
            if ((uB->child)[i] == indexB)
            {
                (uB->child).erase((uB->child).begin() + i);
                break;
            }
        }
        return 1;
    }
    else
    {
        Soilders[indexB] = defense - offense - unionList[unionB]->recruit;
        return 0;
    }
}

int recruit(char mMonarch[11], int mNum, int mOption)
{
    int index = indexing[mMonarch];
    if (mOption)
    {
        int re = 0;
        Union *u = unionList[index];
        for (int child : u->child)
        {
            re += Soilders[child] + u->recruit;
        }
        return re;
    }
    else
    {
        Soilders[index] += mNum;
        return Soilders[index] + unionList[monarchUnion[index]]->recruit;
    }
}
