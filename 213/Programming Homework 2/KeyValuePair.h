#ifndef KEYVALUEPAIR_H
#define KEYVALUEPAIR_H

// DO NOT CHANGE THIS FILE.
#include <sstream>
#include <vector>
#include <string>
#include <ostream>


template<class K, class V>
class KeyValuePair {
public:
    KeyValuePair() {}

    KeyValuePair(const K &key) {
        this->key = key;
    }

    KeyValuePair(const K &key, const V &value) {
        this->key = key;
        this->value = value;
    }

    bool operator<(const KeyValuePair &rhs) const {
        return key < rhs.key;
    }

    bool operator>(const KeyValuePair &rhs) const {
        return rhs < *this;
    }

    bool operator<=(const KeyValuePair &rhs) const {
        return !(rhs < *this);
    }

    bool operator>=(const KeyValuePair &rhs) const {
        return !(*this < rhs);
    }

    bool operator==(const KeyValuePair &rhs) const {
        return key == rhs.key;
    }

    bool operator!=(const KeyValuePair &rhs) const {
        return !(rhs == *this);
    }

    const K &getKey() const {
        return key;
    }

    const V &getValue() const  {
        return value;
    }

    void setValue(const V &value) {
        this->value = value;
    }

    friend std::ostream &operator<<(std::ostream &os, const KeyValuePair &pair) {
        os << "KeyValuePair(key: " << toString(pair.key)
           << ", value: " << toString(pair.value) << ")";
        return os;
    }

private:
    K key;
    V value;

// Generic fallback for other types
    template<typename T>
    static std::string toString(const T &item) {
        std::ostringstream oss;
        oss << item;
        return oss.str();
    }

// Specialization for std::vector<T>
    template<typename T>
    static std::string toString(const std::vector<T> &vec) {
        std::ostringstream oss;
        oss << "[";

        for (size_t i = 0; i < vec.size(); ++i) {
            oss << toString(vec[i]);
            if (i != vec.size() - 1) {
                oss << ", ";  // Separate elements with a comma
            }
        }

        oss << "]";
        return oss.str();
    }

// Special case: string MUST be printed with quotes!
static std::string toString(const std::string &s) {
    return "\"" + s + "\"";
}
};

#endif //KEYVALUEPAIR_H
