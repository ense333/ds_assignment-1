#pragma once
#include "MemberQueue.h"
#include "TermsList.h"
#include "TermsBST.h"
#include "NameBST.h"
#include <fstream>
using namespace std;

class Manager
{
private:
	ifstream	fcmd;
	ofstream	flog;

public:
	Manager();
	~Manager();

	void run(const char* command);
	
	void PrintSuccess(const char* cmd);
	void PrintErrorCode(int num);

	// LOAD
	int LOAD(MemberQueue* queuePointer);
	// ADD
	int ADD(MemberQueue* queuePointer, const string& newName, int newAge, const string& newCollection_day, const string& newCondition);
	// QPOP
	int QPOP(MemberQueue* queuePointer, TermsLIST* listPointer, NameBST* nameBSTPointer);
	// SEARCH
	int SEARCH(NameBST* nameBSTPointer, const string& name);
	// PRINT
	int PRINT(const string& keyword, NameBST* newBST, TermsLIST* newLIST);
	// DELETE
	int DELETE(const string& deleteTarget, const string& deleteValue, NameBST* bstP, TermsLIST* listP);
	// EXIT
	int EXIT();
};
