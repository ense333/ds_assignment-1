#pragma once
#include "TermsBST.h"
#include <iostream>
#include <string>
using namespace std;

class TermsListNode
{
private:
	string condition;
	int memberCnt;		//To count member Number
	TermsListNode*	next;   //From Linked list, point next Node  
	TermsBST* bstp;    //Pointer that point BST

public:
	TermsListNode() : condition(""), memberCnt(0), next(nullptr), bstp(nullptr) {}
	~TermsListNode() {}

	TermsListNode*	getNext()		 { return next; }
	TermsBST* getRoot() {return bstp;}

	void setNext(TermsListNode* next)	 { this->next = next; }
	void setBSTp(TermsBST* bstp)	{this->bstp = bstp; }
	void setCondition(string& condition)	 { this->condition = condition; }
	void plusMemberCnt() {memberCnt++;}
	void minusMemberCnt() {memberCnt--;}
	string getCondition() {return condition;}
	TermsBST* getBSTp() {return bstp;}
	int getCnt() {return memberCnt;}   
};