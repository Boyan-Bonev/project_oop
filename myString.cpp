#include <iostream>
#include <cstring>

const size_t DEF_CAP_STRING = 4;

class MyString {
    char* m_string;
    int size;
    int capacity;

    public:

    char* getString () const {return m_string;}
    int getSize () const {return size;}
    int getCap () const {return capacity;}

    void setSize (int _size) {size = _size;}

    // Big Four 
    // MyString()
    MyString() {
        capacity = DEF_CAP_STRING;
        size = 0;
        m_string = new char[DEF_CAP_STRING];
    }
    // MyString(const MyString& other)
    MyString(const MyString& other) {
        size = other.getSize();
        capacity = other.getCap();
        m_string = new char [other.getSize() + 1];
        strcpy(m_string,other.getString());
    }
    // MyString& operator = (const MyString& other)
    MyString& operator = (const MyString& other) {
        if (this != &other) {
            delete[] m_string;
            size = other.getSize();
            capacity = other.getCap();
            m_string = new char [other.getSize() + 1];
            strcpy(m_string,other.getString());
        }
        return *this;
    }
    // ~MyString
    ~MyString() {
        delete[] m_string;
    }

    // define by capacity   !!MUST CHECK WHEN USED IF IS EMPTY
    //                        AND POINTING AT RANDOM DATA 
    MyString(int cap) {
        if (cap > DEF_CAP_STRING) {
            size = 0;
            capacity = cap;
            m_string = new char [cap];
            if (!m_string) {
                std::cerr << "Failed to allocate memory!";
            }
        }
        else { 
            std::cerr << "Base/Lowest capacity is 4!";
            size = 0;
            capacity = DEF_CAP_STRING;
            m_string = new char [DEF_CAP_STRING];
        }
    }

    MyString(char* array) {
        capacity = strlen(array) + 1;
        size = strlen(array);
        m_string = new char [capacity];
        strcpy_s (m_string, capacity, array);
    }

    bool reserve(int _capacity) {
        if (_capacity > capacity) {
            char* newVector = new char [_capacity];
            if (newVector == nullptr) {
                return false;
            }
            for (int i = 0; i < size; i++) {
                newVector[i] = m_string[i];
            }
            newVector[size] = '\0';
            delete[] m_string;
            m_string = newVector;
            capacity= _capacity;
        }
        return true;
    }

    void readString (std::istream& is = std::cin) {
        char c;
        do {
            is.get(c);
            if (c != '\n' && c!= '\0' && c!= '|') {
            push_back(c);
            }
        }
        while (c != '\n' && c!= '\0' && c!= '|');
        push_back('\0');  
    }

    void addTo (const MyString& addition) {
        int biggerCap = 0;
        capacity > addition.getCap() ?   biggerCap = capacity : // true
                                    biggerCap = addition.getCap(); // false
        if (size + addition.getSize() >= capacity) {
            MyString newStr(2*biggerCap);
            strcpy(newStr.getString(),m_string);
            strcpy(&((newStr.getString())[size]), addition.getString());
            delete[] m_string;
            m_string = newStr.getString();

        }
        else {
            strcpy(&(m_string[size]), addition.getString());
        }
    }

    void push_back (char element) {
        if (size + 1 + 1 >= capacity) {
            if (!reserve(2*capacity)) {
                std::cerr << "Failed to Allocate new memory!";
            }
        }
        if (element != '\0') {
        m_string[size++] = element;
        m_string[size] = '\0';
        }
        else {
            m_string[size] = '\0';
        }

    }

    void pop () { size--;}

    void print () const {
        for (int i = 0; i < size; i++) {
            std::cout << m_string[i];
        }
    }

    bool removeSubString (const MyString& subString) {
        int lenOfRemoved = strlen (subString.getString());
        char* firstOcc = strstr(m_string,subString.getString());
        char* newStr = new char [size - lenOfRemoved + 1 ];
        int i = 0, j = 0;

        if (firstOcc) {
            for (i; &(m_string[i]) != firstOcc; i++) {
                newStr[i] = m_string[i];
            }
            j = i + lenOfRemoved;
            for (j; m_string[j] != '\0'; j++) {
                newStr[i++] = m_string[j];
            }
            newStr[i] = '\0';
            delete[] m_string;
            m_string = newStr;
            return true;
        }
        else return false;
    }

    MyString& operator = (char* source) {
        if (strcmp(m_string, source)) {
            delete[] m_string;
            size = strlen(source);
            capacity = strlen(source) + 1;
            m_string = new char [strlen(source) + 1];
            strcpy(m_string,source);
        }
        return *this;
    }

    MyString& operator = (const char* source) {
        if (strcmp(m_string, source)) {
            delete[] m_string;
            size = strlen(source);
            capacity = strlen(source) + 1;
            m_string = new char [strlen(source) + 1];
            strcpy(m_string,source);
        }
        return *this;
    }

};
    std::ostream& operator << (std::ostream& os, MyString const& string) {
        return os << string.getString();
    }

    std::istream& operator >> (std::istream& is, MyString& string) {
        char c;
        do {
            is.get(c);
            if (c != '\n' && c!= '\0' && c!= '|') {
            string.push_back(c);
            }
        }
        while (c != '\n' && c!= '\0' && c!= '|');
        string.push_back('\0'); 
        return is;
    }


