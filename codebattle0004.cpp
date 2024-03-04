#define CMD_INIT 100
#define CMD_ADD 200
#define CMD_REMOVE 300
#define CMD_QUERY 400
#include <iostream>
#include <stdio.h>
#include <vector>
#include <string>
#include <map>
#include <deque>
#include <fstream>
#include <cstring>
using namespace std;

map<int , deque<int>> students[6];
map<int, pair<int, int>> idContainer;

void insertDeque(deque<int> & dq, int id)
{
	if (id < dq.front())
	{
		dq.push_front(id);
		return;
	}
	deque<int>::iterator front = dq.begin();
	deque<int>::iterator back = dq.end();
	int count = 0;
	while (front != back)
	{
		if (id < (*front)) 
		{
			dq.emplace(front - 1, id);
			return;
		}
		else 
		{
			front++;
		}
	}
	dq.push_back(id);
	return;
}

void popFromDeque(deque<int> & dq, int id){
	deque<int>::iterator front = dq.begin();
	deque<int>::iterator back = dq.end();
	int count = 0;
	while (front + count != back)
	{
		if (id == *(dq.begin() + count)) 
		{
			dq.erase(dq.begin() + count);
			return;
		}
		else 
		{
			count++;
		}
	}
	return;
}

void init() {
	for (int i = 0; i < 6; i++)
	{
		students[i].clear();
	}
	idContainer.clear();
	return;
}

int add(int mId, int mGrade, char mGender[7], int mScore) {
	int category = ((mGrade - 1) * 2);
    if (mGender[0] == 'f') category++;
	idContainer[mId] = make_pair(category, mScore);
	if (students[category].find(mScore) == students[category].end()){
		students[category][mScore] = deque<int> (mId);
	} else {
		insertDeque(students[category][mScore], mId);
	}
	deque<int> deq = (students[category].end()--)->second;
	return deq.back();
}

int remove(int mId) {
	if (idContainer.find(mId) == idContainer.end())
	{
		return 0;
	}
	
	int category = idContainer[mId].first;
	int score = idContainer[mId].second; 
	popFromDeque(students[category][score], mId);
	idContainer.erase(mId);
	if (students[category][score].empty()) {students[category].erase(score);}
    if (students[category].empty()) {return 0;}
	deque<int> deq = (students[category].begin())->second;
	// return deq.empty() ? 0 : deq.front();
	return deq.front();
}

int query(int mGradeCnt, int mGrade[], int mGenderCnt, char mGender[][7], int mScore) {
	vector<int> candidates {};
	for (int i = 0; i < mGenderCnt; i++)
	{
		for (int j = 0; j < mGenderCnt; j++)
		{
			int category = ((mGrade[i] - 1) * 2);
   			if (mGender[j][0] == 'f') category++;
			candidates.push_back(category);
		}
	}
	pair<int, int> winner = make_pair(300001, 1000000001);

	for (int cand : candidates)
	{
		map<int, deque<int>>::iterator tmp;
		if (students[cand].find(mScore) != students[cand].end()){
			tmp = students[cand].find(mScore);
		} 
		else 
		{
			tmp = students[cand].upper_bound(mScore);
		}
		if (tmp == students[cand].end()) continue;
		if (tmp->first < winner.first)
		{
			winner = make_pair(tmp->first , tmp->second.front());
		} 
		else if (tmp->first == winner.first && tmp->second.front() < winner.second)
		{
			winner = make_pair(tmp->first , tmp->second.front());
		}
	} 
	
	return winner.first == 300001 ? 0 : winner.second;
}

static bool run() {
	int q;
	cin >> q;

	int id, grade, score;
	char gender[7];
	int cmd, ans, ret;
	bool okay = false;

	for (int i = 0; i < q; ++i) {
		// scanf("%d", &cmd);
		cin >> cmd;
		switch (cmd) {
			case CMD_INIT:
				init();
				okay = true;
				break;
			case CMD_ADD:
				// scanf("%d %d %s %d %d", &id, &grade, gender, &score, &ans);
				cin >> id >> grade >> gender >> score >> ans;
				ret = add(id, grade, gender, score);
				if (ans != ret)
					okay = false;
				break;
			case CMD_REMOVE:
				// scanf("%d %d", &id, &ans);
				cin >> id >> ans;
				ret = remove(id);
				if (ans != ret)
					okay = false;
				break;
			case CMD_QUERY: {
				int gradeCnt, genderCnt;
				int gradeArr[3];
				char genderArr[2][7];
				// scanf("%d", &gradeCnt);
				cin >> gradeCnt;
				if (gradeCnt == 1) {
					// scanf("%d %d", &gradeArr[0], &genderCnt);
					cin >> gradeArr[0] >> genderCnt;
				} else if (gradeCnt == 2) {
					// scanf("%d %d %d", &gradeArr[0], &gradeArr[1], &genderCnt);
					cin >> gradeArr[0] >> gradeArr[1] >> genderCnt;
				} else {
					// scanf("%d %d %d %d", &gradeArr[0], &gradeArr[1], &gradeArr[2], &genderCnt);
					cin >> gradeArr[0] >> gradeArr[1] >> gradeArr[2] >> genderCnt;
				}
				if (genderCnt == 1) {
					// scanf("%s %d %d", genderArr[0], &score, &ans);
					cin >> genderArr[0] >> score >> ans;
				} else {
					// scanf("%s %s %d %d", genderArr[0], genderArr[1], &score, &ans);
					cin >> genderArr[0] >> genderArr[1] >> score >> ans;
				}
				ret = query(gradeCnt, gradeArr, genderCnt, genderArr, score);
				if (ans != ret)
					okay = false;
				break;
			}
			default:
				okay = false;
				break;
		}
	}
	return okay;
}

int main() {
	// setbuf(stdout, NULL);
    ios::sync_with_stdio(false), cin.tie(0);
	//freopen("sample_input.txt", "r", stdin);

	int T, MARK;
	// scanf("%d %d", &T, &MARK);
	cin >> T >> MARK;
	cout << T << MARK;
	for (int tc = 1; tc <= T; tc++) {
		int score = run() ? MARK : 0;
		// printf("#%d %d\n", tc, score);
		cout << '#' << tc << score << '\n';
	}

	return 0;
}
