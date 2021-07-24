//Implementation file date

#include <iostream>
#include <ctime>
#include "dateType.h"

using namespace std;

void dateType::setDate(int month, int day, int year)
{
    dMonth = month;
    dDay = day;
    dYear = year;
}

void dateType::setDateToCurrentDate()
{
    int month;
    int day;
    int year;

    time_t currentTime = time(0);
    tm *ltm = localtime(&currentTime);
    month =  1 + ltm->tm_mon;
    day =  ltm->tm_mday;
    year = 1900 + ltm->tm_year;
    dMonth = month;
    dDay = day;
    dYear = year;

}

int dateType::getDay() const
{
    return dDay;
}

int dateType::getMonth() const
{
    return dMonth;
}

int dateType::getYear() const
{
    return dYear;
}

void dateType::printDate() const
{
    cout << dMonth << "-" << dDay << "-" <<dYear;
}

	//constructor with parameter
dateType::dateType(int month, int day, int year)
{
	dMonth = month;
	dDay = day;
	dYear = year;
}
