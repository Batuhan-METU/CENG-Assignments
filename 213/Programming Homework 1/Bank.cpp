#include "Bank.h"

EventResult::EventResult(EventType type, int customerId, int bankerOrOfficerId, int timePoint)
    : type(type)
    , customerId(customerId)
    , bankerOrOfficerId(bankerOrOfficerId)
    , timePoint(timePoint)
{}

std::ostream& operator<<(std::ostream& s, const EventResult& r)
{
    switch(r.type)
    {
        case ARRIVAL:
            s << "Customer(" << r.customerId
              << ") arrived at the bank." << std::endl;
            break;
        case QUEUE_ENTERED:
            s << "Customer(" << r.customerId
              << ") entered the queue at position " << r.bankerOrOfficerId << "." << std::endl;
            break;
        case QUEUE_EXITED:
            s << "Customer(" << r.customerId
              << ") exited the queue and was dispatched by Officer("
              << r.bankerOrOfficerId << ")." << std::endl;
            break;
        case SERVICE_STARTED:
            s << "Banker(" << r.bankerOrOfficerId
              << ") started serving Customer(" << r.customerId << ")." << std::endl;
            break;
        case SERVICE_COMPLETED:
            s << "Service for Customer(" << r.customerId
              << ") by Banker(" << r.bankerOrOfficerId
              << ") is completed." << std::endl;
            break;
        case INVALID_EVENT:
            s << "Invalid Event!" << std::endl;
            break;
        case FINISHED:
            s << "Simulation has finished." << std::endl;
            break;
    }

    return s;
}

Bank::Bank(int numBankers,
           const int* bankerServiceTimes,
           int numSecurityOfficers,
           const int* officerDispatchTimes,
           int bankersStartTime)
    : waitingQueue(numSecurityOfficers)
    , numberOfBankers(numBankers)
    , numberOfSecurityOfficers(numSecurityOfficers)
    , currentTime(0)
    , startTime(bankersStartTime)
{
    bankers = new Banker[numberOfBankers];
    for (int i = 0; i < numberOfBankers; ++i) {
        bankers[i] = Banker(i, bankerServiceTimes[i]);
        eventQueue.InsertItem(Event(currentTime + startTime, SERVICE_STARTED, Customer(), i));
    }

    securityOfficers = new SecurityOfficer[numberOfSecurityOfficers];
    for (int i = 0; i < numberOfSecurityOfficers; ++i) {
        securityOfficers[i] = SecurityOfficer(i, officerDispatchTimes[i]);
    }

}

Bank::~Bank()
{
    // TODO: Implement
    delete[] bankers; 
    delete[] securityOfficers; 
}

void Bank::AddCustomer(int id, int priority)
{
    // TODO: Implement
    Customer newCustomer(id, priority, -1); 
    eventQueue.InsertItem(Event(currentTime, ARRIVAL, newCustomer, -1)); 
}

EventResult Bank::DoSingleEventIteration()
{
    // TODO: Implement

    if(eventQueue.IsEmpty()) {
        return EventResult(FINISHED, -1, -1, currentTime); 
    }
    Event currentEvent = eventQueue.RemoveFirstItem(); 
    currentTime = currentEvent.getTimePoint(); 

    EventType type = currentEvent.getType();
    Customer customer = currentEvent.getCustomer();
    int officerOrBankerId = currentEvent.getBankerOrOfficerId();


    if (type == ARRIVAL) {
        int queueIndex = waitingQueue.Enqueue(customer); 
        eventQueue.InsertItem(Event(currentTime, QUEUE_ENTERED, customer, queueIndex)); 

        return EventResult(ARRIVAL, customer.getId(), -1, currentTime); 
    }
    else if (type == QUEUE_ENTERED) {
        int officerId = officerOrBankerId; 

        if(!securityOfficers[officerId].isBusy()) {
            securityOfficers[officerId].setBusy(true);
                
            eventQueue.InsertItem(
                Event(currentTime + securityOfficers[officerId].getDispatchTime(),
                      QUEUE_EXITED,
                      customer,
                      officerId)
            );
        }
        return EventResult(QUEUE_ENTERED, customer.getId(), officerId, currentTime); 
    }

    else if (type == QUEUE_EXITED)
    {
        int officerId = officerOrBankerId;

        Customer nextCustomer = waitingQueue.Dequeue(officerId);

        serviceQueue.InsertItem(nextCustomer);

        if (!waitingQueue.GetQueue(officerId).IsEmpty())
        {
            Customer following = waitingQueue.GetQueue(officerId).Front();
            eventQueue.InsertItem(
            Event(currentTime + securityOfficers[officerId].getDispatchTime(),QUEUE_EXITED,following, officerId));
        }
        else {
            securityOfficers[officerId].setBusy(false);
        }

        return EventResult(QUEUE_EXITED, nextCustomer.getId(), officerId, currentTime);
    }
    else if (type == SERVICE_STARTED) {
        int bankerId = officerOrBankerId;

        if (customer.getId() != -1) {
            return EventResult(SERVICE_STARTED, customer.getId(), bankerId, currentTime);
        }

        if (!serviceQueue.IsEmpty()) {
            Customer nextCustomer = serviceQueue.RemoveFirstItem();
            int serviceDuration = bankers[bankerId].getServiceTime() + nextCustomer.getServiceTime();

            eventQueue.InsertItem(Event(currentTime + serviceDuration,SERVICE_COMPLETED, nextCustomer, bankerId));
            return EventResult(SERVICE_STARTED, nextCustomer.getId(), bankerId, currentTime);
        }

        return EventResult(SERVICE_STARTED, -1, bankerId, currentTime);
    }
    else
    {
        int bankerId = officerOrBankerId;

        EventResult result(SERVICE_COMPLETED, customer.getId(), bankerId, currentTime);

        if (!serviceQueue.IsEmpty())
        {
            Customer nextCustomer = serviceQueue.RemoveFirstItem();

            int serviceDuration = bankers[bankerId].getServiceTime() + nextCustomer.getServiceTime();
            eventQueue.InsertItem(Event(currentTime, SERVICE_STARTED, nextCustomer, bankerId)); 
            
            eventQueue.InsertItem(
                Event(currentTime + serviceDuration, SERVICE_COMPLETED, nextCustomer, bankerId)
            );

        }

        return result;
    }


}

std::ostream& operator<<(std::ostream& stream, const Bank& b)
{
    stream << "Bank State at Time " << b.currentTime << ":\n";
    stream << "Waiting Queue:\n" << b.waitingQueue << "\n";
    stream << "Service Queue:" << b.serviceQueue << "\n";
    stream << "Event Queue:" << b.eventQueue << "\n";
    return stream;
}