#ifndef EXCEPTION_H
#define EXCEPTION_H

#include <iostream>
#include <exception>
#include <string>

class EmptyCollectionException : public std::exception {
public:
    EmptyCollectionException() : message("Collection is empty") {}
    virtual ~EmptyCollectionException() throw() {} 

    virtual const char* what() const throw() {
        return message.c_str();
    }

private:
    std::string message;
};

class IndexOutOfRangeException : public std::exception {
public:
    IndexOutOfRangeException() : message("Index is out of range") {}
    virtual ~IndexOutOfRangeException() throw() {} 

    virtual const char* what() const throw() {
        return message.c_str();
    }

private:
    std::string message;
};

class NotFoundException : public std::exception {
public:
    NotFoundException() : message("Item is not found") {}
    virtual ~NotFoundException() throw() {} 

    virtual const char* what() const throw() {
        return message.c_str();
    }

private:
    std::string message;
};

#endif // EXCEPTION_H