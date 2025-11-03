#ifndef BANK_H
#define BANK_H

#include "SortedDoublyLinkedList.h"
#include "MultipleQueue.h"
#include "Entities.h"

struct EventResult
{
    EventResult(EventType type = INVALID_EVENT, int customerId = -1, int bankerOrOfficerId = -1, int timePoint = -1);
    EventType type;
    int customerId;
    int bankerOrOfficerId;
    int timePoint;
};

std::ostream& operator<<(std::ostream&, const EventResult& r);

class Bank
{
private:
    MultipleQueue<Customer> waitingQueue;
    SortedDoublyLinkedList<Customer> serviceQueue;
    SortedDoublyLinkedList<Event> eventQueue;

    Banker* bankers;
    SecurityOfficer* securityOfficers;

    int numberOfBankers;
    int numberOfSecurityOfficers;

    int* bankerServiceTimes;
    int* officerDispatchTimes;
    int currentTime;

    int startTime;

public:
    // ---- Constructors & Destructor ----
    Bank(int numBankers,
         const int* bankerServiceTimes,
         int numSecurityOfficers,
         const int* officerDispatchTimes,
         int bankersStartTime);

    ~Bank();

    // ---- Core Functionalities ----
    void AddCustomer(int id, int priority);
    EventResult DoSingleEventIteration();

    friend std::ostream& operator<<(std::ostream& stream, const Bank& b);
};

#endif // BANK_H