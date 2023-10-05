#pragma once
#include "MemberQueueNode.h"

class MemberQueue
{
private:
	MemberQueueNode* start;
	MemberQueueNode* rear;
	int cnt;

public:
	MemberQueue();
	~MemberQueue();

	bool empty();
	bool full();
	int push(const string& newName, int newAge, const string& newCollection_day, const string& newCondition);
	MemberQueueNode* pop();
	MemberQueueNode* front();
};

