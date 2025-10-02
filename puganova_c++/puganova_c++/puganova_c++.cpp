#include <iostream>
#include <fstream> // для работы с файлами
#include <string> // для работы сос троками
#include <limits> // для проверки границ чисел

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
        // проверка на ошибку ввода
        if (cin.fail()) {
            cin.clear();
            cin.ignore(numeric_limits<streamsize>::max(), '\n');
            cout << "Invalid input. Please enter a valid value.\n";
        }
        else {
            cin.ignore(numeric_limits<streamsize>::max(), '\n'); // очистка буфера после успешного ввода
            return value;
        }
    }
}

// функция отображения главного меню программы
void display_main_menu() {
    cout << "   PIPELINE SYSTEM MENU\n";
    cout << "------------------------\n";
    cout << "1. Add Pipe\n";
    cout << "2. Add Compressor Station\n";
    cout << "3. View All Objects\n";
    cout << "4. Edit Pipe Repair Status\n";  // изменение статуса ремонта труб
    cout << "5. Manage Station Workshops\n"; // управление цехами станции
    cout << "6. Save Data\n";
    cout << "7. Load Data\n";
    cout << "0. Exit\n";
    cout << "------------------------\n";
}

// функция создания новой трубы с вводом всех параметров
void create_pipe(Pipe& pipe) {
    cout << "\n--- Create New Pipe ---\n";
    cout << "Enter kilometer mark: ";
    getline(cin, pipe.kilometer_mark); // ввод километровой отметки

    // ввод длины с проверкой на положительное значение
    pipe.length_km = get_valid_input<double>("Enter length (km): ");
    while (pipe.length_km <= 0) {
        cout << "Length must be positive. ";
        pipe.length_km = get_valid_input<double>("Enter length (km): ");
    }

    // ввод диаметра с проверкой на положительное значение
    pipe.diameter_mm = get_valid_input<double>("Enter diameter (mm): ");
    while (pipe.diameter_mm <= 0) {
        cout << "Diameter must be positive. ";
        pipe.diameter_mm = get_valid_input<double>("Enter diameter (mm): ");
    }

    pipe.under_repair = false; // по умолчанию труба не в ремонте
    cout << "Pipe created successfully!\n";
}

