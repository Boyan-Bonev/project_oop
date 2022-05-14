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
        bool isPlaced = false;
        for (int i = 0; i < size; i++) {
            if ((prod == store[i]) == 1) {
                store[i].setAmount(store[i].getAmount() + prod.getAmount());
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

    void removeProductByIdx (int idx) {
        store[idx] = store[size];
        store[size--].setToNULL();
    }

    void removeProduct (const char* _name, int amount) {
        Vector idxsOfProduct;
        for (int i = 0; i < size; i++) {
            if (!strcmp(_name,store[i].getNameString())) {
                idxsOfProduct.push_back(i);
            }
        }

        if (idxsOfProduct.getSize() == 0) {
            std::cerr << "No such existent product name in the storage!";
        }
        else {
            sortByExpiryDate(idxsOfProduct);
            int currIdx = 0, totalAmount = 0;
            for (int i = 0; i < idxsOfProduct.getSize(); i++) {
                totalAmount += store[idxsOfProduct[i]].getAmount();
            }
            cout << "There isn't enough " << _name << "s in the storage!\n";
            cout << "Do You still want to remove the existent amount? Answer with Y or N";
            char c;
            cin.get(c);
            cin.get();
            if (c == 'Y') {
                for (int i = 0; i < idxsOfProduct.getSize() && amount > 0; i++) {
                    currIdx = idxsOfProduct[i];
                    if (store[currIdx].getAmount() > amount) {
                        store[currIdx].setAmount(store[currIdx].getAmount() - amount);
                        amount = 0;
                        cout    << amount << ' ' << _name << "s removed from section " << store[currIdx].getSection() 
                                << ", shelf " << store[currIdx].getShelf();
                        continue;
                    }
                    else if (store[currIdx].getAmount() == amount) {
                        removeProductByIdx(currIdx);
                        amount = 0;
                        cout    << amount << ' ' << _name << "s removed from section " << store[currIdx].getSection() 
                                << ", shelf " << store[currIdx].getShelf();
                        continue;
                    } 
                    else {
                        amount -= store[currIdx].getAmount();
                        removeProductByIdx(currIdx);
                        cout    << store[currIdx].getAmount() << ' ' << _name << "s removed from section " << store[currIdx].getSection() 
                                << ", shelf " << store[currIdx].getShelf();
                        continue;
                    }
                }
            }
        } 
    }
    
    void checkUp (int* startDate, int* endDate) {
        
    }

    void sortByExpiryDate (Vector array) {
        int minExpiryIdx = -1, earliestYear = 9999, earliestMonth = 13, earliestDate = 32;
        for (int idx = 0; idx < array.getSize(); idx++) {
            for (int i = 0; i < array.getSize() - 1; i++) {
                earliestYear = 9999, earliestMonth = 13, earliestDate = 32;
                minExpiryIdx = -1;
                if (earliestYear > store[array[i]].getExpiryYYYY()) {
                    earliestYear = store[array[i]].getExpiryYYYY();
                    minExpiryIdx = i;
                }
                else if (earliestYear == store[array[i]].getExpiryYYYY()) {
                    if (earliestMonth > store[array[i]].getExpiryMM()) {
                        earliestMonth = store[array[i]].getExpiryMM();
                        minExpiryIdx = i;
                    }
                    else if (earliestMonth == store[array[i]].getExpiryMM()) {
                        if (earliestDate > store[array[i]].getExpiryDD()) {
                            earliestDate = store[array[i]].getExpiryDD();
                            minExpiryIdx = i;
                        }
                    }
                        
                }
            }
                std::swap(array[idx],array[minExpiryIdx]);
        }
    }

    
};
