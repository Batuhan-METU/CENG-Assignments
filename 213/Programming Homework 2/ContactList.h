#ifndef CONTACT_LIST_H
#define CONTACT_LIST_H

#include <string>
#include <vector>
#include "TreeMap.h"
#include "KeyValuePair.h"
#include "NoSuchItemException.h"

struct ContactInfo {
    std::vector<std::string> phones;
    std::string email;
    std::string company;
    std::string notes;

    ContactInfo() {}

    ContactInfo(const std::vector<std::string> &p,
                const std::string &e,
                const std::string &c,
                const std::string &n = "")
        : phones(p), email(e), company(c), notes(n) {}
};


class ContactList {

private:
    TreeMap<std::string, ContactInfo> contacts;

public:
    ContactList();
    ~ContactList();

    void addContact(const std::string &name, const ContactInfo &info);
    bool deleteContact(const std::string &name);
    void updateContact(const std::string &name, const ContactInfo &newInfo);
    void addPhone(const std::string &name, const std::string &phone);

    const ContactInfo &getContact(const std::string &name) const;

    void print(); 
    void iterateAlphabetically() ;

};

#endif
