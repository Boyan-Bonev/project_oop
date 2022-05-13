#include <iostream>
#include <cstring>
#include "vector.cpp"
#include "myString.cpp"
#include "product.cpp"

using std::cout;
using std::cin;

const size_t MAX_PRODUCTS = 128;
const size_t MAX_WIDTH = 128;

class Storage {
    Product store [MAX_PRODUCTS];
    int size;
    public:
    Storage () {
        for (int i = 0; i < MAX_PRODUCTS; i++) {
            store[i].setToNULL();
            size = 0;
        }
    }

    void addProduct (Product prod) {
        store[size++] = prod;
    }

    void setStorage () {
        int amount;
        cout << "Enter the amount of products you will add: "; cin >> amount;
        for (int i = 0; i < amount; i++) {
            cout << "Product №" << i;
            setProduct();
        }
    }



    void setProduct () {
        store[size++].readProduct();
    }

    void print () {
        cout << "Storage Unit Content:\n";
        cout.setf(std::ios::left);
        cout.width(MAX_WIDTH);
        cout.fill('-');
        cout << '-';
        cout << std::endl;
        cout.fill(' ');
        for (int i = 0; store[i].exists(); i++) {
            cout << "Product №" << i << '\n';
            store[i].print();
        }
        cout.fill('-');
        cout << "All products listed.";
        cout.fill(' ');
    }

};