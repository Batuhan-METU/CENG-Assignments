#include "ContactList.h"
#include <iostream>

ContactList::ContactList() {}

ContactList::~ContactList() {}

void ContactList::addContact(const std::string &name, const ContactInfo &info) {
    //TODO
    contacts.put(name, info); 
}

bool ContactList::deleteContact(const std::string &name) {
    //TODO
    return contacts.deletekey(name); 
}

void ContactList::updateContact(const std::string &name, const ContactInfo &newInfo) {
    //TODO
    contacts.update(name, newInfo); 
}

void ContactList::addPhone(const std::string &name, const std::string &phone) {
    //TODO
    ContactInfo &c = const_cast<ContactInfo&>(contacts.get(name)); 
    c.phones.push_back(phone); 
}

const ContactInfo &ContactList::getContact(const std::string &name) const {
    //TODO
    return contacts.get(name); 
}



void ContactList::iterateAlphabetically() {
    try {
        const KeyValuePair<std::string, ContactInfo>* current = &contacts.firstEntry();

        while (true) {

            const std::string& name = current->getKey();
            const ContactInfo& info = current->getValue();

            
            std::cout << "Name: " << name << std::endl;

            std::cout << "Phones: ";
            for (size_t i = 0; i < info.phones.size(); i++) {
                std::cout << info.phones[i] << " ";
            }
            std::cout << std::endl;

            std::cout << "Email: " << info.email << std::endl;
            std::cout << "Company: " << info.company << std::endl;

            if (!info.notes.empty())
                std::cout << "Notes: " << info.notes << std::endl;

            std::cout << std::endl; 

            try {
                std::string keyPlus = name + " ";
                const KeyValuePair<std::string, ContactInfo>& next =
                    contacts.ceilingEntry(keyPlus);
                current = &next;
            }
            catch (const NoSuchItemException&) {
                break;
            }
        }
    }
    catch (const NoSuchItemException&) {
        return;
    }
}

