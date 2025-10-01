#include <iostream>
#include <fstream>
#include <string>
#include <limits>

using namespace std;

// структура для представления трубопровода
struct Pipe {
    string kilometer_mark;
    double length_km;
    double diameter_mm;
    bool under_repair;
};

// структура для представления компрессорной станции
struct CompressorStation {
    string name;
    int total_workshops;
    int working_workshops;
    int station_class;
};

// функция для безопасного ввода данных с проверкой корректности
template <typename T>
T get_valid_input(const string& prompt) {
    T value;
    while (true) {
        cout << prompt;
        cin >> value;
        if (cin.fail()) {
            cin.clear();
            cin.ignore(numeric_limits<streamsize>::max(), '\n');
            cout << "Invalid input. Please enter a valid value.\n";
        }
        else {
            cin.ignore(numeric_limits<streamsize>::max(), '\n');
            return value;
        }
    }
}

// функция отображения главного меню программы
void display_main_menu() {
    cout << "\n========================\n";
    cout << "   PIPELINE SYSTEM MENU\n";
    cout << "========================\n";
    cout << "1. Add Pipe\n";
    cout << "2. Add Compressor Station\n";
    cout << "3. View All Objects\n";
    cout << "4. Edit Pipe Repair Status\n";
    cout << "5. Manage Station Workshops\n";
    cout << "6. Save Data\n";
    cout << "7. Load Data\n";
    cout << "0. Exit\n";
    cout << "========================\n";
}