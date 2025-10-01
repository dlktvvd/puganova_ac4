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

// функция создания новой трубы с вводом всех параметров
void create_pipe(Pipe& pipe) {
    cout << "\n--- Create New Pipe ---\n";
    cout << "Enter kilometer mark: ";
    getline(cin, pipe.kilometer_mark);

    pipe.length_km = get_valid_input<double>("Enter length (km): ");
    while (pipe.length_km <= 0) {
        cout << "Length must be positive. ";
        pipe.length_km = get_valid_input<double>("Enter length (km): ");
    }

    pipe.diameter_mm = get_valid_input<double>("Enter diameter (mm): ");
    while (pipe.diameter_mm <= 0) {
        cout << "Diameter must be positive. ";
        pipe.diameter_mm = get_valid_input<double>("Enter diameter (mm): ");
    }

    pipe.under_repair = false;
    cout << "Pipe created successfully!\n";
}

// Функция создания новой компрессорной станции
void create_compressor_station(CompressorStation& station) {
    cout << "\n--- Create New Compressor Station ---\n";
    cout << "Enter station name: ";
    getline(cin, station.name);

    station.total_workshops = get_valid_input<int>("Enter total number of workshops: ");
    while (station.total_workshops <= 0) {
        cout << "Number must be positive. ";
        station.total_workshops = get_valid_input<int>("Enter total number of workshops: ");
    }

    station.working_workshops = get_valid_input<int>("Enter number of working workshops: ");
    while (station.working_workshops < 0 || station.working_workshops > station.total_workshops) {
        cout << "Working workshops cannot exceed total workshops. ";
        station.working_workshops = get_valid_input<int>("Enter number of working workshops: ");
    }
    station.station_class = get_valid_input<int>("Enter station class (1-5): ");
    while (station.station_class < 1 || station.station_class > 5) {
        cout << "Class must be between 1 and 5. ";
        station.station_class = get_valid_input<int>("Enter station class (1-5): ");
    }

    cout << "Compressor station created successfully!\n";
}

// функция отображения всех созданных объектов
void display_objects(const Pipe& pipe, const CompressorStation& station) {
    cout << "\n--- CURRENT OBJECTS ---\n";

    cout << "PIPE:\n";
    if (pipe.kilometer_mark.empty()) {
        cout << "  No pipe data available\n";
    }
    else {
        cout << "  Kilometer Mark: " << pipe.kilometer_mark << "\n";
        cout << "  Length: " << pipe.length_km << " km\n";
        cout << "  Diameter: " << pipe.diameter_mm << " mm\n";
        cout << "  Under Repair: " << (pipe.under_repair ? "Yes" : "No") << "\n";
    }
    cout << "\nCOMPRESSOR STATION:\n";
    if (station.name.empty()) {
        cout << "  No station data available\n";
    }
    else {
        cout << "  Name: " << station.name << "\n";
        cout << "  Workshops: " << station.working_workshops << "/" << station.total_workshops << "\n";
        cout << "  Class: " << station.station_class << "\n";
    }
}
// функция изменения статуса ремонта трубы
void edit_pipe_repair(Pipe& pipe) {
    if (pipe.kilometer_mark.empty()) {
        cout << "Error: No pipe available. Please create a pipe first.\n";
        return;
    }

    cout << "\nCurrent repair status: " << (pipe.under_repair ? "Under Repair" : "Operational") << "\n";
    cout << "1. Mark as Under Repair\n";
    cout << "2. Mark as Operational\n";

    int choice = get_valid_input<int>("Select option: ");
    switch (choice) {
    case 1:
        pipe.under_repair = true;
        cout << "Pipe marked as under repair.\n";
        break;
    case 2:
        pipe.under_repair = false;
        cout << "Pipe marked as operational.\n";
        break;
    default:
        cout << "Invalid selection.\n";
    }
}

// функция управления рабочими цехами станции
void manage_station_workshops(CompressorStation& station) {
    if (station.name.empty()) {
        cout << "Error: No compressor station available. Please create a station first.\n";
        return;
    }

    cout << "\nCurrent workshops: " << station.working_workshops << "/" << station.total_workshops << "\n";
    cout << "1. Start Workshop\n";
    cout << "2. Stop Workshop\n";

    int choice = get_valid_input<int>("Select action: ");
    switch (choice) {
    case 1:
        if (station.working_workshops < station.total_workshops) {
            station.working_workshops++;
            cout << "Workshop started. Now " << station.working_workshops << " workshops working.\n";
        }
        else {
            cout << "All workshops are already working.\n";
        }
        break;
    case 2:
        if (station.working_workshops > 0) {
            station.working_workshops--;
            cout << "Workshop stopped. Now " << station.working_workshops << " workshops working.\n";
        }
        else {
            cout << "No workshops are currently working.\n";
        }
        break;
    default:
        cout << "Invalid selection.\n";
    }
}