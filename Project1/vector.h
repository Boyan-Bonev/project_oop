#ifndef VECTOR_H
#define VECTOR_H

template <typename T>
class Vector { 
    int size; // current amount
    int capacity; // max amount
    T* array;
    void copy(const Vector& other);
    void clear();
    bool reserve(int _capacity);
    
    public:
    Vector();
    Vector (const Vector& other) { copy(other); }
    Vector(int cap);
    Vector(int _size, T* _array);

    ~Vector() { clear(); }

    int getSize() const {return size;}
    int getCapacity() const {return capacity;}

    void setVector (int _size, T* _array);
    void readVector (std::istream& is = std::cin);

    void print () const;
    void push_back (T element);
    void erase (int index);
    void pop () { size--;};
    void deleteElem (T elem);
    T& find (T elem) const;
    
    Vector& operator= (const Vector& other);
    T& operator [] (int idx) const;
    bool operator == (const Vector& other) const;
    std::ostream& operator << (std::ostream& os, Vector& dynArray);
    std::ostream& operator << (std::ostream& os, const Vector& dynArray);
    std::istream& operator >> (std::istream& is, Vector& dynArray);

};


#endif