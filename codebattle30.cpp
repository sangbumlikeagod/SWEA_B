#include <iostream>
#include <fstream>
#include <vector>
#include <string>
#include <map>
#include <queue>
using namespace std;



class Trie{
public:
    char alphabet;
    int cnt;
    bool isWordComplete;
    map<char, Trie> subTrie;
    Trie() : alphabet('\0'), cnt(0), isWordComplete(false){
        // subTrie = 
        // 이런 자료구조안에 다른 자료구조는 어떻게 처리하지 
    };
    Trie(char c) : alphabet(c), cnt(1), isWordComplete(false){};
    void putData(string s)
    {
        cnt++;
        if (!s.size()){
            return;
        }
        if (subTrie.find(s[0]) == subTrie.end())
        // 없다
        {
            subTrie[s[0]] = Trie(s[0]);
            if (s.size() != 1)
            {
                subTrie[s[0]].putData(s.substr(1, s.size() - 1));
            }

        }
        else 
        {
            subTrie[s[0]].putData(s.substr(1, s.size() - 1));
        }};
};

string dfs(Trie trie, int k){
    
};

int main(){
    ios::sync_with_stdio(false), cin.tie(0), cin.tie(0);
    ifstream cin("codebattle30.txt", ios_base::in);    
    
    int testcase;
    cin >> testcase;
    string N;
    int k;
    for (int tc = 1; tc <= testcase; tc++){
        cin >> k;
        cin >> N;
        
        Trie root;
        for (int i = 0; i < N.size(); i++){ 
            root.putData(N.substr(i, N.size() - i));
        }
        // cout << '#' << tc << ' ' << N * (res - 1) << '\n';
    }

}