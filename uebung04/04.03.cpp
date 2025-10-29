/*
 * File: 04
 * Author: Kilian | ItwenzyI
 * Created: 29.10.2025
 * Description: 
 */
//

#include <iostream>
#include <random>
#include <chrono>


void random_int_folge(int a[], int n) {
    std::random_device rd;
    std::mt19937 gen(rd());
    std::uniform_int_distribution<> dist(0, n-1);

    for (int i = 0; i < n; i++) {
        a[i] = dist(gen);
    }
}

void Bubblesort(int a[], int n) {
    std::cout << "------------------ BUBBLE SORT ------------------" << std::endl;
    for (int i = n; i > 0; i--) {
        for (int j = 0; j <= i; j++) {
            //std::cout << "a[j]=" << a[j] <<" a[j+1]=" << a[j + 1] << std::endl;
            if (a[j] > a[j + 1]) {
                int temp = a[j];
                a[j] = a[j + 1];
                a[j + 1] = temp;
            }
            // for (int b = 0; b < n; b++) {
            //     std::cout << a[b] << " ";
            // }
            // std::cout << std::endl;
        }
    }
}





void swap(int &a, int &b) {
    int temp = b;
    b = a;
    a = temp;
}


void preparePartition(int a[], int f, int l, int &p) {

    std::random_device rd;
    std::mt19937 gen(rd());
    std::uniform_int_distribution<> dist(f, l);

    int zufall = dist(gen);
    std::cout << zufall << std::endl;
    swap(a[f], a[zufall]);


    int pivot = a[f]; p = f-1;
    for (int i = f; i <= l; i++) {
        if (a[i] <= pivot) {
            p++;
            swap(a[i], a[p]);
        }
    }

    swap(a[f], a[p]);
}

void quicksort(int a[], int f, int l) {
    int part;
    if (f<l) {
        preparePartition(a, f, l, part);
        quicksort(a, f, part-1);
        quicksort(a, part+1, l);
    }
}

void testing_bubblesort(int a[], int n) {
    size_t total_numbers = 0;
    auto start = std::chrono::high_resolution_clock::now();

    while (true) {
        random_int_folge(a, n);
        Bubblesort(a, n);
        total_numbers += n;

        auto now = std::chrono::high_resolution_clock::now();
        std::chrono::duration<double> elapsed = now - start;
        if (elapsed.count() >= 60.0) break;
    }

    auto end = std::chrono::high_resolution_clock::now();
    std::chrono::duration<double> duration = end - start;

    std::cout << "\n--- BUBBLESORT ---\n";
    std::cout << "n = " << n << "\n";
    std::cout << "Dauer: " << duration.count() << " Sekunden\n";
    std::cout << "Sortierte Zahlen insgesamt: " << total_numbers;
    std::cout << "\n";
}

void testing_quicksort(int a[], int n) {
    size_t total_numbers = 0;
    auto start = std::chrono::high_resolution_clock::now();

    while (true) {
        random_int_folge(a, n);
        quicksort(a, 0, n - 1);
        total_numbers += n;

        auto now = std::chrono::high_resolution_clock::now();
        std::chrono::duration<double> elapsed = now - start;
        if (elapsed.count() >= 60.0) break;
    }

    auto end = std::chrono::high_resolution_clock::now();
    std::chrono::duration<double> duration = end - start;

    std::cout << "\n--- QUICKSORT ---\n";
    std::cout << "n = " << n << "\n";
    std::cout << "Dauer: " << duration.count() << " Sekunden\n";
    std::cout << "Sortierte Zahlen insgesamt: " << total_numbers;
    std::cout << "\n";
}


int main() {
    int n = 10000;
    int *a = new int[n];
    testing_bubblesort(a, n);
    testing_quicksort(a, n);




    delete[] a;

    return 0;
}