//Header file linkedQueue.h

#ifndef H_linkedQueue
#define H_linkedQueue

#include <iostream>
#include <cassert>
#include "queueADT.h"
#include "supportList.h"
#include "supportTicket.h"

using namespace std;

//Definition of the node
template <class Type>
struct nodeType
{
    Type info;
    nodeType<Type> *link;
};

template <class Type>
class linkedQueueType: public queueADT<Type>
{
public:
    const linkedQueueType<Type>& operator=(const linkedQueueType<Type>&);

    bool isEmptyQueue() const;
    bool isFullQueue() const;
    void initializeQueue();
    Type front() const;
    Type back() const;
    void addQueue(const Type& queueElement);
    void deleteQueue();
    linkedQueueType();  //Default constructor

    linkedQueueType(const linkedQueueType<Type>& otherQueue); //Copy constructor
    ~linkedQueueType(); //Destructor


private:
    nodeType<Type> *queueFront; //pointer to the front of the queue
    nodeType<Type> *queueRear;  //pointer to the rear of the queue
};

    //Default constructor
template <class Type>
linkedQueueType<Type>::linkedQueueType()
{
    queueFront = nullptr;
    queueRear = nullptr;
}

template <class Type>
bool linkedQueueType<Type>::isEmptyQueue() const
{
    return (queueFront == nullptr);
}

template <class Type>
bool linkedQueueType<Type>::isFullQueue() const
{
    return false;
}

template <class Type>
void linkedQueueType<Type>::initializeQueue()
{
    nodeType<Type> *temp;

    while (queueFront!= nullptr)  //while there are elements left in the queue
    {
        temp = queueFront;  //set temp to point to the current node
        queueFront = queueFront->link;  //advance first to the next node
        delete temp;    //deallocate memory occupied by temp
    }

    queueRear = nullptr;  //set rear to nullptr
} //end initializeQueue


template <class Type>
void linkedQueueType<Type>::addQueue(const Type& newElement)
{
    nodeType<Type> *newNode;

    newNode = new nodeType<Type>;   //create the node

    newNode->info = newElement; //store the info
    newNode->link = nullptr;    //initialize the link
                                //field to nullptr

    if (queueFront == nullptr) //if initially the queue is empty
    {
        queueFront = newNode;
        queueRear = newNode;
    }
    else        //add newNode at the end
    {
        queueRear->link = newNode;
        queueRear = queueRear->link;
    }
}//end addQueue

template <class Type>
Type linkedQueueType<Type>::front() const
{
    assert(queueFront != nullptr);
    return queueFront->info;
} //end front

template <class Type>
Type linkedQueueType<Type>::back() const
{
    assert(queueRear!= nullptr);
    return queueRear->info;
} //end back

template <class Type>
void linkedQueueType<Type>::deleteQueue()
{
    nodeType<Type> *temp;

    if (!isEmptyQueue())
    {
        temp = queueFront;  //make temp point to the
                            //first node
        queueFront = queueFront->link; //advance queueFront

        delete temp;    //delete the first node

        if (queueFront == nullptr) //if after deletion the
                                   //queue is empty
            queueRear = nullptr;   //set queueRear to nullptr
    }
    else
        cout << "Cannot remove from an empty queue" << endl;
}//end deleteQueue


    //Destructor
template <class Type>
linkedQueueType<Type>::~linkedQueueType()
{
    deleteQueue();
}

//overload assignment op
template <class Type>
const linkedQueueType<Type>& linkedQueueType<Type>::operator=(const linkedQueueType<Type>& otherQueue)
{
    //TODO
    //Write the definition of to overload the assignment operator

}

	//copy constructor
template <class Type>
linkedQueueType<Type>::linkedQueueType(const linkedQueueType<Type>& otherQueue)
{
    //TODO
    //Write the definition of the copy constructor
}

#endif
