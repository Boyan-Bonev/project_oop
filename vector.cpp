#include <iostream>
const size_t DEF_CAP = 4;

class Vector {
    int size; // current amount
    int capacity; // max amount
    int* array;

    void copy(const Vector& other) {
        size = other.size;
        capacity = other.capacity;
        array = new int[capacity];
        for (int i = 0; i < size; i++) {
            array[i] = other.array[i];
        }
    }
    void clear() {
        delete[] array;
        array = nullptr;
        size = 0;
        capacity = 0;
    }
    public:

    // Big Four
    Vector() {
        size = 0;
        capacity = DEF_CAP;
        array = new int [capacity];
    }

    Vector (const Vector& other) {
        copy(other);
    }

    Vector& operator= (const Vector& other) {
        if (this != &other) {
            clear();
            copy(other);
        }
        return *this;
    }
    ~Vector() {
        clear();
    }
    // End

    Vector(int cap) {
        capacity = cap;
        array = new int [capacity];
        size = 0;
    }

    Vector(int _size, int* _array) {
        size = _size;
        capacity = size;
        array = new int [capacity];
        for (int i = 0; i < size; i++) {
            array[i] = _array[i];
        }
    }

    void readVector (std::istream& is = std::cin) {
        char c;
        do {
            std::cout << "HEY";
            is >> c;
            if ( c >= '0' && c <= '9') {
            push_back((int)c);
            }
        }
        while ( c != '\0' && c != '\n' );
    }

    int getSize() {return size;}
    int getCapacity() {return capacity;}
    int at(int index) {return array[index];}

    void setVector (int _size, int* _array) {
        size = _size;
        if (capacity < size) {
            reserve(2*capacity);
        }
        for (int i = 0; i < size; i++) {
            array[i] = _array[i];
        }
    }

    bool reserve(int _capacity) {
        if (_capacity > capacity) {
            int* newVector = new int [_capacity];
            if (newVector == nullptr) {
                return false;
            }
            for (int i = 0; i < size; i++) {
                newVector[i] = array[i];
            }
            delete[] array;
            array = newVector;
        }
        return true;
    } // reserves _capacity if bigger

    void push_back (int element) {
        if (size + 1 <= capacity) {
            if (!reserve(2*capacity)) {
                std::cerr << "Failed to Allocate new memory!";
            }
        }
        array[size++] = element;
    }

    void erase (int index) {
        for (int i = index; i < size - 1; i++) {
            array[i] = array[i + 1];
        }
        --size;
    }

    void pop () { size--;}

    // extra functions
    void deleteNum (int num) {
        for (int i = 0; i < size; i++) {
            if (array[i] == num) {
                erase(i);
            }
        }
    }

    int find (int num) const {
        for (int i = 0; i < size; i++) {
            if (array[i] == num) {
                return i;
            }
        }
        return -1;
    }

    void print () const {
        for (int i = 0; i < size; i++) {
           std::cout << array[i];
           // std::cout << ' ';
        }
        // std:: cout << '\n';
    }

    int& operator [] (int idx) const {
        return array[idx];
    }

    bool operator == (const Vector& other) const {
        if (size != other.size) {
            return false;
        }
        for (int i = 0;i < size; i++) {
            if (array[i] != other[i] ) {
                return false;
            }
        }
        return true;
    }
};
