#include <iostream>
#include <queue>
#include "Queue-1.h"

using namespace std;

int const MAX_RUNNABLE_JOBS = 3;

struct Job
{
    int jobID;
    int timeRemaining;

    Job() : jobID(0), timeRemaining(0) {}

    Job(int jobId, int remainingTime) : jobID(jobId), timeRemaining(remainingTime) {}

    int getId()
    {
        return jobID;
    }

    int getTimeRemaining()
    {
        return timeRemaining;
    }
};

std::ostream& operator<<(std::ostream& os, const Job& job)
{
    os << "Job ID: " << job.jobID << ", Time Remaining: " << job.timeRemaining;
    return os;
}

int main()
{
    MySpace::DataStructs::MyQueue<Job> runnableQueue;
    MySpace::DataStructs::MyQueue<Job> sleepingQueue;
    //MySpace::DataStructs::MyQueue<Job> job;


    while (true)
    {
        int switchChoice;

        cout << "Enter one of the following options" << endl;
        cout << "1 - create job and add to \"Runnable\" queue" << endl;
        cout << "2 - display \"Runnable\" queue" << endl;
        cout << "3 - execute job at front of queue" << endl << endl;

        cout << "4 - display \"Sleeping\" queue" << endl;
        cout << "5 - move job from \"Sleeping\" to \"Runnable\" queue" << endl;
        cout << "6 - To exit." << endl;

        cin >> switchChoice;

        int jobId;
        int timeRemaining;

        switch (switchChoice)
        {
        case 1:

            cout << "Enter Job ID: ";
            cin >> jobId;

            cout << "Enter Time Remaining: ";
            cin >> timeRemaining;

            {

                Job job{ jobId, timeRemaining };

                if (runnableQueue.size() > MAX_RUNNABLE_JOBS)
                {
                    runnableQueue.enqueue(job);
                }
                else
                {
                    sleepingQueue.enqueue(job);
                }
            }
            cout << endl << endl;
            break;
        case 2:
            runnableQueue.printQueue();
            cout << endl << endl;
            break;
        case 3:
            if (!runnableQueue.isEmpty())
            {
                cout << "Executing job with ID: " << runnableQueue.front().getId() << endl;
                runnableQueue.dequeue();
                cout << endl << endl;
            }
            else
            {
                cout << "ERROR -  there are no jobs in the \"Runnable Queue\"" << endl;
            }
            break;
        case 4:
            sleepingQueue.printQueue();
            cout << endl << endl;
            break;
        case 5:
            if (runnableQueue.size() >= MAX_RUNNABLE_JOBS)
            {
                cout << "ERROR - Insufficient memory in \"Runnable\" queue." << endl;
            }
            else
            {
                if (!sleepingQueue.isEmpty())
                {
                    Job jobToMove = sleepingQueue.front();
                    sleepingQueue.dequeue();
                    runnableQueue.enqueue(jobToMove);
                    cout << endl << endl;
                }
                else
                {
                    cout << "No job to move from sleeping queue to runnable queue." << endl << endl;
                }
            }
            break;
        case 6:
            return 0;
        default:
            cout << "Invalid Choice! Please select 1-5." << endl;
        }

        
    }
}