// функция создания новой компрессорной станции
void create_compressor_station(CompressorStation& station) {
    cout << "\n--- Create New Compressor Station ---\n";
    cout << "Enter station name: ";
    getline(cin, station.name); // ввод названия станции
    // ввод общего количества цехов
    station.total_workshops = get_valid_input<int>("Enter total number of workshops: ");
    while (station.total_workshops <= 0) {
        cout << "Number must be positive. ";
        station.total_workshops = get_valid_input<int>("Enter total number of workshops: ");
    }
    // ввод количества работающих цехов с проверкой корректности
    station.working_workshops = get_valid_input<int>("Enter number of working workshops: ");
    while (station.working_workshops < 0 || station.working_workshops > station.total_workshops) {
        cout << "Working workshops cannot exceed total workshops. ";
        station.working_workshops = get_valid_input<int>("Enter number of working workshops: ");
    }
    // ввод класса станции с проверкой диапазона
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

    // отображение информации о трубе, если она создана
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
    // отображение информации о станции, если она создана
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
    // проверка существования трубы
    if (pipe.kilometer_mark.empty()) {
        cout << "Error: No pipe available. Please create a pipe first.\n";
        return;
    }
    // отображение текущего статуса и меню выбора
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
    // проверка существования станции
    if (station.name.empty()) {
        cout << "Error: No compressor station available. Please create a station first.\n";
        return;
    }
    // отображение текущего состояния цехов
    cout << "\nCurrent workshops: " << station.working_workshops << "/" << station.total_workshops << "\n";
    cout << "1. Start Workshop\n";
    cout << "2. Stop Workshop\n";

    int choice = get_valid_input<int>("Select action: ");
    switch (choice) {
    case 1:
        // запуск цеха, если есть доступные
        if (station.working_workshops < station.total_workshops) {
            station.working_workshops++;
            cout << "Workshop started. Now " << station.working_workshops << " workshops working.\n";
        }
        else {
            cout << "All workshops are already working.\n";
        }
        break;
    case 2:
        // остановка цеха, если есть работающие
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

// вспомогательная функция для сохранения данных трубы в файл
void save_pipe_to_file(const Pipe& pipe, ofstream& file) {
    file << "PIPE\n";
    file << pipe.kilometer_mark << "\n";
    file << pipe.length_km << "\n";
    file << pipe.diameter_mm << "\n";
    file << pipe.under_repair << "\n";
}

// вспомогательная функция для сохранения данных станции в файл
void save_station_to_file(const CompressorStation& station, ofstream& file) {
    file << "STATION\n";
    file << station.name << "\n";
    file << station.total_workshops << "\n";
    file << station.working_workshops << "\n";
    file << station.station_class << "\n";
}

// основная функция сохранения всех данных в файл
void save_data(const Pipe& pipe, const CompressorStation& station) {
    ofstream file("pipeline_data.txt"); // открытие файла для записи
    if (!file.is_open()) {
        cout << "Error: Could not open file for writing.\n";
        return;
    }
    // сохранение трубы, если она существует
    if (!pipe.kilometer_mark.empty()) {
        save_pipe_to_file(pipe, file);
    }
    // сохранение станции, если она существует
    if (!station.name.empty()) {
        save_station_to_file(station, file);
    }

    file.close();
    cout << "Data saved successfully to pipeline_data.txt\n";
}

// вспомогательная функция для загрузки данных трубы из файла
void load_pipe_from_file(Pipe& pipe, ifstream& file) {
    getline(file, pipe.kilometer_mark);
    file >> pipe.length_km >> pipe.diameter_mm >> pipe.under_repair;
    file.ignore();
}

// вспомогательная функция для загрузки данных станции из файла
void load_station_from_file(CompressorStation& station, ifstream& file) {
    getline(file, station.name);
    file >> station.total_workshops >> station.working_workshops >> station.station_class;
    file.ignore();
}

// основная функция загрузки всех данных из файла
void load_data(Pipe& pipe, CompressorStation& station) {
    ifstream file("pipeline_data.txt"); // открытие файла для чтения
    if (!file.is_open()) {
        cout << "Error: Could not open file for reading.\n";
        return;
    }

    string object_type;
    pipe.kilometer_mark = "";    // сброс данных трубы
    station.name = "";           // сброс данных станции
    // чтение файла построчно
    while (getline(file, object_type)) {
        if (object_type == "PIPE") {
            load_pipe_from_file(pipe, file);
        }
        else if (object_type == "STATION") {
            load_station_from_file(station, file);
        }
    }

    file.close();
    cout << "Data loaded successfully from pipeline_data.txt\n";
}

// функция обработки выбора пользователя и вызова соответствующих функций
void process_user_choice(int choice, Pipe& pipe, CompressorStation& station) {
    switch (choice) {
    case 1:
        create_pipe(pipe);
        break;
    case 2:
        create_compressor_station(station);
        break;
    case 3:
        display_objects(pipe, station);   //просмотр объектов
        break;
    case 4:
        edit_pipe_repair(pipe);           // редактирование трубы
        break;
    case 5:
        manage_station_workshops(station);  // управление станции
        break;
    case 6:
        save_data(pipe, station);
        break;
    case 7:
        load_data(pipe, station);
        break;
    case 0:
        cout << "Exiting program. Goodbye!\n";
        exit(0);
    default:
        cout << "Invalid choice. Please try again.\n"; // неверный ввод
    }
}

// главная функция программы
int main() {
    Pipe main_pipe;                   // создание объекта трубы
    CompressorStation main_station;   // создание объекта станции

    while (true) {
        display_main_menu();                                       // показ меню
        int choice = get_valid_input<int>("Enter your choice: ");  // ввод выбора
        process_user_choice(choice, main_pipe, main_station);      // обработка выбора
    }
}
