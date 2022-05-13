#include <iostream>
#include <cstring>
#include "vector.cpp"
#include "myString.cpp"

using std::cout;
using std::cin;

const size_t MAX_ID = 10;
const size_t YYYY_MM_DD = 3;

class Location {
    int section;
    int shelf;
    Vector identificator;
    public:

    Location () {
        section = -1;
        shelf = -1;

        int* temp2 = new int [MAX_ID];
        for (int i = 0; i < MAX_ID; i++) {
            temp2[i] = 0;
        }
        Vector tempID(MAX_ID, temp2);
        identificator = tempID;
        delete[] temp2;   
    }
    
    Location(int _section, int _shelf, const Vector& _identificator) : section(-1), shelf(-1), identificator(Vector(4)) {
        section = _section;
        shelf = _shelf;
        identificator = _identificator;
    }

    // getters
    int getSection () const {return section;}
    int getShelf () const {return shelf;}
    const Vector& getID () const {return identificator;}

    // setters 
    void setLocation(int _section, int _shelf, const Vector& id) {
        setSection(_section);
        setShelf(_shelf);
        setID(id);
    }
    void setSection (int _section) { section = _section;}
    void setSection () {
        cin >> section;
    }
    void setShelf (int _shelf) {shelf = _shelf;}
    void setShelf () {
        cin >> shelf;
    }
    void setID (const Vector& id) {identificator = id;}
    void setID (int* id, int length) {
        for (int i = 0; i < length ; i++) {
            identificator[i] = id[i];
        }
    }
    void setID () {
        identificator.readVector();
    }

    void setIDSizeToZero () {
        for (int i = 0; i <identificator.getSize();) {
            identificator.pop();
        }
    }

    void readLocation () {
        cout << "Section: "; cin >> section;
        cout << "Shelf: "; cin >> shelf;
        cout << "ID: "; identificator.readVector();
    }

    void printID () const {
        identificator.print();
    }

    void print () const {
        std::cout << "Location - Section " << section << ", Shelf " << shelf << ", ID: ";
        identificator.print();
        std::cout << '\n';
    }
    
    bool operator == (const Location& other) {
        return section == other.getSection() && shelf == other.getShelf() && identificator == other.getID();
    }
};

class Product {
    MyString name;
    int amountLeft;
    MyString manufacturer;
    int entryDate [YYYY_MM_DD];
    int expiryDate [YYYY_MM_DD];
    Location loc;
    MyString comment;
    
    public:
    Product () {
        setToNULL();
    }

    void setName(const MyString& _name) { name = _name;}
    void setExpiryDate (int _expiryDate [YYYY_MM_DD]) { 
        for (int i = 0; i < YYYY_MM_DD; i++) {
            expiryDate[i] = _expiryDate[i];
        }
    }
    void setEntryDate (int _entryDate [YYYY_MM_DD]) { 
        for (int i = 0; i < YYYY_MM_DD; i++) {
            entryDate[i] = _entryDate[i];
        }
    }
    void setManufacturer(const MyString& _manufacturer) { manufacturer = _manufacturer;}
    void setAmount (int amount) {amountLeft = amount;}
    void setLocation (const Location& _loc) { loc = _loc;}
    void setComment(const MyString& _comment) { comment = _comment;}

    MyString& getName () {return name;}
    int* getExpiryDate () {return expiryDate;}
    int* getEntryDate () {return entryDate;}
    MyString& getManufacturer () {return manufacturer;}
    int getAmount () {return amountLeft;}
    Location& getLocation () {return loc;}
    MyString& getComment () {return comment;}

    void readProduct () {
        cout << "Product entry\n";
        cout << "Name: "; 
        for (int i = 0; i < name.getSize();) {
            name.pop();
        }
        name.readString();
        cout << "Quantity: "; cin >> amountLeft; cin.ignore();
        cout << "Manufacturer: "; 
        for (int i = 1; i <= manufacturer.getSize();) {
            manufacturer.pop();
        }
        manufacturer.readString();
        cout << "Date of entry/YYYY_MM_DD/:\n"; 
        cout << "YYYY: "; cin >> entryDate[0]; cin.get();
        cout << "MM: "; cin >> entryDate[1]; cin.get();
        cout << "DD: "; cin >> entryDate[2]; cin.get();
        cout << "Date of expiration/YYYY_MM_DD/:\n";
        cout << "YYYY: "; cin >> expiryDate[0]; cin.get();
        cout << "MM: "; cin >> expiryDate[1]; cin.get();
        cout << "DD: "; cin >> expiryDate[2]; cin.get();
        cout << "Location in Storage/Section,Shelf,ID/:\n";
        cout << "Section: "; loc.setSection(); cin.get();
        cout << "Shelf: "; loc.setShelf(); cin.get();
        cout << "ID: "; loc.setIDSizeToZero(); loc.setID();
        cout << "Comment: ";
        comment.setSize(0);
        comment.readString();
    }

    void setToNULL () {
        name = "N/A";
        int temp[3] = {0,0,0};
        for (int i = 0; i < YYYY_MM_DD; i++) {
            entryDate[i] = 0;
            expiryDate[i] = 0;
        }
        manufacturer = "N/A";
        amountLeft = 0;

        int* temp2 = new int [MAX_ID];
        for (int i = 0; i < MAX_ID; i++) {
            temp2[i] = 0;
        }
        Vector tempID(MAX_ID, temp2);
        delete[] temp2;

        loc.setLocation(0,0,tempID);
        comment = "No comment.";
    }

    bool exists () {
        if (entryDate[0] == 0) {
            return false;
        }
        return true;
    }   

    void print () const {
        cout    << "Name: "; name.print(); cout << '\n';
        cout    << "Quantity: " << amountLeft << '\n';
        cout    << "Manufacturer: "; manufacturer.print(); cout << '\n';
        cout    << "Date of entry: " << entryDate[0] << '/' << entryDate[1] << '/' << entryDate[2] << '\n';
        cout    << "Date of expiration: " << expiryDate[0] << '/' << expiryDate[1] << '/' << expiryDate[2] << '\n';
        cout    << "Location in Storage - Section: " << loc.getSection() << "; Shelf: " << loc.getShelf()
                << "; ID: "; loc.printID(); cout << '\n';
        cout    << "Comment: "; comment.print(); cout << '\n';
    }  
};