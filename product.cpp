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

    int& getNonConstSection () {return section;}
    int& getNonConstShelf () {return shelf;}
    Vector& getNonConstID () {return identificator;}

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

std::ostream& operator << (std::ostream& os, Location& _location) {
    return os   << _location.getSection() << '|' << _location.getShelf() 
                << '|' << _location.getID();
}

std::istream& operator >> (std::istream& is, Location& _location) {
    _location.setIDSizeToZero();
    is >> _location.getNonConstSection();
    is.ignore();
    is >> _location.getNonConstShelf();
    is.ignore();
    is >> _location.getNonConstID();
    return is;
}


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
    void setShelf(int _shelf) {loc.setShelf(_shelf);}
    void setSection(int _section) {loc.setSection(_section);}
    void resetName () { name.setSize(0);}
    void resetManufacturer () {manufacturer.setSize(0);} 
    void resetComment () {comment.setSize(0);}

    MyString& getName () {return name;}
    char* getNameString () {return name.getString();}
    int* getExpiryDate () {return expiryDate;}
    int& getExpiryYYYY () {return expiryDate[0];}
    int& getExpiryMM () {return expiryDate[1];}
    int& getExpiryDD () {return expiryDate[2];}
    int* getEntryDate () {return entryDate;}
    int& getEntryYYYY () {return entryDate[0];}
    int& getEntryMM () {return entryDate[1];}
    int& getEntryDD () {return entryDate[2];}
    MyString& getManufacturer () {return manufacturer;}
    int& getAmount () {return amountLeft;}
    Location& getLocation () {return loc;}
    int getSection () {return loc.getSection();}
    int getShelf () {return loc.getShelf();}
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

    int operator == (const Product& other) {
        if (!strcmp(name.getString(),other.name.getString())) {
            if (!strcmp(manufacturer.getString(),other.manufacturer.getString())) {
                for (int i = 0; i < YYYY_MM_DD; i++) {
                    if (expiryDate[i] != other.expiryDate[i]) {
                        return 0; // differs in the expiry date
                    }
                }
                return 1; // complete similarity
            }
        }
        return -1; // has a major difference
    }

    bool sameNames (const Product& other) {
        return !(strcmp(name.getString(),other.name.getString()));
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

    void print (int quantity) const {
        cout    << "Name: "; name.print(); cout << '\n';
        cout    << "Quantity: " << quantity << '\n';
        cout    << "Manufacturer: "; manufacturer.print(); cout << '\n';
        cout    << "Date of entry: " << entryDate[0] << '/' << entryDate[1] << '/' << entryDate[2] << '\n';
        cout    << "Date of expiration: " << expiryDate[0] << '/' << expiryDate[1] << '/' << expiryDate[2] << '\n';
        cout    << "Location in Storage - Section: " << loc.getSection() << "; Shelf: " << loc.getShelf()
                << "; ID: "; loc.printID(); cout << '\n';
        cout    << "Comment: "; comment.print(); cout << '\n';
    }   
};


std::ostream& operator << (std::ostream& os, Product& prod) {
    return os   << prod.getName() << '|' << prod.getAmount() << '|'
                << prod.getManufacturer() << '|' << prod.getEntryYYYY() << '.'
                << prod.getEntryMM() << '.' << prod.getEntryDD() << '|'
                << prod.getExpiryYYYY() << '.' << prod.getExpiryMM() << '.' 
                << prod.getExpiryDD() << '|' << prod.getLocation() << '|'
                << prod.getComment() << '\n';
    }

    std::istream& operator >> (std::istream& is, Product& prod) {
        prod.resetComment(); prod.resetManufacturer(); prod.resetName();
        is >> prod.getName();
        is >> prod.getAmount();
        is.ignore();
        is >> prod.getManufacturer();
        is >> prod.getEntryYYYY();
        is.ignore();
        is >> prod.getEntryMM();
        is.ignore();
        is >> prod.getEntryDD();
        is.ignore();
        is >> prod.getExpiryYYYY();
        is.ignore();
        is >> prod.getExpiryMM();
        is.ignore();
        is >> prod.getExpiryDD();
        is.ignore();
        is >> prod.getLocation();
        is >> prod.getComment();
        return is;
    }

bool writeProductToFile (const char* name, Product& unit) {
    std::ofstream out;
    out.open(name);
    if (!out) {
        return false;
    }
    out << unit;
    out.close();
    return true;
}