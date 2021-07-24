#ifndef userType_H
#define userType_H

#include <iostream>

using namespace std;


class userType
{
    public:
        void print() const;

        string getPhoneNumber() const
            { return phoneNumber; }
        void setPhoneNumber(string phone)
            { phoneNumber = phone; }
        string getUserName() const
            { return userName; }
        void setUserName(string username)
            { userName = username; }

        userType(string username = "", string phone = "");

    private:
        string userName;
        string phoneNumber;
};


#endif
