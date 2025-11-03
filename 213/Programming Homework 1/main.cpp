#include <iostream>
#include "SinglyLinkedList.h"
#include "Queue.h"
#include "MultipleQueue.h"
#include "SortedDoublyLinkedList.h"
#include "Entities.h"
#include "Bank.h"

int main() 
{
    int bankerServiceTimes[3] = {5, 7, 6};
    int officerDispatchTimes[2] = {2, 3};

    Bank bank(3, bankerServiceTimes, 2, officerDispatchTimes, 10);

    bank.AddCustomer(1, 5);
    bank.AddCustomer(2, 3);
    bank.AddCustomer(3, 4);
    bank.AddCustomer(4, 4);
    bank.AddCustomer(5, 2);
    bank.AddCustomer(6, 1);

    while (true) {
        EventResult result = bank.DoSingleEventIteration();
        if(result.type == INVALID_EVENT) {
            break;
        }
        
        else if (result.type == FINISHED) {
            std::cout << result;
            break;
        }
        std::cout << result;
    }

    std::cout << bank;

    return 0;
}