
#include <iostream>
using namespace std;

int main() {
    long long N;
    while (cin >> N) {
        long long dem = 0;
        while (N > 0) {
            dem += N / 5;
            N /= 5;
        }
        cout << dem << endl;
    }
    return 0;
}