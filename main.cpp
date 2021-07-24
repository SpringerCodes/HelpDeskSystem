/*
Project Description:
Help-desk Project Title: Help-desk System Description: Project will simulate a help-desk system.
The system will allow adding new support requests, viewing new/open calls, updating support requests,
viewing call history and loading/saving history to file. Data Structures: Project will use a queue for new calls,
and a linked list for call history.
Programming Assignments: Jeff/Chris will design the user interface.
Chris will program the functions associated with the Queue.
Jeff will program the functions associated with the Linked List.
*/


#include <iostream>
#include <fstream>
#include <string>
#include "supportList.h"        // Data Structure inside linkedList
#include "supportTicket.h"      // DS inside queue
#include "queueAsArray.h"

using namespace std;

//  Loads queue.txt into the callQueue
bool buildCallQueue(queueType<supportTicket>& currentCallQueue);
//  Loads history.txt into the callHistory
bool buildCallHistory(orderedLinkedList<supportList>& history);
// Select an assigned call
void searchAndResolve(orderedLinkedList<supportList>& history,string userName);
//  Saves both callQueue and callHistory
void saveData(orderedLinkedList<supportList>& history, queueType<supportTicket>& currentQueue);
//  Shows the Main menu
void showMenu();


int main()
{
    cout << "**********************************************************\n";
    cout << "*               Help Desk Assistant                      *\n";
    cout << "*                                                        *\n";
    cout << "*      Written by: Jeff Fox and Chris Springer           *\n";
    cout << "*                                                        *\n";
    cout << "**********************************************************\n" << endl;


    string userName;
    string phone;
    string request;
    int choice;
    int loc;
    queueType<supportTicket> currentCallQueue;
    orderedLinkedList<supportList> currentCallHistory;


    bool doLoadFilesExist = true;


    //Check to see that queue and list properly load. Program terminates if they are not found.
    doLoadFilesExist = buildCallHistory(currentCallHistory) && buildCallQueue(currentCallQueue);




    if (!doLoadFilesExist)
    {
        cout << "Program terminated!" << endl;
        return 1;
    }


    showMenu();

    cin >> choice;
    cin.ignore(100, '\n');

    while (choice != 9)
    {
        if(!cin)    // reset cin if failed state
        {
            cin.clear();
            cin.ignore(100,'\n');
            choice = 0;
        }

        switch (choice)
        {
        case 1:
            {
            //Create a new support ticket and add to the queue

            //user input section
            cout <<"\nPlease enter the required information." <<endl;
            cout << "Username: ";
            getline(cin, userName);
            cout << "Phone: ";
            getline(cin, phone);
            cout << "Please describe the issue: ";
            getline(cin, request);
            cout << endl;

            //ticket assembly portion
            userType user(userName,phone);
            dateType ticketDate;
            ticketDate.setDateToCurrentDate();
            supportTicket newTicket(user, ticketDate, request);
            currentCallQueue.addQueue(newTicket);

            break;
            }

        case 2:
            //Displays the top unassigned ticket
            if(currentCallQueue.isEmptyQueue())
            {
                cout << "\nThere are no tickets waiting to be assigned.\n" << endl;
            }
            else
            {
                cout << "\n***Next Pending Request***" << endl;
                currentCallQueue.front().printSupportTicket();
                cout <<"--------------------------------------" << endl;
            }

            break;
        case 3:
            {
            //Assign top ticket to a tech

            //Display ticket at the front of the queue
            cout << "\n***Support Ticket Details***" << endl;
            currentCallQueue.front().printSupportTicket();

            //User input for tech info
            string techID;
            cout << "\nAssign a tech to the new ticket" << endl;
            cout << "Tech ID: ";
            cin >> techID;
            cout << "Tech Phone: ";
            cin >> phone;

            //objects needed for ticket assigning
            userType techToBeAssignedTicket(techID,phone);
            dateType statusDate;
            statusDate.setDateToCurrentDate();

            //Insert into call history
            supportList ticketToAssign(currentCallQueue.front(),techToBeAssignedTicket,statusDate,"Assigned","");
            currentCallHistory.insert(ticketToAssign);

            cout << "Ticket has been assigned to tech.\n" << endl;
            currentCallQueue.deleteQueue();
            break;
            }
        case 4:
            {

            //print tickets in history
            cout << endl << "***Call History***" << endl;

            currentCallHistory.print();

            cout << endl << "***End of History***" << endl << endl;

            break;

            }
        case 5:
            {
                cout << endl << "Enter username to look up calls: ";
                getline(cin,userName);

                if(userName != "")
                {
                    searchAndResolve(currentCallHistory,userName);
                }

                break;
            }
        default:
            {
                cout << "Invalid choice" << endl;

                break;
            }
        }
        showMenu();
        cin >> choice;
        cin.ignore(100,'\n');
    }
    saveData(currentCallHistory, currentCallQueue);

    //deallocate memory if allocated
    if(!currentCallQueue.isEmptyQueue())
        currentCallQueue.deleteQueue();
    if(!currentCallHistory.isEmptyList())
        currentCallHistory.destroyList();

    return 0;
}

// Display main menu
void showMenu()
{
    cout << "Choose among the following options:" << endl;
    cout << "1: Enter a new support request" << endl;
    cout << "2: View next unassigned request" << endl;
    cout << "3: Assign next request" << endl;
    cout << "4: View all requests" << endl;
    cout << "5: Update opened request" << endl;
    cout << "9: Save & Exit program" << endl;
}

