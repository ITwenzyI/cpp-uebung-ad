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
    for (int i = 0; i <= 4; i++) {
        for (int j = 0; j <= 4; j++) {
            std::cout << "n:" << i << " m:" << j << " :";
            std::cout << function(i,j) << std::endl;
            // Ab n=4 und m=1 bricht das Programm ab, da es zu groß wird.
        }
    }


    return 0;
}