#include <iostream>
using namespace std;int add(int x, int y) {
return x + y;
}int main() {
int a = 5;
int b = 3;
int result;if (a > 0 && b > 0) {
result = add(a, b);
}
else {
result = 0;
}for (int i = 0; i < 3; i++) {
cout << i << endl;
}return 0;
}