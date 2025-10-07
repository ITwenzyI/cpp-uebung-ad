/*
 * File: 02
 * Author: Kilian | ItwenzyI
 * Created: 07.10.2025
 * Description: 
 */
//
#include <iostream>
#include <random>

class Feld {

    private:
    int* daten;
    int groeße;

    public:

    explicit Feld(int n) {
        groeße = n;
        daten = new int[n];
        for (int i = 0; i < n; ++i)
            daten[i] = 0;
    }

    ~Feld() {
        delete[] daten;
    }

    void FillRandom() {
        std::random_device rd;
        std::mt19937 gen(rd());
        std::uniform_int_distribution<> dist(0, 1000);

        for (int i = 0; i < this->groeße; ++i)
            daten[i] = dist(gen);
    }

    void print () const {
        for (int i = 0; i < this->groeße; i++) {
            std::cout << daten[i] << " ";
        }
        std::cout << std::endl;
    }

    int min() const {
        int min = daten[0];
        for (int i = 0; i < this->groeße; i++) {
            if (daten[i] < min) {
                min = daten[i];
            }
        }
        return min;
    }

    int max() const {
        int max = daten[0];
        for (int i = 0; i < this->groeße; i++) {
            if (daten[i] > max) {
                max = daten[i];
            }
        }
        return max;
    }

    int avg()const {
        int sum = 0;
        for (int i = 0; i < this->groeße; i++) {
            sum += daten[i];
        }
        return sum/this->groeße;
    }

};

int main() {
    Feld f(5);
    f.FillRandom();
    f.print();
    std::cout << f.min() << " " << f.max() << " " << f.avg() << std::endl;


    return 0;
}