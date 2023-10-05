#pragma once
#include <iostream>
#include <string>
#include "MemberQueueNode.h"
using namespace std;

class NameBSTNode
{
private:
	string nBSTName;
	int nBSTAge;
	string nBSTCollection_day;
	string nBSTEndCol;
	string nBSTCondition;
	NameBSTNode*	left;
	NameBSTNode*	right;
	

public:
	NameBSTNode(MemberQueueNode* Nnode) : nBSTName(Nnode->getName()), nBSTAge(Nnode->getAge()), nBSTCollection_day(Nnode->getCollection()), nBSTEndCol(Nnode->getEndCol()), nBSTCondition(Nnode->getCondition()), left(nullptr), right(nullptr) {}
	~NameBSTNode() {}

	NameBSTNode*	getLeft()			{ return left; }
	NameBSTNode*	getRight()			{ return right; }

	void setLeft(NameBSTNode* left)						{ this->left = left; }
	void setRight(NameBSTNode* right)					{ this->right = right; }
	
	void setNBSTName(const string& nBSTName) {this->nBSTName = nBSTName;};
	void setNBSTAge(int nBSTAge) {this->nBSTAge = nBSTAge;};
	void setNBSTCol_day(const string& nBSTCollection_day) {this->nBSTCollection_day = nBSTCollection_day;};
	void setNBSTEndCol(const string& nBSTEndCol) {this->nBSTEndCol = nBSTEndCol;};
	void setNBSTCondition(const string& nBSTCondition) {this->nBSTCondition = nBSTCondition;};
	
	string getNBSTName() {return nBSTName;};
	int getNBSTAge() {return nBSTAge;}
	string getNBSTCol_Day() {return nBSTCollection_day;}
	string getNBSTEndCol() {return nBSTEndCol;};
	string getNBSTCondition() {return nBSTCondition;}
};