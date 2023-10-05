#include "Manager.h"
#include <iostream>
#include <sstream>
using namespace std;


Manager::Manager()
{

}
Manager::~Manager()
{

}

void Manager::run(const char* command)
{
    // Open command & log file
    fcmd.open(command);
    flog.open("log.txt");
    if (!fcmd)   //if we can't open command.txt file
    {
        flog << "Fail to open command file" << endl;
        exit(-1);  //End program
    }
    if(!flog){  //if we can't open log.txt file
        flog << "Fail to open log file" << endl;
        exit(-1);   //End program
    }

    //Create each new instance
    MemberQueue* newQueue = new MemberQueue();    //Create MemberQueue instance 
    TermsLIST* newList = new TermsLIST();       //Create TermsList instance
    NameBST* newBst = new NameBST();            //Create NameBST instance

    // Run command
    string commandLine = "";   //To get command line
    while(getline(fcmd, commandLine)){   //using getline function to read command file
        int result = 0;    //to store result from each Command function
        istringstream iss(commandLine);    //using istringstream to change string to input stream
        string commandStart = "";   //To get Command Name like LOAD, ADD..
        iss >> commandStart;     //Read Command Name
        if(commandStart == "LOAD"){
            result = LOAD(newQueue);
        }else if(commandStart == "ADD"){
            string addName, addDate, addCond = "";
            int addAge = 0;
            iss >> addName >> addAge >> addDate >> addCond;  //Read Data
            result = ADD(newQueue, addName, addAge, addDate, addCond);   //And call ADD function with data
        }else if(commandStart == "QPOP"){
            result = QPOP(newQueue, newList, newBst);
        }else if(commandStart == "SEARCH"){
            string searchName = "";
            iss >> searchName;
            result = SEARCH(newBst, searchName);
        }else if(commandStart == "PRINT"){
            string searchCond = "";    //searchCond : Condition(A, B, C, D) or NAME
            iss >> searchCond;
            result = PRINT(searchCond, newBst, newList);
        }else if(commandStart == "DELETE"){
            string searchType, searchValue = "";    //SearchType : DATE, NAME   
            iss >> searchType >> searchValue;
            result = DELETE(searchType, searchValue, newBst, newList);
        }else if(commandStart == "EXIT"){
            EXIT();
            fcmd.close();   //Close command.txt
            flog.close();   //close log.txt
            return;   //End program
        }else{  //Wrong command
            PrintErrorCode(1000);
        }
    }
    fcmd.close();   //Close command.txt
    flog.close();   //close log.txt
    return;
}

void Manager::PrintSuccess(const char* cmd)
{
    flog << "===== " << cmd << " =====" << endl;
    flog << "Success" << endl;
    flog << "=================" << endl << endl;
}
void Manager::PrintErrorCode(int num)
{
    flog << "===== ERROR =====" << endl;
    flog << num << endl;
    flog << "=================" << endl << endl;
}

