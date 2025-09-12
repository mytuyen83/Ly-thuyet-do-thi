#include <iostream>
#include <vector>
using namespace std;

int main() {
    int N;
    cin >> N;
    vector<int> danhdau(N + 1, 0);
    bool hople = true;

    for (int i = 0; i < N; i++) {
        int x; cin >> x;
        if (x < 1 || x > N) {
            hople = false;
        }
        else {
            if (danhdau[x] == 1) {
                hople = false;
            }
            danhdau[x] = 1;
        }
    }

    if (hople) cout << "YES";
    else cout << "NO";

    return 0;
}
