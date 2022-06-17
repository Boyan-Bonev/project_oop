#ifndef MYSTRING_H
#define MYSTRING_H

#include <iostream>

class MyString {
    char* m_string;
    int size;
    int capacity;
    bool reserve(int _capacity);
    public:
    MyString();
    MyString(const MyString& other);
    MyString(int cap);
    MyString(char* array);

    char* getString () const {return m_string;}
    int getSize () const {return size;}
    int getCap () const {return capacity;}

    void setSize (int _size) {size = _size;}

    ~MyString() { delete[] m_string; }

    void readString (std::istream& is = std::cin);
    void addTo (const MyString& addition);
    bool removeSubString (const MyString& subString);

    void push_back (char element);
    void pop () { size--;}
    void print () const;

    MyString& operator = (char* source);
    MyString& operator = (const char* source);
    MyString& operator = (const MyString& other);
    friend std::ostream& operator << (std::ostream& os, MyString const& string);
    friend std::istream& operator >> (std::istream& is, MyString& string);

};

#endif