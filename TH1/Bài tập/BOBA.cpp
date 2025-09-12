#include <iostream>
#include <string>
#include <vector>
using namespace std;

int main() {
    int T;
    cin >> T;
    while (T--) {
        string s;
        cin >> s;
        int n = s.size();
        if (n < 3) {
            cout << 0 << endl;
            continue;
        }
        vector<int> dem(26 * 26 * 26, 0);
        int kq = 0;
        for (int i = 0; i + 2 < n; i++) {
            int id = (s[i] - 'A') * 26 * 26 + (s[i + 1] - 'A') * 26 + (s[i + 2] - 'A');
            dem[id]++;
            if (dem[id] > kq) kq = dem[id];
        }
        cout << kq << endl;
    }
    return 0;
}
