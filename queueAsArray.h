//Header file QueueAsArray

#ifndef H_QueueAsArray
#define H_QueueAsArray

#include <iostream>
#include <cassert>

#include "queueADT.h"

using namespace std;

template <class Type>
class queueType: public queueADT<Type>
{
public:
    const queueType<Type>& operator=(const queueType<Type>&);
      //Overload the assignment operator.

    bool isEmptyQueue() const;

    bool isFullQueue() const;

    void initializeQueue();

    Type front() const;

    Type back() const;

    void addQueue(const Type& queueElement);

    void deleteQueue();

    void saveQueue(Type& queueElement, ofstream file);

    queueType(int queueSize = 100);

    queueType(const queueType<Type>& otherQueue);

    ~queueType();

private:
    int maxQueueSize; //variable to store the maximum queue size
    int count;        //variable to store the number of
                      //elements in the queue
    int queueFront;   //variable to point to the first
                      //element of the queue
    int queueRear;    //variable to point to the last
                      //element of the queue
    Type *list;       //pointer to the array that holds
                      //the queue elements
};

template <class Type>
bool queueType<Type>::isEmptyQueue() const
{
    return (count == 0);
} //end isEmptyQueue

template <class Type>
bool queueType<Type>::isFullQueue() const
{
    return (count == maxQueueSize);
} //end isFullQueue

template <class Type>
void queueType<Type>::initializeQueue()
{
    queueFront = 0;
    queueRear = maxQueueSize - 1;
    count = 0;
} //end initializeQueue

template <class Type>
Type queueType<Type>::front() const
{
    assert(!isEmptyQueue());
    return list[queueFront];
} //end front

template <class Type>
Type queueType<Type>::back() const
{
    assert(!isEmptyQueue());
    return list[queueRear];
} //end back

template <class Type>
void queueType<Type>::addQueue(const Type& newElement)
{
    if (!isFullQueue())
    {
        queueRear = (queueRear + 1) % maxQueueSize; //use mod
                            //operator to advance queueRear
                            //because the array is circular
        count++;
        list[queueRear] = newElement;
    }
    else
        cout << "Cannot add to a full queue." << endl;
} //end addQueue

template <class Type>
void queueType<Type>::deleteQueue()
{
    if (!isEmptyQueue())
    {
        count--;
        queueFront = (queueFront + 1) % maxQueueSize; //use the
                        //mod operator to advance queueFront
                        //because the array is circular
    }
    else
        cout << "Cannot remove from an empty queue." << endl;
} //end deleteQueue


    //Constructor
template <class Type>
queueType<Type>::queueType(int queueSize)
{
    if (queueSize <= 0)
    {
        cout << "Size of the array to hold the queue must "
             << "be positive." << endl;
        cout << "Creating an array of size 100." << endl;

        maxQueueSize = 100;
    }
    else
        maxQueueSize = queueSize;   //set maxQueueSize to
                                    //queueSize

    queueFront = 0;                 //initialize queueFront
    queueRear = maxQueueSize - 1;   //initialize queueRear
    count = 0;
    list = new Type[maxQueueSize];  //create the array to
                                    //hold the queue elements
} //end constructor

    //Destructor
template <class Type>
queueType<Type>::~queueType()
{
    delete [] list;
} //end destructor

template <class Type>
const queueType<Type>& queueType<Type>::operator=(const queueType<Type>& otherQueue)
{
    if (this != &otherQueue)
    {

       queueFront = otherQueue.queueFront;
       queueRear = otherQueue.queueRear;

       count = otherQueue.count;
       maxQueueSize = otherQueue.maxQueueSize;

       delete [] list;
       list = new Type[otherQueue.maxQueueSize];
       assert(list != NULL);

       if (count != 0)
        for (int i = queueFront; i <= queueRear; i = (i + 1) % maxQueueSize)
          list[i] = otherQueue.list[i];
    }
} //end assignment operator

template <class Type>
queueType<Type>::queueType(const queueType<Type>& otherQueue)
{
    queueFront = otherQueue.queueFront;
    queueRear = otherQueue.queueRear;
    count = otherQueue.count;
    maxQueueSize = otherQueue.maxQueueSize;

    list = new Type[otherQueue.maxQueueSize];
    assert(list != NULL);

    for (int i = queueFront; i <= queueRear; i = (i + 1) % maxQueueSize)
        list[i] = otherQueue.list[i];
} //end copy constructor

#endif
