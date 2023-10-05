#pragma once
#include "TermsListNode.h"

class TermsLIST
{
private:
	TermsListNode* head;

public:
	TermsLIST();
	~TermsLIST();

	TermsListNode* getHead();

	// insert
	void insert(TermsListNode* bstNode);
	// search
	TermsListNode* search(const string& condition);
	// delete
	int deleteNode(const string& condition);
};

