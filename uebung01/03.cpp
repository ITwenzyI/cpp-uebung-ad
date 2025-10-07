/*
 * File: 03
 * Author: Kilian | ItwenzyI
 * Created: 07.10.2025
 * Description: 
 */
//
#include <iostream>

class Matrix {
private:
    int zeilen;
    int spalten;
    int *data;
    public:
    Matrix(int z, int s) : zeilen(z), spalten(s) {
        data = new int[zeilen*spalten];
        for (int i = 0; i < zeilen*spalten; i++) {
            data[i] = 0;
        }
    }

    ~Matrix() {
        delete[] data;
    }

    void print() {
        for (int i = 0; i < zeilen; i++) {
            for (int j = 0; j < spalten; j++) {
                std::cout << data[i*spalten + j] << " ";
            }
            std::cout << std::endl;
        }
    }


    void input() {
        std::cout << "Wie viele Zeilen und Spalten hat die Matrix" << std::endl;
        std::cin >> zeilen >> spalten;
        for (int i = 0; i < zeilen; i++) {
            for (int j = 0; j < spalten; j++) {
                std::cout << "Gebe die Zahl für die Matrix an der Position [Zeile, Spalte]: " << i+1 << ", " << j+1 << std::endl;
                std::cin >> data[i*spalten + j];
            }
        }

    }




};

int main() {
    Matrix a(2, 3);
    a.input();
    a.print();

    return 0;
}