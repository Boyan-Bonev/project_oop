#include <iostream>
#include "storage.cpp"


int main () {
    Storage unit;
    MyString unitName;
    MyString tempName;
    int tempAmnt;
    int startDate[3], endDate[3], currDate[3];

    cout << "Въведете името на складовия файл: ";
    unitName.readString();
    readStorageFromFile(unitName.getString(), unit);

    cout << "Въведете продукта си за въвеждане";
    Product prod; prod.readProduct();
    unit.addProduct(prod);

    cout << "Въведете името на продукт за изваждане: "; tempName.readString();
    cout << "Въведете бройката за изваждане: "; cin >> tempAmnt; cin.get();
    unit.removeProduct(tempName.getString(),tempAmnt);

    cout << "Въведете името на продукт за изваждане: "; tempName.readString();
    cout << "Въведете бройката за изваждане: "; cin >> tempAmnt; cin.get();
    unit.removeProduct(tempName.getString(),tempAmnt);

    cout << "Въведете периода, подлежащ на справка: \n";
    cout << "Начална дата /YYYY_MM_DD/:\n"; 
    cout << "YYYY: "; cin >> startDate[0]; cin.get();
    cout << "MM: "; cin >> startDate[1]; cin.get();
    cout << "DD: "; cin >> startDate[2]; cin.get();
    cout << "Крайна дата/YYYY_MM_DD/:\n";
    cout << "YYYY: "; cin >> endDate[0]; cin.get();
    cout << "MM: "; cin >> endDate[1]; cin.get();
    cout << "DD: "; cin >> endDate[2]; cin.get();
    unit.checkUp(startDate,endDate);

    cout << "Въведете сегашната дата, за да разчистите склада: \n";
    cout << "YYYY: "; cin >> currDate[0]; cin.get();
    cout << "MM: "; cin >> currDate[1]; cin.get();
    cout << "DD: "; cin >> currDate[2]; cin.get();
    unit.cleanUp(currDate);

    unit.print();
    return 0;

    /*
    Storage unit;
    std::cin >> unit;
    std::cout << unit;
    std::cout << '\n';
    Product prod;
    std::cin >> prod;
    std::cout << prod;
    std::cout << '\n';
    Location loc;
    std::cin >> loc;
    std::cout << loc;
    std::cout << std::endl;
    Vector id;
    std::cin >> id;
    std::cout << id;
    std::cout << std::endl;
    MyString id2;
    std::cout << "HERE\n";
    std::cin >> id2;
    std::cout << id2;
    */
}