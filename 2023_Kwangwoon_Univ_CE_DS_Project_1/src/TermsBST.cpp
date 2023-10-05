#include "TermsBST.h"
#include "NameBST.h"
#include <iostream>
#include <cstdio>  //in order to use sscanf func
#include <fstream>
using namespace std;

TermsBST::TermsBST() : root(nullptr)
{

}
TermsBST::~TermsBST()
{

}


TermsBSTNode* TermsBST::getRoot()
{
	return root;
}

bool checkDate(const string& date1, const string& date2)     //in order to compare date value which is string by converting into integer value
{  //Input value : date1  comparison target : date2
    int nodeCmpYear, nodeCmpMonth, nodeCmpDay, pCmpYear, pCmpMonth, pCmpDay;
    sscanf(date1.c_str(), "%4d-%02d-%02d", &nodeCmpYear, &nodeCmpMonth, &nodeCmpDay);  //using sscanf function to change string value to integer value
    sscanf(date2.c_str(), "%4d-%02d-%02d", &pCmpYear, &pCmpMonth, &pCmpDay);
    if(nodeCmpYear > pCmpYear) return true;
    else if(nodeCmpYear < pCmpYear) return false;
    else{
        if(nodeCmpMonth > pCmpMonth) return true;
        else if(nodeCmpMonth < pCmpMonth) return false;
        else{
            if(nodeCmpDay <= pCmpDay) return false;
            else return true;
        }
    }
}

// insert
int TermsBST::insert(TermsBSTNode* node)
{
    TermsBSTNode *p = root, *pp = NULL;
    int nodeCmpYear, nodeCmpMonth, nodeCmpDay, pCmpYear, pCmpMonth, pCmpDay;
    string nodeCol = node->getEndCol();
    sscanf(nodeCol.c_str(), "%4d-%02d-%02d", &nodeCmpYear, &nodeCmpMonth, &nodeCmpDay);
    //Search for position in BST Tree
    while (p) {
        pp = p;
        string pCol = p->getEndCol();
        sscanf(pCol.c_str(), "%4d-%02d-%02d", &pCmpYear, &pCmpMonth, &pCmpDay);

        if (nodeCmpYear < pCmpYear) {     //if given node's Year value is less than current node's Year value
            p = p->getLeft();       //need to go left node
        } else if (nodeCmpYear == pCmpYear) {       //since year is same, check Month
            if (nodeCmpMonth < pCmpMonth) {            //if given node's month value is less than current node's month value
                p = p->getLeft();           //move to left node
            } else if (nodeCmpMonth > pCmpMonth) {     //if greater then move to Right
                p = p->getRight();
            } else {              //If month value is same
                if (nodeCmpDay < pCmpDay) {         //if given node's day value is less than current node's day value
                    p = p->getLeft();           //move to left node
                } else {
                    p = p->getRight();
                }
            }
        } else {   //given node's Year value is greater than current node's Year value
            p = p->getRight();   //need to go Right node
        }
    }
    //setting child Node
    if (root != NULL) {     //same comparison as above
        if (nodeCmpYear < pCmpYear) {
            pp->setLeft(node);
        } else if (nodeCmpYear == pCmpYear) {
            if (nodeCmpMonth < pCmpMonth) {
                pp->setLeft(node);
            } else if (nodeCmpMonth > pCmpMonth) {
                pp->setRight(node);
            } else {
                if (nodeCmpDay < pCmpDay) {
                    pp->setLeft(node);
                } else {
                    pp->setRight(node);
                }
            }
        } else {
            pp->setRight(node);
        }
    } else {  //if BST is empty then set node as root node
        root = node;
    }
    return 1;
}

// print
void TermsBST::print(TermsBSTNode* node, ofstream& flog)
{
	if(node != NULL){
		print(node->getLeft(), flog);   //since it is InOrder way, move left first
        flog << node->getBSTName() << "/" << node->getBSTAge() << "/" << node->getBSTCol_day() << "/" << node->getEndCol() << "\n";  //then write to log file
		print(node->getRight(), flog);   //then move to right
	}
}

void TermsBST::printInOrder(ofstream& flog)
{
	print(root, flog);
}

