/*
 * File: 2
 * Author: Kilian | ItwenzyI
 * Created: 16.10.2025
 * Description: 
 */
//

#include <iostream>
#include <stack>

int function(int n, int m) {
    if (n==0) {
        return m+1;
    }
    if (m==0 && n >= 1) {
        return function(n-1, 1);
    }
    return function(n-1, function(n, m-1));
}

int function2(int n, int m) {
    std::stack<int> stack;
    while (true) {
        if (n == 0) {
            m = m + 1;
            if (stack.empty()) {
                break;
            }
            n = stack.top();
            stack.pop();
        }

        else if (m==0) {
            n = n - 1;
            m = 1;
        }
        else {
            stack.push(n-1);
            m = m - 1;
        }

    }
    return m;
}

int main() {
    std::cout << function2(0, 3) << std::endl; // → 4
    std::cout << function2(1, 1) << std::endl; // → 3
    std::cout << function2(2, 2) << std::endl; // → 7
    std::cout << function2(3, 2) << std::endl; // → 29
    std::cout << function2(3, 3) << std::endl; // → 61
    std::cout << function2(4, 4) << std::endl; // → 29

    return 0;
}