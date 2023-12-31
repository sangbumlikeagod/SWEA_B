#define MAX_N 50000
#define MAX_M 50000
#define MAX_LEN 11
#define ull unsigned long long

#include <unordered_set>
#include <vector>

using namespace std;

#define getLen(v) (v & 15)
#define getPos(i) (5 * (9 - (i)))
#define getCh(v, i) (((v >> (getPos(i) + 4)) & 31) - 1)
#define getFirstCh(v) getCh(v, 0)
#define getLastCh(v) getCh(v, getLen(v) - 1)

inline ull encode(char word[])
{
	ull ret = 0ULL;
	int len = 0;

	for (; len < 10 && word[len] != 0; len++)
	{
		ret = (ret << 5) | (word[len] - 'a' + 1);
	}

	return (ret << (getPos(len-1) + 4)) | len;
}

inline ull flip(ull word)
{
	int len = getLen(word);
	word >>= getPos(len-1) + 4;
	ull ret = 0;

	while (word)
	{
		ret <<= 5;
		ret |= word & 31;
		word >>= 5;
	}

	return (ret << (getPos(len-1) + 4)) | len;
}

#define p(i) (((i)-1)>>1)
#define lc(i) (((i)<<1)+1)
#define rc(i) (lc(i)+1)
#define swap(a,b) (a^=b^=a^=b)

struct Heap
{
	int size;
	ull h[MAX_M];

	void clear()
	{
		size = 0;
	}

	void push(ull v)
	{
		h[size++] = v;
		for (int i = size - 1; i > 0 && h[i] < h[p(i)]; i = p(i))
			swap(h[i], h[p(i)]);
	}

	ull pop()
	{
		ull r = h[0];
		h[0] = h[--size];
		for (int i = 0; lc(i) < size;)
		{
			if (rc(i) < size && h[rc(i)] < h[i] && h[rc(i)] < h[lc(i)])
			{
				swap(h[rc(i)], h[i]);
				i = rc(i);
			}
			else if (h[lc(i)] < h[i]) {
				swap(h[lc(i)], h[i]);
				i = lc(i);
			}
			else
				break;
		}
		return r;
	}
} words[26];

struct Hash
{
	static const int KEY_BIT_CNT = 16;
	static const int IDX_MASK = (1 << 17) - 1;

	int tc = 0;
	int size;

	int head[1 << KEY_BIT_CNT];
	int next[MAX_M * 2];
	ull val[MAX_M * 2];
	
	inline int getKey(ull v)
	{
		return (v >> (5 * 10 + 4 - KEY_BIT_CNT)) & ((1 << KEY_BIT_CNT) - 1);
	}

	bool exists(ull v)
	{
		int key = getKey(v);
		for (int cur = head[key]; (cur & ~IDX_MASK) == tc; cur = next[cur & IDX_MASK])
			if (val[cur & IDX_MASK] == v)
				return true;

		return false;
	}

	void insert(ull v)
	{
		int idx = size++;
		val[idx] = v;

		int key = getKey(v);
		next[idx] = head[key];
		head[key] = idx | tc;
	}

	void clear()
	{
		tc += IDX_MASK + 1;
		size = 0;
	}
} wordSet;

struct Cycle
{
	int size;
	int cur;
	int prv[MAX_N];
	int nxt[MAX_N];

	void init(int N)
	{
		size = N;
		cur = 0;
		for (int i = 0; i < N; i++)
		{
			prv[i] = (N + i - 1) % N;
			nxt[i] = (i + 1) % N;
		}
	}

	void setCur(int mID)
	{
		cur = mID - 1;
	}

	void next()
	{
		cur = nxt[cur];
	}

	int pop()
	{
		nxt[prv[cur]] = nxt[cur];
		prv[nxt[cur]] = prv[cur];
		return cur + 1;
	}
} cycle;

vector<ull> used;

void addWord(ull word)
{
	int key = getFirstCh(word);
	words[key].push(word);
	wordSet.insert(word);
}

void init(int N, int M, char mWords[][MAX_LEN])
{
	for (int i = 0; i < 26; i++)
		words[i].clear();
	wordSet.clear();

	for (int i = 0; i < M; i++)
		addWord(encode(mWords[i]));

	cycle.init(N);
}

ull getNextWord(ull word) {
	int key = getLastCh(word);
	if (words[key].size > 0)
	{
		ull nextWord = words[key].pop();
		used.push_back(nextWord);
		return nextWord;
	}
	return 0;
}

int playRound(int mID, char mCh)
{
	char first[2] = { mCh, 0 };
	ull word = encode(first);

	cycle.setCur(mID);
	while ((word = getNextWord(word)) != 0)
		cycle.next();

	for (ull word : used)
	{
		ull flipped = flip(word);
		if (!wordSet.exists(flipped))
			addWord(flipped);
	}
	used.clear();

	return cycle.pop();
}