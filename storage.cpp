#include <iostream>
#include <cstring>
#include "product.cpp"

using std::cout;
using std::cin;
using std::endl;

const size_t MAX_PRODUCTS = 64;
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

    bool shelfIsEmpty(int _section, int _shelf) {
        for (int i = 0; i < size; i++) {
            if (store[i].getSection() == _section) {
                if (store[i].getShelf() == _shelf) {
                    return true;
                }
            }
        }
        return false;
    }

    void addProduct (Product prod) {
        int temp;
        bool isPlaced = false;
        for (int i = 0; i < size; i++) {
            if ((prod == store[i]) == 1) {
                store[i].setAmount(store[i].getAmount() + prod.getAmount());
                temp = i;
            }
            if ((prod == store[i]) == 0) {
                store[size++] = prod;
                store[size - 1].setSection(store[i].getSection());
                for (int i = store[i].getShelf() + 1; !isPlaced; i++) {
                    if (shelfIsEmpty(store[i].getSection(),i)) {
                        store[size - 1].setShelf(i);
                        isPlaced = true;
                    }
                }
            }
        }

    }

    void setStorage () {
        int amount;
        cout << "Enter the amount of products you will add: "; cin >> amount;
        cin.ignore();
        for (int i = 0; i < amount; i++) {
            cout << "Product №" << i << '\n';
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
        cout << '\n';
        Vector usedIndexes;
        int quantity = 0;
        bool hasBeenAccounted = false;
        for (int i = 0; store[i].exists(); i++) {
            for (int k = 0; k < usedIndexes.getSize(); k++) {
                if (usedIndexes[k] == i) {
                    hasBeenAccounted = true;
                }
            }
            if (hasBeenAccounted) {
                continue;
            }
            quantity = store[i].getAmount();
            cout << "Product №" << i << '\n';
            for (int j = i + 1; store[j].exists(); j++) {
                if (store[i].sameNames(store[j])) {
                    quantity += store[j].getAmount();
                    usedIndexes.push_back(j);
                }
            }
            store[i].print(quantity);
            cout << '\n';
        }
        cout.setf(std::ios::left);
        cout.width(MAX_WIDTH);
        cout.fill('-');
        cout << '-';
        cout << std::endl;
        cout << "All products listed.";
        cout.fill(' ');
    }

    
};