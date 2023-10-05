#pragma once
#include <string>
#include <iostream>

#include "MemberQueueNode.h"

using namespace std;

class TermsBSTNode
{
private:
	string BSTName;     
	int BSTAge;
	string BSTCollection_day;
	string BSTEndCol;     //End of Collection day
	TermsBSTNode*	left;
	TermsBSTNode*	right;


public:
	TermsBSTNode(MemberQueueNode* Nnode) : BSTName(Nnode->getName()), BSTAge(Nnode->getAge()), BSTCollection_day(Nnode->getCollection()), BSTEndCol(Nnode->getEndCol()), left(nullptr), right(nullptr) {}
	~TermsBSTNode() {}

	TermsBSTNode*	getLeft()			{ return left; }
	TermsBSTNode*	getRight()			{ return right; }

	void setLeft (TermsBSTNode* left)	{ this->left = left; }
	void setRight(TermsBSTNode* right)	{ this->right = right; }
	
	string getBSTName() {return BSTName;};
	int getBSTAge() {return BSTAge;};
	string getBSTCol_day() {return BSTCollection_day;};
	string getEndCol() {return BSTEndCol;};
	void setBSTName(const string& bstName) {this->BSTName = bstName;};
	void setBSTAge(int bstAge) {this->BSTAge = bstAge;};
	void setBSTCol_day(const string& bstCollection_day) {this->BSTCollection_day = bstCollection_day;};
	void setBSTEndCol(const string& bstEndCol) {this->BSTEndCol = bstEndCol;};
};