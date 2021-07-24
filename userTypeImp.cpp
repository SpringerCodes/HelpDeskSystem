#include <string.h>
#include "userType.h"

using namespace std;

userType::userType(string username, string phone)
{
    userName = username;
    phoneNumber = phone;
}

void userType::print() const
{
    cout << "User Name: " << userName << endl;
    cout << "Phone Num: " << phoneNumber << endl;
}
