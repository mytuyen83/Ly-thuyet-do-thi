#include <iostream>
#include <fstream>
#include <vector>
#include <stack>
#include <algorithm>
using namespace std;

int n;
vector<vector<int>> ke;

void ReadFile() {
    ifstream fi("DOTHI_NUAEULER.INP");
    if (!fi.is_open()) {
        cout << "Khong mo duoc file!\n";
        exit(1);
    }
    fi >> n;
    ke.assign(n + 1, vector<int>(n + 1, 0));
    for (int i = 1; i <= n; i++) {
        for (int j = 1; j <= n; j++) {
            fi >> ke[i][j];
        }
    }
    fi.close();
}

bool LaDoThiNuaEuler(int& start) {
    vector<int> bac(n + 1, 0);
    vector<int> odd;
    for (int i = 1; i <= n; i++) {
        int d = 0;
        for (int j = 1; j <= n; j++) d += ke[i][j];
        bac[i] = d;
        if (d % 2 == 1) odd.push_back(i);
    }
    if (odd.size() == 2) {
        start = odd[0]; // bắt đầu từ 1 trong 2 đỉnh lẻ
        return true;
    }
    return false;
}

vector<int> DuongDiEuler(int start) {
    vector<int> kq;
    vector<vector<int>> g = ke;
    stack<int> st;
    st.push(start);

    while (!st.empty()) {
        int u = st.top();
        int vFound = -1;
        for (int v = 1; v <= n; v++) {
            if (g[u][v] > 0) { vFound = v; break; }
        }
        if (vFound == -1) {
            kq.push_back(u);
            st.pop();
        }
        else {
            g[u][vFound]--;
            g[vFound][u]--;
            st.push(vFound);
        }
    }
    reverse(kq.begin(), kq.end());
    return kq;
}

int main() {
    ReadFile();
    int start;
    if (!LaDoThiNuaEuler(start)) {
        cout << 0 << endl;
    }
    else {
        cout << 1 << endl;
        vector<int> dd = DuongDiEuler(start);
        for (int i = 0; i < (int)dd.size(); i++) {
            cout << dd[i];
            if (i < (int)dd.size() - 1) cout << " ";
        }
        cout << endl;
    }
    return 0;
}
