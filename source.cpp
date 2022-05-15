#include <iostream>
#include <cstring>
#include "storage.cpp"

using std::cin;
using std::cout;

bool isValidCommand (char* string) {
    return  !strcmp(string,"Извеждане") || !strcmp(string,"Добавяне на продукт") ||
            !strcmp(string,"Изваждане на продукт") || !strcmp(string,"Справка за наличност") ||
            !strcmp(string,"Разчистване") || !strcmp(string,"Помощ") || !strcmp(string,"Край");
}

void printCommands () {
    cout << "Валидни команди:\nИзвеждане;Добавяне на продукт; Изваждане на продукт; Справка за наличност; Разчистване; Помощ; Край\n";
}

int main () {  
    Storage unit;
    MyString unitName;
    cout << "Въведете името на складовия файл: ";
    unitName.readString();
    readStorageFromFile(unitName.getString(), unit);

    Product prod;
    MyString tempName;
    int tempAmnt;
    int startDate[3], endDate[3], currDate[3];


    MyString input;
    do {
        cout << "Въведете командата, която желаете или /Помощ/ за изреждане на командите\n";
        input.setSize(0);
        input.readString();
        if (!strcmp(input.getString(),"Извеждане")) {
            unit.print();
        }
        else if (!strcmp(input.getString(),"Добавяне на продукт")) {
            cout << "Въведете продукта си:\n";
            prod.readProduct();
            unit.addProduct(prod);
        }
        else if (!strcmp(input.getString(),"Изваждане на продукт")) {
            cout << "Въведете името му: "; tempName.readString();
            cout << "Въведете бройката за изваждане: "; cin >> tempAmnt; cin.get();
            unit.removeProduct(tempName.getString(),tempAmnt);
        }
        else if (!strcmp(input.getString(),"Справка за наличност")) {
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
        }
        else if (!strcmp(input.getString(),"Разчистване")) {
            cout << "Въведете сегашната дата: \n";
            cout << "YYYY: "; cin >> currDate[0]; cin.get();
            cout << "MM: "; cin >> currDate[1]; cin.get();
            cout << "DD: "; cin >> currDate[2]; cin.get();
            unit.cleanUp(currDate);
        }
        else if (!strcmp(input.getString(),"Помощ")) {
            printCommands();
        }
        if (!isValidCommand(input.getString())) {
            cout << "Невалидна функция. Моля опитайте отново\n";
        }

    }
    while (!strcmp(input.getString(),"Край"));
    
    return 0;
}