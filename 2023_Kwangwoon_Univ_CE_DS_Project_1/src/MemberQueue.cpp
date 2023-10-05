#include "MemberQueue.h"
#include <string>
using namespace std;

MemberQueue::MemberQueue()    //constructor
{
    start = nullptr;      //initialize start, rear, cnt
    rear = nullptr;
	cnt = 0;
}
MemberQueue::~MemberQueue()   //destructor
{
	while(start){    //using while loop to delete Queue
        MemberQueueNode* temp = start;
        start = start->next;
        delete temp; 
    }
}

bool MemberQueue::empty()    //if start has nullptr, means empty
{
    return start == nullptr;
}
bool MemberQueue::full()   //if cnt has 100, means full
{
    return cnt == 100;
}
int MemberQueue::push(const string& newName, int newAge, const string& newCollection_day, const string& newCondition)
{
	if(full()){   //if queue is full, then return 200 to make Error
        return 200;
    } 
    if(newName == "" || newCollection_day == "" || newCondition == ""){   //if given value is NULL, then also return 200
        return 200;
    }
    MemberQueueNode* newNode = new MemberQueueNode(newName, newAge, newCollection_day, newCondition);   //create new MemberQueueNode instance with given value
    cnt++;   //since it is push, increase count
    if(empty()){  //if queue is empty 
        start = rear = newNode;     //then make pushed value to start, rear
    } else {     
        rear->next = newNode;   //Add new Node to rear
        rear = newNode;
    }
    return 1;
}
MemberQueueNode* MemberQueue::pop()
{
    if(empty()){   //if queue is empty, then there is no value to pop
        return nullptr;
    }else{
        MemberQueueNode* popNode = start;   //since we need to pop from front, we need to change start, start->next value
        start = start->next; 
        if(!start){
            rear = nullptr;  //if queue is empty, also initialize rear
        }
        cnt--;    //decrease count
        return popNode;
    }
}
MemberQueueNode* MemberQueue::front()
{
    return start;    //return start
}

