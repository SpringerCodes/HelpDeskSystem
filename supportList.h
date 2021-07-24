#ifndef supportList_H
#define supportList_H

#include <iostream>
#include <string.h>
#include "dateType.h"
#include "userType.h"
#include "orderedLinkedList.h"

using namespace std;

class supportList
{
    public:
        // print all the details of the list
        friend ostream& operator<<(ostream&, const supportList&);

        bool operator==(const supportList&) const;
        bool operator>=(const supportList&) const;

        void setCallerInfo(userType callerInfo) { this->callerInfo = callerInfo; }
        void setCallDate(dateType callDate) { this->callDate = callDate; }
        void setProblemDetails(string problemDetails) { this->problemDetails = problemDetails; }
        void setTechInfo(userType techInfo) { this->techInfo = techInfo; }
        void setStatusDate(dateType date) { this->statusDate = date; }
        void setResolutionDetails(string resolutionDetails) { this->resolutionDetails = resolutionDetails; }
        void setCallStatus(string callStatus);

        // prints few details
        void print();

        //string getUserName() { return callerInfo.getUserName(); }
        userType getCallerInfo() { return callerInfo; }
        dateType getCallDate() { return callDate; }
        string getProblemDetails() { return problemDetails; }
        userType getTechInfo() { return techInfo; }
        dateType getStatusDate() { return statusDate; }
        string getCallStatus() { return callStatus; }
        string getResolutionDetails() { return resolutionDetails; }

        supportList();
        // used when from queue
        supportList(supportTicket, userType, dateType, string, string);
        // used when from history.txt
        supportList(userType, dateType, string, userType, dateType, string, string);

    private:
        userType callerInfo;
        dateType callDate;
        string problemDetails;

        userType techInfo;
        string callStatus;          // Assigned/Closed
        dateType statusDate;
        string resolutionDetails;
};

supportList::supportList()
{
    resolutionDetails = "";
    callStatus = "";
}

// From history.txt to linkedlist
supportList::supportList(userType callerInfo, dateType callDate, string problemDetails, userType techInfo, dateType statusDate, string callStatus, string resolutionDetails)
{
    this->callerInfo = callerInfo;
    this->callDate = callDate;
    this->problemDetails = problemDetails;

    this->techInfo = techInfo;
    this->statusDate = statusDate;
    this->resolutionDetails = resolutionDetails;

    setCallStatus(callStatus);
}

// From queue to linkedlist
supportList::supportList(supportTicket assignedTicket, userType techInfo, dateType statusDate, string callStatus, string resolutionDetails)
{
    this->callerInfo = assignedTicket.getUser();
    this->callDate = assignedTicket.getDate();
    this->problemDetails = assignedTicket.getRequest();

    this->techInfo = techInfo;
    this->statusDate = statusDate;
    this->resolutionDetails = resolutionDetails;

    setCallStatus(callStatus);
}

//Validates callStatus
void supportList::setCallStatus(string callStatus)
{
    if(callStatus == "Assigned" || callStatus == "Closed")
        this->callStatus = callStatus;
    else
        this->callStatus = "";
}

// This is used to print out the list
ostream& operator<<(ostream& outStream, const supportList& thisList)
{
    int m,d,y;

    outStream << "--------------------------------------" << endl;
    outStream << "Caller username: " << thisList.callerInfo.getUserName() << endl;
    outStream << "Caller phone #: " << thisList.callerInfo.getPhoneNumber() << endl;

    m = thisList.callDate.getMonth();
    d = thisList.callDate.getDay();
    y = thisList.callDate.getYear();
    outStream << "Call date: " << m << "/" << d << "/" << y << endl;

    outStream << "Problem reported: " << thisList.problemDetails << endl;

    if(thisList.callStatus != "")
    {
        outStream << "Call status: " << thisList.callStatus << endl;

        m = thisList.statusDate.getMonth();
        d = thisList.statusDate.getDay();
        y = thisList.statusDate.getYear();
        outStream << "Status date: " << m << "/" << d << "/" << y << endl;
        outStream << "Tech name: " << thisList.techInfo.getUserName()<< endl;
        outStream << "Tech phone #: " << thisList.techInfo.getPhoneNumber() << endl;
        if(thisList.callStatus == "Closed")
            outStream << "Resolution details: " << thisList.resolutionDetails << endl;
    }

    return outStream;
}

//Prints small details for updating
void supportList::print()
{
    int m,d,y;

    cout << "Caller username: " << callerInfo.getUserName() << endl;
    m = callDate.getMonth();
    d = callDate.getDay();
    y = callDate.getYear();
    cout << "Call date: " << m << "/" << d << "/" << y << endl;
    cout << "Problem reported: " << problemDetails << endl;
    cout << "Call status: " << callStatus << endl;
    cout << "Tech name: " << techInfo.getUserName()<< endl;
}

bool supportList::operator==(const supportList& otherList) const
{
    return (callerInfo.getUserName() == otherList.callerInfo.getUserName());

}

bool supportList::operator>=(const supportList& otherList) const
{
    return (callerInfo.getUserName() >= otherList.callerInfo.getUserName());
}

#endif
