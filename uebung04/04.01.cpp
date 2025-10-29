/*
 * File: 04
 * Author: Kilian | ItwenzyI
 * Created: 29.10.2025
 * Description: 
 */
//

#include <iostream>

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
        while (i >= 0 && a[i] > key) {
            a[i + 1] = a[i]; //a2 = 13
            i = i - 1; // 0
        }

        a[i + 1] = key; // a1 = 13
        std::cout << "i=" << i <<" a[i+1]=" << a[i + 1] << std::endl;
    }
}

void Bubblesort(int a[], int n) {
    std::cout << "------------------ BUBBLE SORT ------------------" << std::endl;
    for (int i = 0; i < n; i++) {
        for (int j = n-2; j >= i; j--) {
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
    for (i = 0; i < n; i++) {
        min = i;

        for (j = i; j < n; j++) {
            std::cout << "a[j]=" << a[j] <<" a[min]=" << a[min] << std::endl;
            if (a[j] < a[min]) {
                min = j;
            }
        }
        int temp = a[i];
        a[i] = a[min];
        a[min] = temp;

        for (int b = 0; b < n; b++) {
            std::cout << a[b] << " ";
        }
        std::cout << std::endl;
    }
}


int main() {
    int a[] = {-5, 13, -32, 7, -3, 17, 23, 12, -35, 19};
    Insertionsort(a, std::size(a));
    Bubblesort(a, std::size(a));
    Selectionsort(a, std::size(a));
    for (int i : a) {
        std::cout << i << " ";
    }

    return 0;
}