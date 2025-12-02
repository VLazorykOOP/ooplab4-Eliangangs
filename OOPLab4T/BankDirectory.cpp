#include <iostream>
#include <string>
#include <vector>
#include <optional>
using namespace std;

class Person {
private:
    string surname;
    string name;
    string patronymic;
public:
    Person() = default;
    Person(const string& s, const string& n, const string& p)
        : surname(s), name(n), patronymic(p) {}

    friend ostream& operator<<(ostream& os, const Person& p) {
        os << p.surname << " " << p.name << " " << p.patronymic;
        return os;
    }

    friend istream& operator>>(istream& is, Person& p) {
        is >> p.surname >> p.name >> p.patronymic;
        return is;
    }
};

template<typename Key>
class BankDirectory {
private:
    struct Entry {
        Key key;
        Person value;
    };

    vector<Entry> entries;

public:
    int CodeError = 0;

    void add(const Key& key, const Person& person) {
        for (auto& e : entries) {
            if (e.key == key) {
                e.value = person;
                return;
            }
        }
        entries.push_back({key, person});
    }

    Person& operator[](const Key& key) {
        for (auto& e : entries) {
            if (e.key == key) {
                CodeError = 0;
                return e.value;
            }
        }

        CodeError = 1;
        entries.push_back({key, Person()});
        return entries.back().value;
    }

    Person& operator()(const Key& key) {
        return this->operator[](key);
    }

    friend ostream& operator<<(ostream& os, const BankDirectory& dir) {
        for (const auto& e : dir.entries) {
            os << "[" << e.key << "] : " << e.value << "\n";
        }
        return os;
    }

    friend istream& operator>>(istream& is, BankDirectory& dir) {
        size_t n;
        is >> n;
        for (size_t i = 0; i < n; ++i) {
            Key key;
            Person p;
            is >> key;
            is >> p;
            dir.add(key, p);
        }
        return is;
    }
};

int main2() {
    BankDirectory<string> bd;

    bd.add("UA1234567890", Person("Токарюк", "Еліна", "Олексіївна"));
    bd.add("UA0987654321", Person("Іванов", "Іван", "Іванович"));

    cout << bd;

    Person& p1 = bd["UA1234567890"];
    if (bd.CodeError == 0) {
        cout << "Found: " << p1 << "\n";
    } else {
        cout << "Error: key not found\n";
    }

    Person& p2 = bd["NON_EXISTENT"];
    if (bd.CodeError != 0) {
        cout << "Key not found, added default entry.\n";
    }

    Person& p3 = bd("UA0987654321");
    cout << "Accessed: " << p3 << "\n";

    return 0;
}