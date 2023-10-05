#pragma once
#include "NameBSTNode.h"

class NameBST
{
private:
	NameBSTNode* root;

public:
	NameBST();
	~NameBST();

	NameBSTNode* getRoot();

	// insert
	int insert(NameBSTNode* node);
	// search
	NameBSTNode* search(const string& name);
	// print
	void print(NameBSTNode* node, ofstream& flog);

	void printInOrder(ofstream& flog);
	// delete
	pair<string, string> deleteByName(const string& name);
};