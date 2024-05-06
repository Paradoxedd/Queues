#pragma once

#include <iostream>
#include<cassert>

#include<queue> //for `merge` method at bottom

using std::queue;

using std::cout;
using std::cin;
using std::endl;
using std::string;



namespace MySpace
{
    namespace DataStructs
    {

        template <typename T>
        class QueueADT
        {
        public:
            virtual bool isEmpty() = 0;
            virtual bool isFull() = 0;


            virtual T& front() = 0;
            virtual T& back() = 0;

            virtual void enqueue(const T& newValue) = 0;
            virtual void dequeue() = 0;
        };

        template <typename T>
        struct Node
        {
            T info;
            Node<T>* link;
        };



        /// <summary>
        /// Implements a queue using nodes
        /// </summary>
        /// <typeparam name="T"></typeparam>
        template <typename T>
        class MyQueue : public QueueADT<T>
        {
        private:
            Node<T>* queueFront;
            Node<T>* queueBack; //add nodeCount?
            int nodeCount;

        public:
            MyQueue()
            {
                queueFront = nullptr;
                queueBack = nullptr;
                nodeCount = 0;
            }

            //delete the copy constructor: 
            //(don't let user copy queue objects)
            //MyQueue(const MyQueue<T>& otherQueue) = delete;
            //Now MSVC compiler error 2280 occurs

            //Alternative - deep copy
            MyQueue(const MyQueue<T>& otherQueue)
            {
                //cout << "copy constructor called" << endl; 
                queueFront = nullptr;
                queueBack = nullptr;
                nodeCount = 0; //updated by `enqueue` below 

                Node<T>* current = otherQueue.queueFront;
                while (current != nullptr)
                {
                    enqueue(current->info);
                    //enqueue uses `new`
                    //default copy constructor uses:
                    //this->link = otherQueue->link
                    current = current->link;
                }
            }

            //allow use of initializer list
            MyQueue(std::initializer_list<T> initList)
            {
                //int i = 0; 
                for (auto& element : initList)
                {
                    this->enqueue(element);
                }
            }

            //DELETING (disallowing) copy assignment: 
            //MyQueue<T>& operator = (const MyQueue<T> otherQueue) = delete;
            //OR:
            MyQueue<T>& operator = (const MyQueue<T> otherQueue)
            {
                //goofy repeat of copy constructor def (except use of return):
                queueFront = nullptr;
                queueBack = nullptr;
                nodeCount = 0; //updated by `enqueue` below 

                Node<T>* current = otherQueue.queueFront;
                while (current != nullptr)
                {
                    enqueue(current->info);
                    //enqueue uses `new`
                    //default copy constructor uses:
                    //this->link = otherQueue->link
                    current = current->link;
                }

                return *this;
            }

            bool isEmpty()
            {
                return (queueFront == nullptr);
            }

            bool isFull()
            {
                return false;
                //add capacity as member var, if desired 
                //required if making queue from static array
            }

            T& front()
            {
                return queueFront->info;
            }

            T& back()
            {
                return queueBack->info;
            }

            int size() { return nodeCount; }

            /// <summary>
            /// Inserts node at BACK of queue (FIFO) 
            /// </summary>
            void enqueue(const T& newValue)
            {
                Node<T>* newNode = new Node<T>;

                newNode->info = newValue;

                newNode->link = nullptr;

                //enqueue def continues next slides

                if (isEmpty()) //true if inserting first queue element
                {
                    queueFront = newNode;
                    queueBack = newNode;
                }

                else
                {
                    queueBack->link = newNode;
                    queueBack = queueBack->link;
                }

                nodeCount++;
            }

            void dequeue()
            {
                assert(!isEmpty());

                Node<T>* temp = queueFront;

                queueFront = queueFront->link;

                delete temp;

                nodeCount--;
            }

            void printQueue()
            {
                Node<T>* current = new Node<T>;
                current = queueFront;



                for (int i = 0; i < nodeCount; i++)
                {
                    cout << current->info << endl;
                    current = current->link;
                }

            }

            //interesting pointer transposition runtime error
            //MyQueue<T> mergeQueues(MyQueue<T> secondQueue)
            //{
            //	MyQueue<T> mergedQueue;

            //	while (!(this->isEmpty() && secondQueue.isEmpty()))
            //	{
            //		if (!this->isEmpty())
            //		{
            //			mergedQueue.enqueue(this->front());
            //			this->dequeue();
            //		}

            //		if (!secondQueue.isEmpty())
            //		{
            //			mergedQueue.enqueue(secondQueue.front());
            //			secondQueue.dequeue();
            //		}
            //	}

            //	return mergedQueue;
            //}

            /// <summary>
            /// Assumes not an empty queue
            /// </summary>
            //~MyQueue()	//contains BUG at the moment 
            //{
            //	cout << "Calling destructor: " << endl; 

            //	Node<T>* current = queueFront;

            //	while (!isEmpty())
            //	{
            //		queueFront = queueFront->link;
            //		delete current;
            //	}

            //	queueBack = nullptr; 

            //	cout << "Done with deallocation - no memory leaks?" << endl; 
            //}
        };

        /// <summary>
        /// NOTE the use of std::queue
        /// </summary>
        /// <typeparam name="T"></typeparam>
        /// <param name="firstQueue"></param>
        /// <param name="secondQueue"></param>
        /// <returns></returns>
        template<typename T>
        queue<T> mergeQueues(queue<T> firstQueue, queue<T> secondQueue)
        {
            queue<T> mergedQueue;

            while (!(firstQueue.empty() && secondQueue.empty()))
            {
                if (!firstQueue.empty())
                {
                    mergedQueue.push(firstQueue.front());
                    firstQueue.pop();
                }

                if (!secondQueue.empty())
                {
                    mergedQueue.push(secondQueue.front());
                    secondQueue.pop();
                }
            } //end while

            return mergedQueue;
        }
    }
}
