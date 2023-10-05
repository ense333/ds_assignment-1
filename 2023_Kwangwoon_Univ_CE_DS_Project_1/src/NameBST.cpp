#include "NameBST.h"
#include <iostream>
#include <cstdio>
#include <utility>
#include <fstream>
using namespace std;

NameBST::NameBST() : root(nullptr)
{

}
NameBST::~NameBST()
{

}

NameBSTNode* NameBST::getRoot()    //get NameBST's root 
{
	return root;
}

// insert
int NameBST::insert(NameBSTNode* node)
{    
	NameBSTNode *p = root, *pp = NULL;

	if(root == NULL){   //if BST is empty
		root = node;   //then set root value to node
		return 1;
	}
	while(p){     //if BST is not Empty, then
		pp = p;
		if(node->getNBSTName() < p->getNBSTName()){     //if current node's name value is greater than given node's value
			p = p->getLeft();    //move to left
		}else{				//if current node's name value is less or equal than given node's value
			p = p->getRight();    //move to right
		}
	}

	if (node->getNBSTName() < pp->getNBSTName()) {    //then set left or right node with given node value
        pp->setLeft(node);
    } else {
        pp->setRight(node);
    }
    return 1;
}
// search
NameBSTNode* NameBST::search(const string& name)
{
	NameBSTNode* p = root, *q = NULL;

	while(p && name != p->getNBSTName()){   //searching node with name 
		q = p;
		if(name < p->getNBSTName()){  
			p = p->getLeft();
		}else{
			p = p->getRight();
		}
	}
	if(p == NULL) return NULL; //NOT FOUND
	return p;
}
// print
void NameBST::print(NameBSTNode* node, ofstream& flog)
{
	if(node != NULL){    //since we need to print inOrder way
		print(node->getLeft(), flog);   //move to left first
		flog << node->getNBSTName() << "/" << node->getNBSTAge() << "/" << node->getNBSTCol_Day() << "/" << node->getNBSTEndCol() << "\n";
		print(node->getRight(), flog);
	}
}

void NameBST::printInOrder(ofstream& flog)     //in order to call function with root value which is private
{
	print(root, flog);
}

pair<string, string> NameBST::deleteByName(const string& name)     //return End Collection day and Condition value using pair in order to delete from TermsList, TermsBST
{  
	NameBSTNode* p = root, *q = NULL;
	string resultDate = "";
	string resultCon = "";

	while(p && name != p->getNBSTName()){     //search node to be deleted by using name value
		q = p;
		if(name < p->getNBSTName()){
			p = p->getLeft();
		}else{
			p = p->getRight();
		}
	}
	if(p == NULL){     //If we can't find Name
		resultCon = "NotFound";
		resultDate = "NotFound";
		return make_pair(resultDate, resultCon);
	}
	if(p->getLeft() == NULL && p->getRight() == NULL){		//if p is leaf node
		if(q == NULL){   //if q is NULL then p is leaf and root node
			root = NULL;   //so root node became NULL
		}else if(q->getLeft() == p){   //if q's left node is p
			q->setLeft(nullptr);    //then q's left node will be deleted and become null
		}else{
			q->setRight(nullptr);    //same for right
		}
		resultDate = p->getNBSTEndCol();     //store value before delete
		resultCon = p->getNBSTCondition();
		delete p;
		return make_pair(resultDate, resultCon);    //return as pair using make_pair function
	}
	else if(p->getLeft() == NULL){       //if p only has right child
		if(q == NULL){
			root = p->getRight();
		}
		else if(q->getLeft() == p){
			q->setLeft(p->getRight());
		}else{
			q->setRight(p->getRight());
		}
		resultDate = p->getNBSTEndCol();
		resultCon = p->getNBSTCondition();
		delete p;
		return make_pair(resultDate, resultCon);
	}
	else if(p->getRight() == NULL){		//if p only has left child
		if(q == NULL){
            root = p->getLeft();
        }else if(q->getLeft() == p){
            q->setLeft(p->getLeft());
        }else{
            q->setRight(p->getLeft());
        }
		resultDate = p->getNBSTEndCol();
		resultCon = p->getNBSTCondition();
		delete p;
		return make_pair(resultDate, resultCon);
	}
	else{			//if p has left and right child
		NameBSTNode *prevprev = p, *prev = p->getRight(), *curr = p->getRight()->getLeft();
		while(curr){
			prevprev = prev;
			prev = curr;
			curr = curr->getLeft();
		}
		string currentEndCol = p->getNBSTEndCol();   //Save the value to be deleted 
    	string currentCondition = p->getNBSTCondition();

		//set prev value to p 
		p->setNBSTName(prev->getNBSTName());
        p->setNBSTAge(prev->getNBSTAge());
        p->setNBSTCol_day(prev->getNBSTCol_Day());
        p->setNBSTEndCol(prev->getNBSTEndCol());
		p->setNBSTCondition(prev->getNBSTCondition());
		//set Right and left child value 
		if(prevprev == p){
			prevprev->setRight(prev->getRight());
		}else{ 
			prevprev->setLeft(prev->getRight());
		}
		resultDate = currentEndCol;
   		resultCon = currentCondition;
		delete prev;
		return make_pair(resultDate, resultCon);
	}
}
