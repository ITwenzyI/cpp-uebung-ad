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


    Matrix add(const Matrix& x) {
        Matrix y = Matrix(x.zeilen, x.spalten);

        if (this->zeilen == x.zeilen && this->spalten == x.spalten) {
            for (int i = 0; i < zeilen; i++) {
                for (int j = 0; j < spalten; j++) {
                    y.data[i*spalten + j] = data[i*spalten + j] + x.data[i*zeilen + j];
                }
            }
        }
        else {
            std::cout << "Fehler, nicht gleiche Spalten und Zeilen Anzahl der Matrizen!" << std::endl;
        }
        return y;
    }

    Matrix mult(const Matrix& x) {
        Matrix y(this->zeilen, x.spalten);

        if (this->spalten == x.zeilen) {
            for (int i = 0; i < zeilen; i++) {
                for (int j = 0; j < x.spalten; j++) {
                    int sum = 0;

                    for (int k = 0; k < this->spalten; k++) {
                        sum += data[i * this->spalten + k] * x.data[k * x.spalten + j];
                    }
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

int main() {
    Matrix a(2, 2);
    a.input(); // (1, 2 | 3, 4)
    a.print();
    Matrix b(2, 3);
    b.input(); // (1, 2, 3 | 4, 5, 6)
    b.print();
    Matrix c = a.mult(b);
    c.print();

    return 0;
}