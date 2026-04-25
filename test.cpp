// Однострочный комментарий
#include <iostream>
using namespace std;

/*
Многострочный комментарий
Описание программы
*/

int add(int x, int y) {
    return x + y; // возвращаем сумму
}

int main() {
    int a = 5;    // первое число
    int b = 3;    // второе число
    int result;

    if (a > 0 && b > 0) {
        result = add(a, b); /* вызов функции */
    }
    else {
        result = 0;
    }

    for (int i = 0; i < 3; i++) {
        cout << i << endl;
    }

    return 0;
}