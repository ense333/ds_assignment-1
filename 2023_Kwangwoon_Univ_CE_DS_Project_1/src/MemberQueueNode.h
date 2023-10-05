#pragma once
#include <string>
#include<iostream>
using namespace std;

class MemberQueueNode
{
private:
	string name;
	int age;
	string collection_day;
	string condition;

public:
	MemberQueueNode* next;	
	MemberQueueNode(const string& newName, int newAge, const string& newCollection_day, const string& newCondition)
    : name(newName), age(newAge), collection_day(newCollection_day), condition(newCondition), next(nullptr) {}
	~MemberQueueNode() {}
	void setName(const string& newName);
	void setAge(const int& newAge);
	void setCollection(const string& newCollection_day);
	void setCondition(const string& newCondition);
	const string getName();
	int getAge();
	const string getCollection();
	const string getCondition();
	const string getEndCol();
};

