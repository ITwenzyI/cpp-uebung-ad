/*
 * File: 04
 * Author: Kilian | ItwenzyI
 * Created: 29.10.2025
 * Description: 
 */
//

#include <iostream>
#include <random>

void Insertionsort(int a[], int n) {
    std::cout << "------------------ INSERTION SORT ------------------" << std::endl;
    int i, j, key;

    for (j = 1; j < n; j++) {
        key = a[j]; //13 -32
        i = j - 1; // 0 1

        for (int b = 0; b < n; b++) {
            std::cout << a[b] << " ";
        }
        std::cout << std::endl;

        std::cout << "a[i]= " << a[i] << " key=" << key << std::endl;
        while (i >= 0 && a[i] < key) {
            a[i + 1] = a[i]; //a2 = 13
            i = i - 1; // 0
        }

        a[i + 1] = key; // a1 = 13
        std::cout << "i=" << i <<" a[i+1]=" << a[i + 1] << std::endl;
    }
}

void Bubblesort(int a[], int n) {
    std::cout << "------------------ BUBBLE SORT ------------------" << std::endl;
    for (int i = n; i > 0; i--) {
        for (int j = 0; j <= i; j++) {
            std::cout << "a[j]=" << a[j] <<" a[j+1]=" << a[j + 1] << std::endl;
            if (a[j] > a[j + 1]) {
                int temp = a[j];
                a[j] = a[j + 1];
                a[j + 1] = temp;
            }
            for (int b = 0; b < n; b++) {
                std::cout << a[b] << " ";
            }
            std::cout << std::endl;
        }
    }
}

void Selectionsort(int a[], int n) {
    std::cout << "------------------ SELECTION SORT ------------------" << std::endl;
    int i, j, min;
    for (i = n-1; i >= 0; i--) {
        min = i;

        for (j = 0; j <= i; j++) {
            std::cout << "a[j]=" << a[j] <<" a[min]=" << a[min] << std::endl;
            if (a[j] > a[min]) {
                min = j;
            }
        } // min = 6

        int temp = a[i];
        a[i] = a[min];
        a[min] = temp;

        for (int b = 0; b < n; b++) {
            std::cout << a[b] << " ";
        }
        std::cout << std::endl;
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


int main() {
    int a[] = {-5, 13, -32, 7, -3, 17, 23, 12, -35, 19};
    //Insertionsort(a, std::size(a));
    //Bubblesort(a, std::size(a));
    //Selectionsort(a, std::size(a));
    quicksort(a, 0, 9);
    for (int i : a) {
        std::cout << i << " ";
    }

    return 0;
}