// LOAD
int Manager::LOAD(MemberQueue* queuePointer)
{
    if(!queuePointer->empty()){   //If queue is not Empty then Error
        PrintErrorCode(100);
        return 100;
    }
    ifstream dataFile("data.txt");  
    if(!dataFile){   //Fail to open data file
        PrintErrorCode(100);  //then print error code
        return 100;
    }
    string line = "";
    flog << "===== LOAD =====\n"; 
    while(getline(dataFile, line)){   //Read Data from data.txt
        istringstream iss(line);  
        string name = "";
        int age = 0;
        string date = "";
        string cond = "";
		
        if (iss >> name >> age >> date >> cond) {  //using istringstream to read each data
            queuePointer->push(name, age, date, cond);    //Using push function to add Queue
            flog << name << "/" << age << "/" << date << "/" << cond << "\n";    //write to log.txt 
        } else {    // Failed to read the data
            PrintErrorCode(100);
            return 100;
        }
	}
    flog << "=================" << endl << endl;
    dataFile.close();  //close data.txt
    return 1;
}
// ADD
int Manager::ADD(MemberQueue* queuePointer, const string& newName, int newAge, const string& newCollection_day, const string& newCondition)
{
    int result = queuePointer->push(newName, newAge, newCollection_day, newCondition);   //using push function to add Data to queue
    if(result == 200){   //If queue is full or any input has None value
        PrintErrorCode(200);
        return -1;
    }else{     //If success, write to log file
        flog << "===== ADD =====\n"; 
        flog << newName << "/" << newAge << "/" << newCollection_day << "/" << newCondition << "\n";
        flog << "===============" << endl << endl;
        return 1;
    }
}
// QPOP
int Manager::QPOP(MemberQueue* queuePointer, TermsLIST* listPointer, NameBST* nameBSTPointer)
{
    if(queuePointer->empty()){  //If queue is empty, then error
        PrintErrorCode(300);
        return -1;
    }
    while(!queuePointer->empty()){
        MemberQueueNode* poppedNode = queuePointer->pop();   
        if(poppedNode == NULL){   //If poppedNode doesn't exist
            PrintErrorCode(300);   //print error code
            return -1;
        }

        //put into Termslist
        string condition = poppedNode->getCondition();   //extract each condition 
        TermsListNode* listNode = new TermsListNode();   //create each new TermsList Node
        listNode->setCondition(condition);
        listPointer->insert(listNode);

        //Put into TermsBST using TermsList
        TermsBSTNode* termsBSTNode = new TermsBSTNode(poppedNode);      //create each new TermsBST Node
        listPointer->search(condition)->getBSTp()->insert(termsBSTNode);  //using TermsList to get Each TermsBST Pointer and add value
        
        //Put into NameBST
        NameBSTNode* nameBSTNode = new NameBSTNode(poppedNode);    //create each new NameBST Node
        nameBSTPointer->insert(nameBSTNode);
    }
    PrintSuccess("QPOP");
    return 1;
}
// SEARCH
int Manager::SEARCH(NameBST* nameBSTPointer, const string& name){
    NameBSTNode* searchNode = nameBSTPointer->search(name);   //using NameBST's search function
    if(searchNode == NULL){     //if there is none result
        PrintErrorCode(400);
        return -1;
    }else{
        flog << "===== SEARCH =====\n"; 
        flog << searchNode->getNBSTName() << "/" << searchNode->getNBSTAge() << "/" << searchNode->getNBSTCol_Day() << "/" << searchNode->getNBSTEndCol() << "\n";
        flog << "==================" << endl << endl;
    }
}
// PRINT
int Manager::PRINT(const string& keyword, NameBST* newBST, TermsLIST* newLIST){
    if(keyword.length() == 1){   //If we want to search in condition(A,B,C,D)
        TermsListNode* searchNode = newLIST->search(keyword);   //Search From TermsBST
        if(searchNode == NULL){   //If searching value doesn't exists
            PrintErrorCode(500);
            return -1;
        }else{
            flog << "===== PRINT =====\n";
            flog << "Terms_BST " << keyword << "\n";
            searchNode->getBSTp()->printInOrder(flog);     //print result in In order way
            flog << "==================" << endl << endl;
            return 1;
        }
    }else if(keyword == "NAME"){        //If we want to search in Name
        flog << "===== PRINT =====\n";
        flog << "NAME_BST " << keyword << "\n";
        newBST->printInOrder(flog);     //print result in In order way
        flog << "==================" << endl << endl;
        return 1;
    }else{      //No Keyword -> Wrong Command  
        PrintErrorCode(1000);
        return -1;
    }
}

// DELETE 
int Manager::DELETE(const string& deleteTarget, const string& deleteValue, NameBST* bstP, TermsLIST* listP){
    
    if(deleteTarget == "DATE"){  //if Target we delete is DATE
        int cnt = -1;
        TermsListNode* check = listP->getHead();   //to iterate list, get head from list
        if(check == NULL){   //if List has no Value
            PrintErrorCode(600);
            return -1;
        }
        while(check){
            string checkVal = "";
            TermsBST* termsBSTP = check->getBSTp();
            while(checkVal != "NotFound"){
                cnt++;  
                checkVal = termsBSTP->deletebyDate(deleteValue);  //delete from TermsBST
                pair<string, string> result = bstP->deleteByName(checkVal);   //delete from NameBST
                listP->deleteNode(result.second);    //delete from Terms_List 
            }
            check = check->getNext();
        }
        if(cnt == 0){   //No value to delete
            PrintErrorCode(600);
            return -1;
        }
        PrintSuccess("DELETE");
    }else if(deleteTarget == "NAME"){  //if Target we delete is NAME 
        int resultTermsBST, resultTermsList = 0;    
        pair<string, string> resultDel = bstP->deleteByName(deleteValue);   //Delete NameBST         
        resultTermsBST = listP->search(resultDel.second)->getBSTp()->deletebyName(resultDel.first, deleteValue);  //Delete TermsBST
        resultTermsList = listP->deleteNode(resultDel.second);  //Delete TermsList
        if(resultTermsBST == -1 || resultTermsList == -1 || resultDel.first == "NotFound" || resultDel.second == "NotFound"){  //If there is no value to delete
            PrintErrorCode(600);
            return -1;
        }
        PrintSuccess("DELETE");
    }else{  //Wrong Command
        PrintErrorCode(1000);
        return -1;
    }
}

// EXIT
int Manager::EXIT(){
    PrintSuccess("EXIT");
}