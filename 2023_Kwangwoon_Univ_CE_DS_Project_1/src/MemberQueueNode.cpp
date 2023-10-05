#include "MemberQueueNode.h"
#include <iostream>
#include <string>
#include <cstdio>  //in order to use sscanf func
#include <iomanip>   //in order to use setfill
#include <sstream>    //in order to change end condition date to string
using namespace std;

void MemberQueueNode::setName(const string& newName){   //to set Node's name value
	name = newName;
}

void MemberQueueNode::setAge(const int& newAge){	//to set Node's age value
	age = newAge;
}

void MemberQueueNode::setCollection(const string& newCollection_day){	//to set Node's collection_day value
	collection_day = newCollection_day;
}

void MemberQueueNode::setCondition(const string& newCondition){		//to set Node's condition value
	condition = newCondition;
}

const string MemberQueueNode::getName(){      //to get Node's Name value
	return name;
}

int MemberQueueNode::getAge(){			//to get Node's Age value
	return age;
}

const string MemberQueueNode::getCollection(){			//to get Node's Collection_day value
	return collection_day;
}

const string MemberQueueNode::getCondition(){			//to get Node's Condition value
	return condition;
}

const string MemberQueueNode::getEndCol(){      //To make end of Collection day using Collection_day, Condition value
	string currCol = this->getCollection();
	string currCon = this->getCondition();
	
	int currYear, currMonth, currDay = 0;
	
	sscanf(currCol.c_str(), "%4d-%02d-%02d", &currYear, &currMonth, &currDay);   //using sscanf to change string value into integer value
	ostringstream oss;

	if(currCon == "A"){
		if(currMonth <= 6){     
			currMonth += 6;
		}else{				//if current Month is Over 6, then we need to decrease 6 month and increase year value
			currMonth -= 6;
			currYear += 1;
		}

	}else if(currCon == "B"){
		currYear += 1;
	}else if(currCon == "C"){
		currYear += 2;
	}else if(currCon == "D"){
		currYear += 3; 
	}else {
		return "Wrong Value\n";
	}
    int daysInMonth[] = {0, 31, 28, 31, 30, 31, 30, 31, 31, 30, 31, 30, 31};    //calculate each month's day number

    if ((currYear % 4 == 0 && currYear % 100 != 0) || (currYear % 400 == 0)) {    //If it is a leap year, change the number of days in February to 29
        daysInMonth[2] = 29;
    }

    while (currDay > daysInMonth[currMonth]) {   // Handle if the number of days exceeds the number of days in the month
        currDay -= daysInMonth[currMonth];
        currMonth++;
        if (currMonth > 12) {
            currMonth -= 12;
            currYear++;
        }
    }

	oss << currYear << "-" << setfill('0') << setw(2) << currMonth << "-" << setfill('0') << setw(2) << currDay;   //using ostringstream to formalize the End of Collection Day 
	string newDay = oss.str();      //using str() function to change oss stream value into string value
	return newDay;    
}