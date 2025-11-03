#include "Entities.h"

Customer::Customer()
    : id(-1), priorityLevel(99999), serviceTime(99999)
{}

Customer::Customer(int id, int priority, int serviceTime)
    : id(id), priorityLevel(priority), serviceTime(serviceTime)
{}

int Customer::getId() const {
    return id;
}

int Customer::getPriority() const {
    return priorityLevel;
}

int Customer::getServiceTime() const {
    return serviceTime;
}

bool Customer::operator<(const Customer& other) const {
    return this->priorityLevel < other.priorityLevel;
}

bool Customer::operator==(const Customer& other) const {
    return this->priorityLevel == other.priorityLevel;
}

bool Customer::operator<(int value) const {
    return this->priorityLevel < value;
}

bool Customer::operator==(int value) const {
    return this->priorityLevel == value;
}

Customer& Customer::operator=(int value) {
    this->priorityLevel = value;
    return *this;
}

int Customer::operator()() const {
    return this->priorityLevel;
}

std::ostream& operator<<(std::ostream& os, const Customer& c) {
    os << "[ID:" << c.id
       << " P:" << c.priorityLevel
       << " S:" << c.serviceTime << "]";
    return os;
}

// Converts an EventType value to its corresponding string representation.
const char* EventTypeToString(EventType e)
{
    switch (e)
    {
        case ARRIVAL:          return "ARRIVAL";
        case QUEUE_EXITED:     return "QUEUE_EXITED";
        case SERVICE_STARTED:  return "SERVICE_STARTED";
        case SERVICE_COMPLETED:return "SERVICE_COMPLETED";
        case QUEUE_ENTERED:    return "QUEUE_ENTERED";
        case FINISHED:         return "FINISHED";
        default:               return "INVALID_EVENT";
    }
}

Event::Event()
    : timePoint(-1), type(INVALID_EVENT), customer(Customer()), bankerOrOfficerId(-1)
{}

Event::Event(int timePointIn, EventType typeIn, Customer customerIn, int bankerOrOfficerIdIn)
    : timePoint(timePointIn), type(typeIn), customer(customerIn), bankerOrOfficerId(bankerOrOfficerIdIn)
{}

bool Event::operator<(const Event& other) const {
    return this->timePoint < other.timePoint;
}

bool Event::operator==(const Event& other) const {
    return this->timePoint == other.timePoint;
}

bool Event::operator<(int value) const {
    return this->timePoint < value;
}

bool Event::operator==(int value) const {
    return this->timePoint == value;
}

int Event::getTimePoint() const {
    return timePoint;
}

EventType Event::getType() const {
    return type;
}

const Customer& Event::getCustomer() const {
    return customer;
}

int Event::getBankerOrOfficerId() const {
    return bankerOrOfficerId;
}

void Event::setPriority(int timePoint) {
    this->timePoint = timePoint;
}

std::ostream& operator<<(std::ostream& os, const Event& e) {
    if (e.type == INVALID_EVENT) {
        os << "Event[INVALID]";
        return os;
    }
    os << "Event[Time:" << e.timePoint
       << " Type:" << EventTypeToString(e.type);
    if (e.type == ARRIVAL || e.type == QUEUE_ENTERED || e.type == QUEUE_EXITED || e.type == SERVICE_COMPLETED) {
        os << " CustomerID:" << e.customer.getId();
    }
    if (e.type == SERVICE_STARTED || e.type == SERVICE_COMPLETED) {
        os << " BankerID:" << e.bankerOrOfficerId;
    }
    else if (e.type == QUEUE_EXITED || e.type == QUEUE_ENTERED) {
        os << " OfficerID:" << e.bankerOrOfficerId;
    }
    
    os << "]";
    return os;
}

SecurityOfficer::SecurityOfficer()
    : id(0), dispatchTime(1), busy(false)
{}

SecurityOfficer::SecurityOfficer(int id, int dispatchTime)
    : id(id), dispatchTime(dispatchTime), busy(false)
{}

const int& SecurityOfficer::getId() const{ 
    return id;
}

const int& SecurityOfficer::getDispatchTime() const {
    return dispatchTime;
}

bool SecurityOfficer::isBusy() const {
    return busy;
}

void SecurityOfficer::setId(int id) {
    this->id = id;
}

void SecurityOfficer::setDispatchTime(int dispatchTime) {
    this->dispatchTime = dispatchTime;
}

void SecurityOfficer::setBusy(bool busy) {
    this->busy = busy;
}

Banker::Banker()
    : id(0), serviceTime(1)
{}

Banker::Banker(int id, int serviceTime)
    : id(id), serviceTime(serviceTime)
{}

const int& Banker::getId() const {
    return id;
}

const int& Banker::getServiceTime() const {
    return serviceTime;
}

void Banker::setId(int id) {
    this->id = id;
}

void Banker::setServiceTime(int serviceTime) {
    this->serviceTime = serviceTime;
}
