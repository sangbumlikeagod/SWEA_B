#include <iostream>
#include <algorithm>
#include <unordered_map>
#include <vector>
#include <queue>

using namespace std;


vector<int> userAlarmSizeAndUpdatedAt[501];
vector<int> newsWhereCompanyAndCreatedAt[30001];

vector<vector<int>> newspaperSubscriber[501];
vector<int> userAlarmStack[501];

int maxUser;
int maxNewspaper;

int userIdx;
int newspaperIdx;
int newsIdx;

unordered_map<int, int> newsIndexer;
unordered_map<int, int> userIndexer;
unordered_map<int, int> newspaperIndexer;

struct VectorComparison {
	bool operator()(vector<int> a, vector<int> b) {
		if (a[0] != b[0])
		{
			return a[0] > b[0];
		}
		else
		{
			return a[1] > b[1];
		}
	}
};

priority_queue<vector<int>, vector<vector<int>>, VectorComparison> *newspaperQueue[501];
priority_queue<vector<int>, vector<vector<int>>, VectorComparison> *newsGatherer;



void gatherNews(int mTime)
{
	// cout << "GatherNews����" << '\n';
	for (int i = 0; i < newspaperIdx; i++)
	{
		// ���� �ð��� �� �߰��Ǳ�� �� �ð����� ũ�ٸ� 
		while (newspaperQueue[i]->empty() == false && newspaperQueue[i]->top()[0] <= mTime)
		{
			// ����� ������ �ƴ� ��쿡�� 
			int realNewsIdx = newsIndexer[newspaperQueue[i]->top()[1]];
			if (newsWhereCompanyAndCreatedAt[realNewsIdx][0] != -1)
			{
				newsGatherer->push(vector<int> {newspaperQueue[i]->top()[0], newspaperQueue[i]->top()[1], i});
			}
			newspaperQueue[i]->pop();
		}
	}
	// ����� ������ ���� �ʴ´ٰ� ����

	while (newsGatherer->empty() == false)
	{
		int nextNewsPaper = newsGatherer->top()[2];

		for (vector<int> realUserIdAndAddedTime : newspaperSubscriber[nextNewsPaper])
		{
			// cout << realUserId << "�� 1�� ���Ѵ�" << '\n';
			int realUserId = realUserIdAndAddedTime[0];
			userAlarmStack[realUserId].push_back(newsGatherer->top()[1]);
			userAlarmSizeAndUpdatedAt[realUserId][0] ++;
			//if (realUserId == 15)
			//{
			//	cout << "user15��" << newsGatherer->top()[1] << "�� ����" << '\n';
			//}
			// cout << userAlarmSizeAndUpdatedAt[realUserId][0] << '\n';
			// �ε��� �� newsId�� ����ǰ� ����
		}
		newsGatherer->pop();
	}
	// cout << "gatherNews" << '\n';
}

void init(int N, int K)
{
	maxUser = N;
	maxNewspaper = K;

	userIdx = 0;
	newspaperIdx = 0;
	newsIdx = 0;

	newsIndexer.clear();
	newspaperIndexer.clear();
	userIndexer.clear();
	
	newsGatherer = new priority_queue<vector<int>, vector<vector<int>>, VectorComparison>;

	for (int i = 0; i < K; i++)
	{
		newspaperQueue[i] = new priority_queue<vector<int>, vector<vector<int>>, VectorComparison>;
	}
	for (int i = 0; i < N; i++)
	{
		userAlarmSizeAndUpdatedAt[i] = { 0, 0 };
		userAlarmStack[i].clear();
	}
	for (int i = 0; i < K; i++)
	{
		newspaperSubscriber[i].clear();
	}
	for (int i = 0; i < 30001; i++)
	{
		newsWhereCompanyAndCreatedAt[i] = { 0, 0 };
	}
}

void registerUser(int mTime, int mUID, int mNum, int mChannelIDs[])
{
	gatherNews(mTime);
	// userId �ε��� �׷��� ���� ���� ����
	//int realUserId;
	if (userIndexer.find(mUID) == userIndexer.end())
	{
		userIndexer[mUID] = userIdx++;

	}
	int	realUserId = userIndexer[mUID];


	for (int i = 0; i < mNum; i++)
	{
		// ���� ���� ���� 
		if (newspaperIndexer.find(mChannelIDs[i]) == newspaperIndexer.end())
		{
			newspaperIndexer[mChannelIDs[i]] = newspaperIdx++;
		}
		int realNewspaperIdx = newspaperIndexer[mChannelIDs[i]];
		newspaperSubscriber[realNewspaperIdx].push_back(vector<int> {realUserId, mTime});
	}
	// cout << "registerUser" << '\n';
}

