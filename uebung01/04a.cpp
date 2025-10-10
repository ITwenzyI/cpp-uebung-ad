/*
 * File: 04a
 * Author: Kilian | ItwenzyI
 * Created: 08.10.2025
 * Description: 
 */
//
#include <iostream>
#include <chrono>       // chrono für Zeitmessung
#include <thread>       // sleep_for

class Matrix {
private:
    int zeilen;
    int spalten;
    int *data;
    public:
    // Konsturktor mit Zeilen und Spalten ohne Inhalt wenn man über input Inhalt bestimmen will
    Matrix(const int &z, const int &s) : zeilen(z), spalten(s) {
        // Zeilen*Spalten weil genau so viele int Werte die Matrix hat
        data = new int[zeilen*spalten];
        for (int i = 0; i < zeilen*spalten; i++) {
            // Alle Werte der Matrix auf 0 setzen
            data[i] = 0;
        }
    }

    // Konstruktor mit vorgegebenen Inhalt in einem Array
    Matrix(int z, int s, const int inhalt[]) : zeilen(z), spalten(s) {
        data = new int[zeilen*spalten];
        for (int i = 0; i < zeilen*spalten; i++) {
            data[i] = inhalt[i];
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

    // Print Funktion
    void print() const {
        for (int i = 0; i < zeilen; i++) {
            for (int j = 0; j < spalten; j++) {
                std::cout << data[i*spalten + j] << " ";
            }
            std::cout << std::endl;
        }
    }


    // Input Funktion mit Abfrage von Zeilen und Spalten. Angepasste Matrix
    void input() {
        std::cout << "Wie viele Zeilen hat die Matrix" << std::endl;
        std::cin >> zeilen;
        std::cout << "Wie viele Spalten hat die Matrix" << std::endl;
        std::cin >> spalten;
        for (int i = 0; i < zeilen; i++) {
            for (int j = 0; j < spalten; j++) {
                std::cout << "Gebe die Zahl für die Matrix an der Position [Zeile, Spalte]: " << i+1 << ", " << j+1 << std::endl;
                std::cin >> data[i*spalten + j];
            }
        }

    }


    Matrix add(const Matrix& x) const {
        // Start Punkt der Zeitmessung
        auto start = std::chrono::high_resolution_clock::now();
        // Counter Variable für die Zugriffe
        int counter = 0;

        ++counter;
        Matrix y = Matrix(x.zeilen, x.spalten);

        ++counter;
        // Abfrage der Matritzen wichtig für addition
        if (this->zeilen == x.zeilen && this->spalten == x.spalten) {
            ++counter;
            for (int i = 0; i < zeilen; i++) {
                ++counter;
                for (int j = 0; j < spalten; j++) {
                    ++counter;
                    // Neue Matrix = Jeder Wert der alten + übergebene
                    y.data[i*spalten + j] = data[i*spalten + j] + x.data[i*spalten + j];
                }
            }
        }
        else {
            ++counter;
            std::cout << "Fehler, nicht gleiche Spalten und Zeilen Anzahl der Matrizen!" << std::endl;
        }
        ++counter;
        std::cout << "Counter Add: " << counter << std::endl;
        auto ende = std::chrono::high_resolution_clock::now();
        auto dauer = std::chrono::duration_cast<std::chrono::milliseconds>(ende - start);
        std::cout << "Verstrichene Zeit Add: " << dauer.count() << " ms" << std::endl;
        return y;
    }

    Matrix mult(const Matrix& x) const {
        // Start der Zeitmessung
        auto start = std::chrono::high_resolution_clock::now();
        // Counter für Zugriffe
        int counter = 0;

        ++counter;
        // Bei Multiplikation verändert sich die Ergebnis Matrix
        Matrix y(this->zeilen, x.spalten);

        // Test ob Zeit in ms funktioniert
        // std::this_thread::sleep_for(std::chrono::milliseconds(500));

        // Bei Multiplikation wichtig das Spalten der ersten Matrix == Zeilen der Übergebenen Matrix ist.
        ++counter;
        if (this->spalten == x.zeilen) {
            ++counter;
            for (int i = 0; i < zeilen; i++) {
                ++counter;
                for (int j = 0; j < x.spalten; j++) {
                    ++counter;
                    int sum = 0;

                    ++counter;
                    for (int k = 0; k < this->spalten; k++) {
                        ++counter;
                        // Summiert hier auf weil bei Multiplikation ja Zeile * Spalte durchgeführt wird
                        sum += data[i * this->spalten + k] * x.data[k * x.spalten + j];
                    }
                    ++counter;
                    // Neue Matrix bekommt sum von oben
                    y.data[i * x.spalten + j] = sum;
                }
            }
        }
        else {
            ++counter;
            std::cout << "Fehler, die Matrize 1 muss gleich viele Spalten wie die Matrize 2 Zeilen haben!" << std::endl;
        }

        ++counter;
        std::cout << "Counter Mult: " << counter << std::endl;
        auto ende = std::chrono::high_resolution_clock::now();
        auto dauer = std::chrono::duration_cast<std::chrono::milliseconds>(ende - start);
        std::cout << "Verstrichene Zeit Mult: " << dauer.count() << " ms" << std::endl;
        return y;
    }





};

int main() {
    int inhalt_a[4] = {1, 2, 3, 4};
    Matrix a(2, 2, inhalt_a);
    //a.input(); // (1, 2 | 3, 4)
    a.print();
    int inhalt_b[6] = {1, 2, 3, 4, 5, 6};
    Matrix b(2, 3, inhalt_b);
    //b.input(); // (1, 2, 3 | 4, 5, 6)
    b.print();
    Matrix c = a.mult(b);
    c.print();
    Matrix d = a.add(b);
    d.print();


    return 0;
}