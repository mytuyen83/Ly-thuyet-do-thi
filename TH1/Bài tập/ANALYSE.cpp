#include <iostream>
#include <vector>
using namespace std;

bool laNguyenTo(int n) {
    if (n < 2) return false;
    for (int i = 2; i * i <= n; i++) {
        if (n % i == 0) return false;
    }
    return true;
}

int main() {
    int N;
    while (cin >> N) {
        vector<int> kq;
        for (int p = 2; p <= N; p++) {
            if (laNguyenTo(p)) {
                int mu = 0, m = N;
                while (m > 0) {
                    mu += m / p;
                    m /= p;
                }
                kq.push_back(mu);
            }
        }
        for (int i = 0; i < (int)kq.size(); i++) {
            cout << kq[i];
            if (i + 1 < (int)kq.size()) cout << " ";
        }
        cout << endl;
    }
    return 0;
}
