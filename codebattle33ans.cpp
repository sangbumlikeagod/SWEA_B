#define nullptr		0

#define MAXN		50001
#define MAXM		50001
#define MAXK		200001

#define func(a,b) (a+b)

template <typename T>
void zwap(T &a, T &b)
{
	T t = a; a = b; b = t;
}

struct Robot
{
	int rID;		// 로봇의 아이디
	int IQ;			// 지능
	int wID;		// 일하고 있는 작업 번호
	int begin;		// 일을 시작한 시각
	bool broken;	// 고장 여부
	
	int maxidx, minidx;	// maxHeap과 minHeap 에서의 위치 기억
};

Robot robot[MAXN];

struct Job			// 작업 객체 구조체
{
	Robot** arr;	// 투입된 로봇 정보
	int n;
};

Job jobs[MAXM];		// jobs[i] := i 번째 작업 정보

int mm;
Robot* mem[MAXK];	// mem[i] := i 번째 로봇의 정보

Robot** getRobot(int n)
{
	Robot** ret = &mem[mm];
	mm += n;
	
	return ret;
}

struct maxcomp
{
	void set(Robot* a, int idx)
	{
		a->maxidx = idx;
	}

	bool operator() (Robot* a, Robot* b)
	{
		return a->IQ != b->IQ ? a->IQ < b->IQ : a->rID > b->rID;
	}
};

struct mincomp
{
	void set(Robot* a, int idx)
	{
		a->minidx = idx;
	}
	
	bool operator() (Robot* a, Robot* b)
	{
		return a->IQ != b->IQ ? a->IQ > b->IQ : a->rID > b->rID;
	}
};

template<typename C>
struct Que // 쉬는 로봇들을 담는 자료구조
{
	Robot* arr[MAXN + 1];
	int size;

	C comp;
	
	void init()
	{
		size = 0;
	}
	
	void init(int n, Robot heapifed[])
	{
		for (int i = 0; i < n; ++i)
		{
			arr[i] = &heapifed[i + 1];
			comp.set(arr[i], i);
		}
		
		size = n;
	}
	
	void push(Robot* v)
	{
		arr[size] = v;
		comp.set(arr[size], size);
		
		int cur = size++;
		
		while (cur > 0)
		{
			int par = (cur - 1) / 2;
			if (comp(arr[cur], arr[par]))
				break;
			zwap(arr[cur], arr[par]);
			comp.set(arr[cur], cur);
			comp.set(arr[par], par);
			cur = par;
		}
	}
	
	Robot* pop()
	{
		if (size == 0) return nullptr;
		
		Robot* ret = arr[0];
		arr[0] = arr[--size];
		comp.set(arr[0], 0);
		
		int cur = 0;
		while (cur * 2 + 1 < size)
		{
			int child = cur * 2 + 2 < size && comp(arr[cur * 2 + 1], arr[cur * 2 + 2]) ? cur * 2 + 2 : cur * 2 + 1;
			if (comp(arr[child], arr[cur]))
				break;
			zwap(arr[cur], arr[child]);
			comp.set(arr[cur], cur);
			comp.set(arr[child], child);
			cur = child;
		}
		
		return ret;
	}
	
	void remove(int idx)
	{
		if (idx >= size) return;
		
		arr[idx] = arr[--size];
		comp.set(arr[size], idx);

		int cur = idx;
		while (cur * 2 + 1 < size)
		{
			int child = cur * 2 + 2 < size && comp(arr[cur * 2 + 1], arr[cur * 2 + 2]) ? cur * 2 + 2 : cur * 2 + 1;
			if (comp(arr[child], arr[cur]))
				break;
			zwap(arr[cur], arr[child]);
			comp.set(arr[cur], cur);
			comp.set(arr[child], child);
			cur = child;
		}

		while (cur > 0)
		{
			int par = (cur - 1) / 2;
			if (comp(arr[cur], arr[par]))
				break;
			zwap(arr[cur], arr[par]);
			comp.set(arr[cur], cur);
			comp.set(arr[par], par);
			cur = par;
		}		
	}
};