// delete by Name with given date value
int TermsBST::deletebyName(const string& date, const string& name)
{   
	TermsBSTNode* p = root, *q = NULL;
	
	int nodeCmpYear, nodeCmpMonth, nodeCmpDay, pCmpYear, pCmpMonth, pCmpDay;
    sscanf(date.c_str(), "%4d-%02d-%02d", &nodeCmpYear, &nodeCmpMonth, &nodeCmpDay);
    //Search with given date value
	while(p && name != p->getBSTName()){
		
		string pCol = p->getEndCol();
        sscanf(pCol.c_str(), "%4d-%02d-%02d", &pCmpYear, &pCmpMonth, &pCmpDay);

		q = p;
		if(nodeCmpYear > pCmpYear){  
			p = p->getRight();
		}else if(nodeCmpYear == pCmpYear){  
			if(nodeCmpMonth > pCmpMonth){
                p = p->getRight();
            }else if(nodeCmpMonth == pCmpMonth){
                if(nodeCmpDay > pCmpDay){
                    p = p->getRight();
                }else{
                    p = p->getLeft();
                }
            }else{
                p = p->getLeft();
            }
		}else{
            p = p->getLeft();
        }

	}
	if(p == NULL) return -1; //NOT found

	if(p->getLeft() == NULL && p->getRight() == NULL){   //p is leaf node
		if(q == NULL){
			root = NULL;
		}else if(q->getLeft() == p){
            q->setLeft(nullptr);
		}else{
            q->setRight(nullptr);
        }
        delete p;
	}
    else if(p->getLeft() == NULL){  //if p only has right child
        if(q == NULL){
            root = p->getRight();
        }
        else if(q->getLeft() == p){
            q->setLeft(p->getRight());
        }else{
            q->setRight(p->getRight());
        }
        delete p;
    }
    else if(p->getRight() == NULL){  //P only has left child
        if(q == NULL){
            root = p->getLeft();
        }else if(q->getLeft() == p){
            q->setLeft(p->getLeft());
        }else{
            q->setRight(p->getLeft());
        }
        delete p;
    }else{     //P has left and right child
        TermsBSTNode *prevprev = p, *prev = p->getRight(), *curr = p->getRight()->getLeft();
        while(curr){
            prevprev = prev;
            prev = curr;
            curr = curr->getLeft();  
        }
        //curr is NULL, prev is the node to be deleted, prevprev is prev's parent, prev->LeftChild is NULL
        //change current node's value with prev value since we delete current node's value
        p->setBSTName(prev->getBSTName());
        p->setBSTAge(prev->getBSTAge());
        p->setBSTCol_day(prev->getBSTCol_day());
        p->setBSTEndCol(prev->getEndCol());
        if(prevprev == p){
            prevprev->setRight(prev->getRight());
        }else{
            prevprev->setLeft(prev->getRight());
        } 
        delete prev;
    }

}

//Delete by date and return deleted node's name in order to delete from NameBST
string TermsBST::deletebyDate(const string& date){ 
    TermsBSTNode* p = root, *q = NULL;
	string result = "";
	int nodeCmpYear, nodeCmpMonth, nodeCmpDay, pCmpYear, pCmpMonth, pCmpDay;
    sscanf(date.c_str(), "%4d-%02d-%02d", &nodeCmpYear, &nodeCmpMonth, &nodeCmpDay);
    //Search for value to be deleted by date
	while(p && !checkDate(date, p->getEndCol())){
		
		string pCol = p->getEndCol();
        sscanf(pCol.c_str(), "%4d-%02d-%02d", &pCmpYear, &pCmpMonth, &pCmpDay);
		q = p;
		if(nodeCmpYear > pCmpYear){ 
			p = p->getRight();
		}else if(nodeCmpYear == pCmpYear){   
			if(nodeCmpMonth > pCmpMonth){
                p = p->getRight();
            }else if(nodeCmpMonth == pCmpMonth){
                if(nodeCmpDay > pCmpDay){
                    p = p->getRight();
                }else{
                    p = p->getLeft();
                }
            }else{
                p = p->getLeft();
            }
		}else{
            p = p->getLeft();
        }

	}
	if(p == NULL) return "NotFound"; //NOT found

	if(p->getLeft() == NULL && p->getRight() == NULL){   //P is leaf node
		if(q == NULL){
			root = NULL;
		}else if(q->getLeft() == p){
            q->setLeft(nullptr);
		}else{
            q->setRight(nullptr);
        }
        result = p->getBSTName();
        delete p;
        return result;
	}
    else if(p->getLeft() == NULL){  //if p only has right child
        if(q == NULL){
            root = p->getRight();
        }
        else if(q->getLeft() == p){
            q->setLeft(p->getRight());
        }else{
            q->setRight(p->getRight());
        }
        result = p->getBSTName();
        delete p;
        return result;
    }
    else if(p->getRight() == NULL){  //P only has left child
        if(q == NULL){
            root = p->getLeft();
        }else if(q->getLeft() == p){
            q->setLeft(p->getLeft());
        }else{
            q->setRight(p->getLeft());
        }
        result = p->getBSTName();
        delete p;
        return result;
    }
    else{   //P has left and right child
        TermsBSTNode *prevprev = p, *prev = p->getRight(), *curr = p->getRight()->getLeft();
        while(curr){
            prevprev = prev;
            prev = curr;
            curr = curr->getLeft();  
        }
        result = p->getBSTName();   //in order to save node's name before change below

        //curr is NULL, prev is the node to be deleted, prevprev is prev's parent, prev->LeftChild is NULL
        p->setBSTName(prev->getBSTName());
        p->setBSTAge(prev->getBSTAge());
        p->setBSTCol_day(prev->getBSTCol_day());
        p->setBSTEndCol(prev->getEndCol());

        if(prevprev == p){ 
            prevprev->setRight(prev->getRight());
        }else{
            prevprev->setLeft(prev->getRight());
        }
        delete prev;
        return result;
    }
}