// searches for userName in the assigned calls and prompts user to add a resolution
void searchAndResolve(orderedLinkedList<supportList>& history,string userName)
{
    string resolution;
    dateType statusDate;
    bool found = false;
    char yn;

    if(!history.isEmptyList())
    {
        cin.clear();
        cout << endl;

        linkedListIterator<supportList> lli = history.begin();
        supportList current = *lli;

        while(lli != nullptr)
        {
            current = *lli;
            if(current.getCallerInfo().getUserName() == userName && current.getCallStatus() == "Assigned")
            {
                current.print();
                cout << "Add resolution and close this call (Y/N)? ";
                cin >> yn;
                cin.ignore(100, '\n');

                if(yn == 'Y' || yn == 'y')
                {
                    found = true;
                    break;
                }
            }

            ++lli;
        }

        if(found)
        {
            history.deleteNode(current);        // Delete the original

            cout << "Enter resolution: ";
            getline(cin,resolution);
            statusDate.setDateToCurrentDate();

            current.setCallStatus("Closed");
            current.setResolutionDetails(resolution);
            current.setStatusDate(statusDate);

            history.insert(current);           // Insert the updated

            cout << "Call is now closed." << endl << endl;
        }
        else
        {
            cout << "No matches found to update." << endl << endl;
        }
    }
}

// Load queue.txt into callQueue
bool buildCallQueue(queueType<supportTicket>& currentCallQueue)
{
    ifstream infile;
    char fileName[50];

    userType user;
    string userName;
    int month;
    int day;
    int year;
    string phone;
    string request;

    infile.open("Queue.txt");
    if (!infile)
    {
        cout << "Input file Queue.txt not found.\nCould not load unassigned support tickets." << endl;
        return false;
    }

    while (infile >> userName >> month >> day >> year)
    {
        infile >> phone;
        infile.ignore(100,'\n');
        getline(infile, request);
        dateType tempDate(month, day, year);
        user.setPhoneNumber(phone);
        user.setUserName(userName);
        supportTicket tempTicket(user, tempDate, request);
        currentCallQueue.addQueue(tempTicket);
    }
    return true;
}

//Reads history.txt into currentCallHistory linkedList
bool buildCallHistory(orderedLinkedList<supportList>& history)
{
    ifstream inFile;
    string filename = {"History.txt"};

    string userName;
    string phoneNumber;
    string problemDetails;
    string techName;
    string callStatus;
    string resolutionDetails;

    int m,d,y;
    bool retValue = false;

    inFile.open(filename);
    if(inFile)
    {
        while (!inFile.eof())
        {
            getline(inFile, userName);
            if(userName != "")
            {
                inFile >> m >> d >> y;
                inFile.ignore(100,'\n');
                dateType callDate(m,d,y);

                getline(inFile, phoneNumber);
                userType userInfo(userName,phoneNumber);
                getline(inFile, problemDetails);
                getline(inFile, techName);
                getline(inFile, phoneNumber);
                userType techInfo(techName,phoneNumber);
                getline(inFile, callStatus);

                inFile >> m >> d >> y;
                inFile.ignore(100,'\n');
                dateType statusDate(m,d,y);

                getline(inFile, resolutionDetails);

                supportList newListItem(userInfo, callDate, problemDetails, techInfo, statusDate, callStatus, resolutionDetails);
                history.insert(newListItem);
            }
        }

        inFile.close();

        retValue = true;
    }
    else
    {
        cout << "Input file: " << filename << " not found.\nCould not load call history database." << endl;
    }

    return retValue;
}

// saves both callQueue and callHistory to files
void saveData(orderedLinkedList<supportList>& history, queueType<supportTicket>& currentQueue)
{
    ofstream myQueueFile;
    ofstream myHistoryFile;
    string fileName;
    dateType date;
    int m,d,y;

    fileName = "Queue.txt";
    myQueueFile.open(fileName);

    while(!currentQueue.isEmptyQueue())
    {
        date = currentQueue.front().getDate();
        m = date.getMonth();
        d = date.getDay();
        y = date.getYear();

        myQueueFile << currentQueue.front().getUser().getUserName() << endl;
        myQueueFile << m << " " << d << " " << y << endl;
        myQueueFile << currentQueue.front().getUser().getPhoneNumber() << endl;
        myQueueFile << currentQueue.front().getRequest() << endl;
        currentQueue.deleteQueue();

    }
    myQueueFile.close();


    if(!history.isEmptyList())
    {
        fileName = "History.txt";
        myHistoryFile.open(fileName);

        linkedListIterator<supportList> lli = history.begin();
        supportList current = *lli;

        while(lli != nullptr)
        {
            current = *lli;

            myHistoryFile << current.getCallerInfo().getUserName() << endl;

            date = current.getCallDate();
            m = date.getMonth();
            d = date.getDay();
            y = date.getYear();
            myHistoryFile << m << " " << d << " " << y << endl;

            myHistoryFile << current.getCallerInfo().getPhoneNumber() << endl;
            myHistoryFile << current.getProblemDetails() << endl;
            myHistoryFile << current.getTechInfo().getUserName() << endl;
            myHistoryFile << current.getTechInfo().getPhoneNumber() << endl;
            myHistoryFile << current.getCallStatus() << endl;

            date = current.getStatusDate();
            m = date.getMonth();
            d = date.getDay();
            y = date.getYear();
            myHistoryFile << m << " " << d << " " << y << endl;

            myHistoryFile << current.getResolutionDetails() << endl;

            ++lli;
        }

        myHistoryFile.close();
    }
}

