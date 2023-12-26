#include <iostream>
#include <fstream>
#include <vector>
#include <map>
#include <queue>

using namespace std;



int main(){
    ios::sync_with_stdio(false), cin.tie(0), cin.tie(0);
    ifstream cin("codebattle16.txt", ios_base::in);    
    
    int testcase;
    cin >> testcase;
    int N;
    int A;
    int res;
    for (int tc = 1; tc <= testcase; tc++){
        
        map<int, int> tree;
        int size = 1;
        cin >> N >> A;
        res = 0;

        tree[A] = 1;
        for (int i = 0; i < N; i++)
        {
            int a, b;
            cin >> a >> b;
            if (tree.find(a) != tree.end()){tree[a] = 1;}
            else {tree[a]++;}
            if (tree.find(b) != tree.end()){tree[b] = 1;}
            else {tree[b]++;}
            size += 2;
            int index = 0;
            for (map<int, int>::iterator ptrTree = tree.begin(); ptrTree != tree.end(); ptrTree++)
            {
                index += ptrTree -> second;
                if (index > size / 2){
                    res += ptrTree -> first % 20171109;
                    break;
                }
            }
            res %= 20171109;
        }
        
        
        cout << '#' << tc << ' ' << res << '\n';
    }

}