int offerNews(int mTime, int mNewsID, int mDelay, int mChannelID)
{
	gatherNews(mTime);
	int realNewsIdx = newsIdx;
	newsIndexer[mNewsID] = newsIdx++;
	int realNewspaperIdx = newspaperIndexer[mChannelID];

	newspaperQueue[realNewspaperIdx]->push(vector<int> {mTime + mDelay, mNewsID});
	newsWhereCompanyAndCreatedAt[realNewsIdx][0] = realNewspaperIdx;
	newsWhereCompanyAndCreatedAt[realNewsIdx][1] = mTime + mDelay;

	// cout << "offerNews" << '\n';
	return newspaperSubscriber[realNewspaperIdx].size();
}

void cancelNews(int mTime, int mNewsID)
{
	gatherNews(mTime);
	int realNewsIdx = newsIndexer[mNewsID];
	//  ��¥ �Ź��� �ε����� ����Ǿ�����
	if (newsWhereCompanyAndCreatedAt[realNewsIdx][1] == -1) {
		return;
	}

	int realNewspaperIdx = newsWhereCompanyAndCreatedAt[realNewsIdx][0];
	for (vector<int> realUserIdAndAddedTime : newspaperSubscriber[realNewspaperIdx])
	{
		int realUserId = realUserIdAndAddedTime[0];
		int AddedTime = realUserIdAndAddedTime[1];
		// �� �ֽſ� ������Ʈ �ƴٸ� �������� ���� ������Ʈ �Ǳ� ���� ��ҵƴٸ� ������ updatedTime�� �� �����̸� ( ���� Ÿ���̸� 0�� ���� ���� )
		if (AddedTime < newsWhereCompanyAndCreatedAt[realNewsIdx][1] &&  mTime >= newsWhereCompanyAndCreatedAt[realNewsIdx][1] && userAlarmSizeAndUpdatedAt[realUserId][1] < newsWhereCompanyAndCreatedAt[realNewsIdx][1])
		{
			userAlarmSizeAndUpdatedAt[realUserId][0]--;
		}
	}
	newsWhereCompanyAndCreatedAt[realNewsIdx][0] = -1;
	newsWhereCompanyAndCreatedAt[realNewsIdx][1] = -1;
}

int checkUser(int mTime, int mUID, int mRetIDs[])
{
	gatherNews(mTime);

	int realUserId = userIndexer[mUID];
	int fillSize = 0;
	int returnValue = userAlarmSizeAndUpdatedAt[realUserId][0];

	int retVal = 0;

	while (fillSize < 3 && userAlarmStack[realUserId].empty() == false)
	{
		int siz = userAlarmStack[realUserId].size();
		int nextNewsIdx = userAlarmStack[realUserId][siz - 1];
		int realNewsIdx = newsIndexer[nextNewsIdx];
		if (newsWhereCompanyAndCreatedAt[realNewsIdx][0] != -1)
		{
			mRetIDs[fillSize++] = nextNewsIdx;
			retVal++;
			// cout << nextNewsIdx << '\t';

		}
		userAlarmStack[realUserId].pop_back();
	}

		//while (userAlarmStack[realUserId].empty() == false)
		//{
		//	int siz = userAlarmStack[realUserId].size();
		//	int nextNewsIdx = userAlarmStack[realUserId][siz - 1];
		//	int realNewsIdx = newsIndexer[nextNewsIdx];
		//	if (newsWhereCompanyAndCreatedAt[realNewsIdx][0] != -1)
		//	{
		//		retVal++;
		//	}
		//	userAlarmStack[realUserId].pop_back();
		//}
	userAlarmStack[realUserId].clear();
	userAlarmSizeAndUpdatedAt[realUserId][0] = 0;
	userAlarmSizeAndUpdatedAt[realUserId][1] = mTime;
	// cout << "checkUser" << '\n';
	return returnValue;
}

