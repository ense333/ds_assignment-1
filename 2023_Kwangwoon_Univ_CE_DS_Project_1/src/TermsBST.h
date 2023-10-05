#pragma once
#include "TermsBSTNode.h"


class TermsBST
{
private:
	TermsBSTNode* root;

public:
	TermsBST();
	~TermsBST();

	TermsBSTNode* getRoot();

	// insert
	int insert(TermsBSTNode* node); 
	// print
	void print(TermsBSTNode* node, ofstream& flog); 
	//print inorder
	void printInOrder(ofstream& flog);
	// deletebyName
	int deletebyName(const string& date, const string& name);
	// deletebyDate
	string deletebyDate(const string& date);
};