// supportTicket is the data structure inside the queue

#ifndef supportTicket_H
#define supportTicket_H

#include <iostream>
#include <string.h>
#include "dateType.h"
#include "userType.h"
#include "linkedList.h"

using namespace std;

class supportTicket
{
    public:

        supportTicket();
        supportTicket(userType user, dateType date, string request);

        userType getUser() const;
        dateType getDate();
        string getRequest();
        void setRequest(string newRequest);
        void printSupportTicket();

        bool operator==(const supportTicket&) const;
        bool operator>=(const supportTicket&) const;
        ~supportTicket();


    private:
        userType user;
        dateType date;
        string request;

};

supportTicket::supportTicket()
{
    //sets date to today's date by default.
    dateType newDate;
    newDate.setDateToCurrentDate();
    date = newDate;

    request = "";

}
supportTicket::supportTicket(userType user,dateType date, string request)
{
    this->user = user;
    this->date = date;
    this->request = request;
}

string supportTicket::getRequest(){ return request;}
dateType supportTicket::getDate(){return date;}
userType supportTicket::getUser() const {return user;}


void supportTicket::setRequest(string newRequest) {
    request = newRequest;
}

void supportTicket::printSupportTicket(){

    cout << "Username: " << user.getUserName() << endl;
    cout << "Date: ";
    date.printDate();
    cout << "\nPhone: " << user.getPhoneNumber() << endl;
    cout << "Request: " << request << endl << endl;
}

bool supportTicket::operator==(const supportTicket& otherTicket) const
{
    return (getUser().getUserName() == otherTicket.getUser().getUserName());
}

bool supportTicket::operator>=(const supportTicket& otherTicket) const
{
    return (user.getUserName() >= otherTicket.getUser().getUserName());
}

supportTicket::~supportTicket()
{
}


#endif
