#include <iostream>
#include <fstream>
using namespace std;
int main() {
    char line[10001];
    int tong = 0;
    while (cin.getline(line, 10000, '\n')) {
        int d = 0, a, tmp;
        int len = strlen(line);
        while (d < len) {
            sscanf(line + d, "%d%n", &a, &tmp);
            tong += a;
            d += tmp;
        }
    }
    cout << tong << endl;
    return 0;
}