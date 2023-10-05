#include "TermsList.h"
#include "TermsBST.h"
#include <iostream>
#include <string>
using namespace std;

TermsLIST::TermsLIST(): head(nullptr)
{

}
TermsLIST::~TermsLIST()
{

}

TermsListNode* TermsLIST::getHead()    //return TermsList's head 
{
	return head;
}

// insert
void TermsLIST::insert(TermsListNode* bstNode)
{
	if(head == nullptr){  //If TermsList is empty
		TermsBST* termsHeadBST = new TermsBST();   //create new TermsBST 
		head = bstNode;		//and set given input value to head
		bstNode->setNext(nullptr);		//set next value to NULL
		bstNode->setBSTp(termsHeadBST);  //given input value to point to TermsBST, since it is new TermsList node
		bstNode->plusMemberCnt();   //increase count value for Each Condition 
		return;
	}
	TermsListNode* curr = head;
	while(curr){ 
		if(curr->getCondition() == bstNode->getCondition()){  //If corresponding node exists
			curr->plusMemberCnt();		//Then only increase count value
			return;
		}
		if(curr->getNext() == nullptr) {  //If there is no current condition value's node
			curr->setNext(bstNode);    //link with new Node
			TermsBST* termsBST = new TermsBST();    //Create new TermsBST for corresponding condition
			bstNode->setNext(nullptr);		//set next value to NULL
			bstNode->setBSTp(termsBST);  	//given input value to point to TermsBST, since it is new TermsList node
			bstNode->plusMemberCnt(); 	 //increase count value for Each Condition 
			return;
		}
		curr = curr->getNext();   //move to next node
	}
}
// search
TermsListNode* TermsLIST::search(const string& condition)
{
	TermsListNode* curr = head;   //get head node
	while(curr){  //until node has value
		if(curr->getCondition() == condition) return curr;  //If value is found return current node
		curr = curr->getNext();   //move to next node
	}
	return NULL;  //fail to find
}

// delete
int TermsLIST::deleteNode(const string& condition)
{
	TermsListNode* curr = head;
	TermsListNode* prev = nullptr;
	//Find node to delete 
	while(curr != nullptr && curr->getCondition() != condition){
		prev = curr;
		curr = curr->getNext();
	}
	//If we can't find node to delete
	if(curr == nullptr){
		return -1;
	}
	//Find the node to be deleted and connect the preceding node with the node to be deleted
	if(prev != nullptr){
		if(curr->getCnt() > 1){   //if member count is above 1
			curr->minusMemberCnt();  //just decrease membercount
			return 1;	
		}  
		prev->setNext(curr->getNext());   //if member count is 1, then connect the preceding node
	} else {  //If node to delete is first node
		if(curr->getCnt() > 1){
			curr->minusMemberCnt();
			return 1;
		}
		head = curr->getNext();  
	}
	//delete node
	delete curr;
	return 1;
}