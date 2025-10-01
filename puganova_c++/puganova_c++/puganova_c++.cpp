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