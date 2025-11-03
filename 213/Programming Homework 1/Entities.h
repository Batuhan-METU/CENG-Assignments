#ifndef ENTITIES_H
#define ENTITIES_H

#include <iostream>

// ======================
// CUSTOMER
// ======================
class Customer
{
    private:
    int id;
    int priorityLevel;
    int serviceTime;
    
    public:
    // Constructors & Destructor
    Customer();
    Customer(int id, int priority, int serviceTime);
    // Accessors
    int getId() const;
    int getPriority() const;
    int getServiceTime() const;
    // Comparison Operators
    bool operator<(const Customer& other) const;
    bool operator==(const Customer& other) const;
    bool operator<(int value) const;
    bool operator==(int value) const;
    Customer& operator=(int value);
    int operator()() const;
    // Mutators
    void setPriority(int priority);
    
    friend std::ostream& operator<<(std::ostream&, const Customer&);
};

// ======================
// EVENT
// ======================
// Represents the type of events that can occur in the bank simulation.
enum EventType {
    ARRIVAL = 0,         // A customer arrives at the bank
    QUEUE_ENTERED,       // A customer enters the queue
    QUEUE_EXITED,        // A customer leaves the queue to join sorted list
    SERVICE_STARTED,     // A banker starts serving the customer
    SERVICE_COMPLETED,   // The service for the customer has finished
    INVALID_EVENT,        // An invalid or undefined event type
    FINISHED              // The simulation has finished
};

class Event
{
private:
    int timePoint;
    EventType type;
    Customer customer;
    int bankerOrOfficerId;

public:
    // ---- Constructors ----
    Event();
    Event(int timePointIn, EventType type, Customer customer, int bankerOrOfficerIdIn);

    // ---- Comparison Operators ----
    bool operator<(const Event& other) const;
    bool operator==(const Event& other) const;
    bool operator<(int value) const;
    bool operator==(int value) const;

    // ---- Accessors ----
    int getTimePoint() const;
    EventType getType() const;
    const Customer& getCustomer() const;
    int getBankerOrOfficerId() const;

    // ---- Mutators ----
    void setPriority(int timePoint);

    friend std::ostream& operator<<(std::ostream&, const Event&);
};

// ======================
// SECURITY OFFICER
// ======================
class SecurityOfficer
{
private:
    int id;  
    int dispatchTime;
    bool busy;

public:
    SecurityOfficer();
    SecurityOfficer(int id, int dispatchTime);
    const int& getId() const;
    const int& getDispatchTime() const;
    bool isBusy() const;
    void setId(int id);
    void setDispatchTime(int dispatchTime);
    void setBusy(bool busy);
};

// ======================
// BANKER
// ======================
class Banker
{
private:
    int id;
    int serviceTime;

public:
    Banker();
    Banker(int id, int serviceTime);
    const int& getId() const;
    const int& getServiceTime() const;
    void setId(int id);
    void setServiceTime(int serviceTime);
};

#endif // ENTITIES_H