Que<maxcomp> maxque;
Que<mincomp> minque;

void init(int N)  // 초기화
{
	for (int i = 1; i <= N; ++i)
	{
		robot[i].rID = i;
		robot[i].IQ = 0;
		robot[i].wID = 0;
		robot[i].begin = 0;
		robot[i].broken = false;
	}
	
	maxque.init(N, robot);	
	minque.init(N, robot);
	
	mm = 0;
}

int callJob(int cTime, int wID, int mNum, int mOpt)  // cTime 시간에 wID 작업으로 mNum대의 로봇을 투입한다. mOpt 기준에 맞게 한다.
{
	jobs[wID].arr = getRobot(mNum);
	jobs[wID].n = mNum;
	
	int ret = 0;
	if (mOpt == 0)  // 높은 지능을 우선으로
	{
		int cnt = 0;
		while (cnt < mNum)
		{
			Robot* p = maxque.pop();	// 제일 높은 지능의 로봇을 선택
			
			// 작업에 로봇을 배정한다.
			p->wID = wID;
			p->begin = cTime;
			jobs[wID].arr[cnt++] = p;
			
			// 해당 로봇을 minque 에서도 제외한다.
			minque.remove(p->minidx);
			ret += p->rID;
		}
	}
	else  // 낮은 지능을 우선으로
	{
		int cnt = 0;
		while (cnt < mNum)
		{
			Robot* p = minque.pop();	// 제일 낮은 지능의 로봇을 선택
			
			// 작업에 로봇을 배정한다.
			p->wID = wID;
			p->begin = cTime;
			jobs[wID].arr[cnt++] = p;
			
			// 해당 로봇을 maxque 에서도 제외한다.
			maxque.remove(p->maxidx);
			ret += p->rID;
		}
	}

	return ret;
}

void returnJob(int cTime, int wID)	// cTime 시간에 wID 작업에 있는 로봇들을 반환한다.
{
	int n = jobs[wID].n;
	for (int i = 0; i < n; ++i)
	{
		Robot* p = jobs[wID].arr[i];
		if (p->broken || p->wID != wID)	// 로봇이 고장났거나, 다른 작업 중이면 무시한다. (Lazy return)
			continue;

		// 작업 시간만큼 지능을 낮춘다.
		p->IQ -= cTime - p->begin;
		p->wID = 0;
		
		// 가용 로봇 집합에 반환시킨다.
		maxque.push(p);
		minque.push(p);
	}
}

void broken(int cTime, int rID)	// cTime 시간에 rID 로봇이 고장난다.
{
	if (robot[rID].wID != 0)	// 작업 중이라면, 작업을 취소하고 고장 처리한다.
	{
		robot[rID].wID = 0;
		robot[rID].broken = true;
	}
}

void repair(int cTime, int rID)	// cTime 시간에 rID 로봇이 고쳐졌다.
{
	if (robot[rID].broken)
	{
		robot[rID].IQ = -cTime;		// 로봇의 지능 지수를 -cTime 으로 처리한다.
		robot[rID].broken = false;
		
		// 가용 로봇 집합에 반환시킨다.
		maxque.push(&robot[rID]);
		minque.push(&robot[rID]);
	}
}

int check(int cTime, int rID)	// cTime 시간에 rID 로봇의 상황을 확인한다.
{
	int ret;
	if (robot[rID].broken)			// 고장난 상태
		ret = 0;
	else if (robot[rID].wID != 0)	// 작업 중인 상태
		ret = -robot[rID].wID;
	else							// 그 외의 상태
		ret = cTime + robot[rID].IQ;	// 깎인 지능에 흐른 시간을 더하면 원래 지능이 계산된다.

	return ret;
}
