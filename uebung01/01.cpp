/*
 * File: 01a
 * Author: Kilian | ItwenzyI
 * Created: 07.10.2025
 * Description: 
 */
//

#include <iostream>

int ggT(int a, int b) {
    int r;
    do {
        r = a % b;
        a = b;
        b = r;
    } while (r != 0);
    return a;
}

int ggT_rek(int a, int b) {
    if (b == 0)
        return a;
    return ggT_rek(b, a % b);
}

int kgV(int a, int b) {
    int r;
    int i = 0;
    do {
        r = (a* ++i) % b;
    } while (r != 0);
    return a*i;
}

void print_values() {
    for (int i = 30; i <= 40; i++) {
        for (int j = 40; j >= 30; j--) {
            std::cout << "a=" << i << " b=" << j << " ggT=" << ggT(i,j) << " kgV=" << kgV(i,j) << " a*b=" << i*j << std::endl;
        }
    }
}

int main() {
    print_values();

    return 0;
}