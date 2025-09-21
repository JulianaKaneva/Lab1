#include <iostream>
#include <fstream>  
#include <string> 
#include <clocale>

using namespace std;

struct truba {
    string Name1;
    float Dlina = 0;
    float Diametr = 0.0;
    bool Remont = true;
};

struct ks {
    string Name2;
    int WorkShops = 0;
    int OpenWS = 0;
    float Class = 0.0;
};


// Функция для проверки ввода числа
int check() {
    float number;
    while (true) {
        cin >> number;
        if (cin.fail() || number <= 0) {
            cout << "Введите положительное число";
            cin.clear();
            cin.ignore(numeric_limits<streamsize>::max(), '\n');
        }
        else {
            return number;
        }
    }
}
// Функция для проверки целочисленности цехов
int checkWorkShops() {
    int number;
    while (true) {
        cin >> number;
        if (cin.fail() || number <= 0 || cin.peek() != '\n') {
            cout << "Введите положительное целое число: ";
            cin.clear();
            cin.ignore(numeric_limits<streamsize>::max(), '\n');
        }
        else {
            return number;
        }
    }
}

bool checkRemont() {
    int status;
    while (true) {
        cin >> status;
        if (cin.fail() || (status != 0 && status != 1)) {
            cout << "Введите 0 (в ремонте) или 1 (работает): ";
            cin.clear();
            cin.ignore(numeric_limits<streamsize>::max(), '\n');
        }
        else {
            return (status == 1);
        }
    }
}

truba truba_cin() {
    truba T;
    cout << "Километровая отметка трубы" << endl;
    getline(cin >> ws, T.Name1);
    cout << "Длина (км)" << endl;
    T.Dlina = check();
    cout << "Диаметр (мм)" << endl;
    T.Diametr = check();
    cout << "Статус ремонта: ";
    T.Remont = checkRemont();
    return T;
}

void truba_redakt(truba& T) {
    cout << "Текущий статус: " << (T.Remont ? "В ремонте" : "Работает") << endl;
    T.Remont = checkRemont();
    cout << "Статус обновлен: " << (T.Remont ? "В ремонте" : "Работает") << endl;
}

void openWS_redakt(ks& K) {
    cout << "Сейчас в работе: " << (K.OpenWS) << endl;
    K.OpenWS = checkWorkShops();
    cout << "Данные обновлены: " << (K.OpenWS) << endl;
}

ks ks_cin() {
    ks K;
    cout << "Название" << endl;
    getline(cin >> ws, K.Name2);
    cout << "Количество цехов" << endl;
    K.WorkShops = checkWorkShops();
    cout << "Количество цехов в работе " << endl;
    K.OpenWS = checkWorkShops();
    while (true) {
        if (K.OpenWS > K.WorkShops) {
            cout << "Количество цехов в работе превышает общее количество цехов" << endl;
            K.OpenWS = check();
        }
        else {
            break;
        }
    }
    cout << "Класс станции" << endl;
    K.Class = check();
    return K;
}

// Вывод данных о трубе
void print_truba(const truba& t) {
    cout << "\nДанные о трубе" << endl;
    cout << "Километровая отметка: " << t.Name1 << endl;
    cout << "Длина: " << t.Dlina << " км" << endl;
    cout << "Диаметр: " << t.Diametr << " мм" << endl;
    cout << "Статус ремонта: " << (t.Remont ? "В ремонте" : "Работает") << endl;
}

// Вывода данных о КС
void print_ks(const ks& k) {
    cout << "\nДанные о КС" << endl;
    cout << "Название: " << k.Name2 << endl;
    cout << "Количество цехов: " << k.WorkShops << endl;
    cout << "Цехов в работе: " << k.OpenWS << endl;
    cout << "Класс станции: " << k.Class << endl;
}

int main(){
    setlocale(LC_ALL, "Russian");
    truba t;
    ks k;
    t = truba_cin(); // ввод данных трубы
    k = ks_cin();
    print_truba(t); // вывод данных трубы
    print_ks(k);
    return 0;
}

