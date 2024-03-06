#define MAX_N 50000
#define MAX_M 50000
#define MAX_LEN 11
#include <iostream>
#include <string>
#include <map>
#include <queue>
#include <vector>
#include <algorithm>
#include <unordered_map>
using namespace std;


struct words {
	string str;
	int count;
	words(string s) : str(s), count(0) {
		int i = 0;
		int j = str.length() - 1;
		bool ispalindrom = true;
		while (i < j)
		{
			if (s[i++] != s[j--])
			{
				count = 1;
				break;
			}
		}

	};
	bool operator<(words &other) {
		
		int s1 = str.length();
		int s2 = other.str.length();
		int p = 0;
		while (p < s1 && p < s2)
		{
			if (str[p] != other.str[p])
			{
				return str[p] < other.str[p];
			}
			p++;
		}
		return s1 < s2;
	}
};

struct CompareWords {
	bool operator()(const words* a, const words* b)
	{
		int s1 = a->str.length();
		int s2 = b->str.length();
		int p = 0;

		while (p < s1 && p < s2)
		{
			if (a->str[p] != b->str[p])
			{
				return a->str[p] > b->str[p];
			}
			p++;
		}
		return s1 > s2;
	}
};

struct node {
	int val;
	node* next;
	node* before;
	node(int n) : val(n), next(nullptr), before(nullptr){};
};

class CircularLinkedList {
	int size;
public:
	node* forCheck[50001];

	CircularLinkedList(int n) : size(n), forCheck() {
		//for (int i = 1; i <= size; i++)
		//{
		//	forCheck[i] = nullptr;
		//}
		//cout << size << '\n';
		for (int i = 1; i <= size; i++)
		{
 			forCheck[i] = new node(i);
			//cout << forCheck[i]->val;
			if (i != 1) {
				forCheck[i - 1]->next = forCheck[i];
				forCheck[i]->before = forCheck[i - 1];
			}
		}
		forCheck[size]->next = forCheck[1];
		forCheck[1]->before = forCheck[size];
	};
	int nextUser(int n)
	{
		return forCheck[n]->next->val;
	}
	void popUser(int n)
	{
		forCheck[n]->before->next = forCheck[n]->next;
		forCheck[n]->next->before = forCheck[n]->before;
	}
	void debug(int n)
	{
		node* head = forCheck[n];
		int headVal = head->val;
		while (true)
		{
			//cout << head->val <<'\t';
			head = head->next;
			if (head->val == headVal)
			{
				cout << '\n';
				break;
			}
		}
	}
};

vector<priority_queue<words*, vector<words*>, CompareWords>*> que(26);
CircularLinkedList iclist = CircularLinkedList(1);
unordered_map<string, int> check;
//map<words*, int> games;

//void debug(map<words*, int>& game)
//{
//	for (map<words*, int>::iterator i = game.begin(); i != game.end(); i++)
//	{
//		cout << i->first->str << '\t';
//	}
//	cout << '\n';
//}

void debug()
{
	for (int i = 0; i < 26; i++)
	{
		if (que[i]->empty()) {
			cout << '0' << '\t';
			continue;
		}
		cout << que[i]->top()->str << '\t';
	}
	cout << '\n';
}

void init(int N, int M, char mWords[][MAX_LEN])
{
	//games.clear();
	check.clear();
	iclist = CircularLinkedList(N);
	for (int i = 0; i < 26; i++)
	{
		que[i] = new priority_queue<words*, vector<words*>, CompareWords>;
	}


	for (int i = 0; i < M; i++)
	{
		string s = mWords[i];
		//cout << s << ' ' << s.length() << '\n';
		check[s] = 1;
		que[s[0] - 'a']->push(new words(s));
	}
}

int playRound(int mID, char mCh)
{
	// 

	vector<words*> tmp{};
	while (!que[mCh - 'a']->empty())
	{
		string s = que[mCh - 'a']->top()->str;
		check[s] = 1;
		tmp.push_back(que[mCh - 'a']->top());
		//cout << s << '\t' << '\t';
		que[mCh - 'a']->pop();
		mCh = s[s.length() - 1];
		mID = iclist.nextUser(mID);
	}
	
	for (int i = 0; i < tmp.size(); i++)
	{
		if (tmp[i]->count)
		{
			string s;
			for (int j = (tmp[i]->str).length() - 1; j >= 0; j--)
			{
				s += (tmp[i]->str)[j];
			}
			if (check.find(s) != check.end()) continue;
			//cout << s << s.length() << '\t';
			words* newword = new words(s);
			//newword->count--;
			que[s[0] - 'a']->push(newword);
		}
	}
	//cout << '\n';
	iclist.popUser(mID);

	return mID;
}