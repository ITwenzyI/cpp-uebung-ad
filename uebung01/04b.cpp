/*
 * File: 04b
 * Author: Kilian | ItwenzyI
 * Created: 10.10.2025
 * Description: 
 */
#include <iostream>
#include <string>
#include <chrono>       // chrono für Zeitmessung

class Matrix {

public:
    size_t zeilen;
    size_t spalten;
    int *data;

    // Konsturktor mit Zeilen und Spalten ohne Inhalt wenn man über input Inhalt bestimmen will
    Matrix(const size_t &z, const size_t &s) : zeilen(z), spalten(s) {
        // Zeilen*Spalten weil genau so viele size_t Werte die Matrix hat
        data = new int[zeilen*spalten];
        for (size_t i = 0; i < zeilen*spalten; i++) {
            // Alle Werte der Matrix auf 0 setzen
            data[i] = 0;
        }
    }

    // Desturktor
    ~Matrix() {
        delete[] data;
    }

    // Move Konstruktor
    Matrix(Matrix&& other) noexcept
    : zeilen(other.zeilen), spalten(other.spalten), data(other.data)
    {
        other.data = nullptr;
        other.zeilen = other.spalten = 0;
    }

    Matrix add(const Matrix& x) const {
        Matrix y = Matrix(x.zeilen, x.spalten);

        // Abfrage der Matritzen wichtig für addition
        if (this->zeilen == x.zeilen && this->spalten == x.spalten) {
            for (size_t i = 0; i < zeilen; i++) {
                for (size_t j = 0; j < spalten; j++) {
                    // Neue Matrix = Jeder Wert der alten + übergebene
                    y.data[i*spalten + j] = data[i*spalten + j] + x.data[i*spalten + j];
                }
            }
        }
        else {
            std::cout << "Fehler, nicht gleiche Spalten und Zeilen Anzahl der Matrizen!" << std::endl;
        }
        return y;
    }

    Matrix mult(const Matrix& x) const {

        // Bei Multiplikation verändert sich die Ergebnis Matrix
        Matrix y(this->zeilen, x.spalten);

        // Bei Multiplikation wichtig das Spalten der ersten Matrix == Zeilen der Übergebenen Matrix ist.
        if (this->spalten == x.zeilen) {
            for (size_t i = 0; i < zeilen; i++) {
                for (size_t j = 0; j < x.spalten; j++) {
                    int sum = 0;

                    for (size_t k = 0; k < this->spalten; k++) {
                        // Summiert hier auf weil bei Multiplikation ja Zeile * Spalte durchgeführt wird
                        sum += data[i * this->spalten + k] * x.data[k * x.spalten + j];
                    }
                    // Neue Matrix bekommt sum von oben
                    y.data[i * x.spalten + j] = sum;
                }
            }
        }
        else {
            std::cout << "Fehler, die Matrize 1 muss gleich viele Spalten wie die Matrize 2 Zeilen haben!" << std::endl;
        }

        return y;
    }

};

void mult_time(int minuten) {
    // Zielzeit in Sekunden!
    double zeit_s = 0;
    size_t faktor = 1;

    while (zeit_s <= 60 * minuten) {
        auto start = std::chrono::high_resolution_clock::now();

        Matrix a(100*faktor, 100*faktor);
        Matrix b(100*faktor, 100*faktor);
        Matrix c = a.mult(b);

        auto ende = std::chrono::high_resolution_clock::now();
        std::chrono::duration<double> dauer = ende - start;
        zeit_s = dauer.count();

        // Dynamischer Faktor, weil am anfang noch sehr kurze Änderungen und später länger
        if (zeit_s < 1) faktor *= 2;
        else if (zeit_s < 10) faktor += 5;
        else faktor += 2;

        std::cout << "Matrixgröße: " << "\t" << " | " << "Zeit (s) " << "\n";
        std::cout << faktor*100 << "\t\t" << " | " << dauer.count() << " s" << "\n";
    }
}

void add_time(int minuten) {
    // Zielzeit in Sekunden!
    double zeit_s = 0;
    size_t faktor = 1;

    while (zeit_s <= 60 * minuten) {
        auto start = std::chrono::high_resolution_clock::now();

        Matrix a(100*faktor, 100*faktor);
        Matrix b(100*faktor, 100*faktor);
        Matrix c = a.add(b);

        auto ende = std::chrono::high_resolution_clock::now();
        std::chrono::duration<double> dauer = ende - start;
        zeit_s = dauer.count();

        // Dynamischer Faktor, weil am anfang noch sehr kurze Änderungen und später länger
        if (zeit_s < 1) faktor *= 2;
        else if (zeit_s < 10) faktor += 5;
        else faktor += 2;

        std::cout << "Matrixgröße: " << "\t" << " | " << "Zeit (s) " << "\n";
        std::cout << faktor*100 << "\t\t" << " | " << dauer.count() << " s" << "\n";

    }
}

int main() {

    std::string choice;
    std::cout << "Zeitmessung bei mult oder add?" << std::endl;
    std::cin >> choice;

    if (choice == "mult") {
        mult_time(1);
        mult_time(2);
        mult_time(5);
        mult_time(10);
    }
    else if (choice == "add") {
        add_time(1);
        add_time(2);
        add_time(5);
        add_time(10);
    }
    else
        std::cout << "Optionen: mult | add" << std::endl;


    return 0;
}