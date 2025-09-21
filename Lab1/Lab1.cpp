#include <iostream>
#include <fstream>  
#include <string> 
#include <clocale>
#include <limits>

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
float check() {
    float number;
    while (true) {
        cin >> number;
        if (cin.fail() || number <= 0) {
            cout << "Введите положительное число";
            cin.clear();
            cin.ignore(numeric_limits<streamsize>::max(), '\n');
        }
        else {
            cin.ignore(numeric_limits<streamsize>::max(), '\n');
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
            cin.ignore(numeric_limits<streamsize>::max(), '\n');
            return number;
        }
    }
}
// Функция для проверки статуса ремонта
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
            cin.ignore(numeric_limits<streamsize>::max(), '\n');
            return (status == 0);
        }
    }
}

truba truba_cin(truba& T) {
    cout << "Километровая отметка трубы " << endl;
    getline(cin >> ws, T.Name1);
    cout << "Длина (км) " << endl;
    T.Dlina = check();
    cout << "Диаметр (мм) " << endl;
    T.Diametr = check();
    cout << "Статус ремонта: (0 - в ремонте, 1 - работает) ";
    T.Remont = checkRemont();
    return T;
}

ks ks_cin(ks& K) {
    cout << "Название " << endl;
    getline(cin >> ws, K.Name2);
    cout << "Количество цехов " << endl;
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

void truba_redakt(truba& T) {
    if (T.Name1.empty()) {
        cout << "Ошибка: труба не добавлена" << endl;
        return;
    }

    cout << "Текущий статус: " << (T.Remont ? "В ремонте (Введите 0 - в ремонте, 1 - работает)" : "Работает (Введите 0 - в ремонте, 1 - работает)") << endl;
    T.Remont = checkRemont();
    cout << "Статус обновлен: " << (T.Remont ? "В ремонте" : "Работает") << endl;
}

void openWS_redakt(ks& K) {
    if (K.Name2.empty()) {
        cout << "Ошибка: КС не добавлена" << endl;
        return;
    }

    cout << "Сейчас в работе: " << K.OpenWS << " из " << K.WorkShops << endl;
    cout << "Новое количество цехов в работе: ";

    int newOpenWS;
    while (true) {
        newOpenWS = checkWorkShops();

        if (newOpenWS > K.WorkShops) {
            cout << "Количество работающих цехов не может превышать общее количество цехов";
            cout << "Введите снова: ";
        }
        else {
            break;
        }
    }

    K.OpenWS = newOpenWS;
    cout << "Данные обновлены: " << K.OpenWS << " цехов в работе" << endl;
}

// Сохранение в файл
void save(const truba& t, const ks& k, const string& filename) {
    ofstream file(filename);
    if (file.is_open()) {
        // Труба
        file << "Truba" << endl;
        file << t.Name1 << endl;
        file << t.Dlina << endl;
        file << t.Diametr << endl;
        file << t.Remont << endl;

        // КС
        file << "KS" << endl;
        file << k.Name2 << endl;
        file << k.WorkShops << endl;
        file << k.OpenWS << endl;
        file << k.Class << endl;

        file.close();
        cout << "Данные сохранены в файл: " << filename << endl;
    }
    else {
        cout << "Ошибка" << endl;
    }
}

// Загрузка из файла
bool load(truba& t, ks& k, const string& filename) {
    ifstream file(filename);
    if (file.is_open()) {
        string line;

        // Проверка формата
        getline(file, line);
        if (line != "Truba") {
            cout << "Неверный формат" << endl;
            file.close();
            return false;
        }
        // Загрузка
        getline(file >> ws, t.Name1);
        file >> t.Dlina >> t.Diametr >> t.Remont;
        file.ignore();


        getline(file, line);
        if (line != "KS") {
            cout << "Неверный формат" << endl;
            file.close();
            return false;
        }
        getline(file >> ws, k.Name2);
        file >> k.WorkShops >> k.OpenWS >> k.Class;

        // Проверка корректности данных
        if (k.OpenWS > k.WorkShops) {
            k.OpenWS = k.WorkShops;
        }

        file.close();
        cout << "Данные загружены из файла: " << filename << endl;
        return true;
    }
    else {
        cout << "Ошибка" << endl;
        return false;
    }
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

// Показать 
void Show(const truba& t, const ks& k) {
    if (t.Name1.empty() || k.Name2.empty()) {
        cout << "Данные не добавлена" << endl;
        return;
    }
    else {
        print_truba(t);
        print_ks(k);
    }
}

// Меню
void ShowMenu(truba& t, ks& k) {
    int option;
    string filename;

    while (1) {
        cout << "\nМеню" << endl;
        cout << "1. Добавить трубу" << endl;
        cout << "2. Добавить КС" << endl;
        cout << "3. Просмотр всех объектов" << endl;
        cout << "4. Редактировать трубу" << endl;
        cout << "5. Редактировать КС" << endl;
        cout << "6. Сохранить в файл" << endl;
        cout << "7. Загрузить из файла" << endl;
        cout << "0. Выход" << endl;
        cout << "Выберите действие: ";

        cin >> option;
        cin.ignore(numeric_limits<streamsize>::max(), '\n');
        switch (option) {
        case 1:
            truba_cin(t);
            break;

        case 2:
            ks_cin(k);
            break;

        case 3:
            Show(t, k);
            break;

        case 4:
            truba_redakt(t);
            break;

        case 5:
            openWS_redakt(k);
            break;

        case 6:
            if (t.Name1.empty() || k.Name2.empty()) {
                cout << "Для сохранения должны быть добавлены и труба и КС.\n";
                break;
            }
            cout << "Введите имя файла: ";
            getline(cin, filename);
            save(t, k, filename);
            break;

        case 7:
            cout << "Введите имя файла: ";
            getline(cin, filename);
            load(t, k, filename);
            break;

        case 0:
            cout << "Выход из программы.\n";
            return;

        default:
            cout << "Неверный выбор. Попробуйте снова.\n";
            break;
        }
    }
}

int main() {
    setlocale(LC_ALL, "Russian");
    truba t;
    ks k;
    ShowMenu(t, k);
    return 0;
}

