#include <iostream>
#include <fstream>
#include <vector>
#include <stack>
using namespace std;

int n;
vector<vector<int>> ke; // danh sách kề
int used[7][7]; // đánh dấu cạnh đã dùng
vector<pair<int, int>> ketqua;

void ReadFile() {
    ifstream fi("DOMINO.INP");
    if (!fi.is_open()) {
        cout << "Khong mo duoc file!\n";
        exit(1);
    }
    fi >> n;
    ke.assign(7, {});
    for (int i = 0; i < n; i++) {
        int x, y;
        fi >> x >> y;
        ke[x].push_back(y);
        ke[y].push_back(x);
        used[x][y]++;
        used[y][x]++;
    }
    fi.close();
}

void Euler(int u) {
    stack<int> st;
    vector<int> duongdi;
    st.push(u);
    while (!st.empty()) {
        int x = st.top();
        bool found = false;
        while (!ke[x].empty()) {
            int y = ke[x].back();
            ke[x].pop_back();
            if (used[x][y] > 0) {
                used[x][y]--;
                used[y][x]--;
                st.push(y);
                found = true;
                break;
            }
        }
        if (!found) {
            duongdi.push_back(x);
            st.pop();
        }
    }
    // đảo ngược đường đi
    reverse(duongdi.begin(), duongdi.end());

    for (int i = 0; i + 1 < (int)duongdi.size(); i++) {
        ketqua.push_back({ duongdi[i], duongdi[i + 1] });
    }
}

int main() {
    ReadFile();

    // kiểm tra bậc chẵn
    int bac[7] = { 0 };
    for (int i = 0; i <= 6; i++) {
        for (int j = 0; j <= 6; j++) {
            bac[i] += used[i][j];
        }
        if (bac[i] % 2 != 0) {
            cout << 0 << endl;
            return 0;
        }
    }

    cout << 1 << endl;

    // tìm 1 đỉnh bắt đầu
    int start = 0;
    for (int i = 0; i <= 6; i++) {
        if (bac[i] > 0) {
            start = i;
            break;
        }
    }

    Euler(start);

    for (auto& e : ketqua) {
        cout << e.first << " " << e.second << endl;
    }

    return 0;
}
