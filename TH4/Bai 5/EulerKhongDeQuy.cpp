#include <iostream>
#include <fstream>
#include <vector>
#include <stack>
using namespace std;

int n;
vector<vector<int>> ke;

// Đọc dữ liệu từ file
void ReadFile() {
    ifstream fi("DOTHI_EULER.INP");
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

// Kiểm tra có phải đồ thị Euler không (tất cả đỉnh bậc chẵn)
bool LaDoThiEuler() {
    for (int i = 1; i <= n; i++) {
        int bac = 0;
        for (int j = 1; j <= n; j++) bac += ke[i][j];
        if (bac % 2 != 0) return false;
    }
    return true;
}

// Tìm chu trình Euler (không đệ quy)
vector<int> ChuTrinhEuler(int start) {
    vector<int> kq;
    stack<int> st;
    vector<vector<int>> g = ke; // copy ma trận để xoá cạnh

    st.push(start);

    while (!st.empty()) {
        int u = st.top();
        bool coCanh = false;
        for (int v = 1; v <= n; v++) {
            if (g[u][v] > 0) {
                coCanh = true;
                st.push(v);
                g[u][v]--;
                g[v][u]--;
                break;
            }
        }
        if (!coCanh) {
            kq.push_back(u);
            st.pop();
        }
    }

    return kq; // đã có chu trình Euler
}

int main() {
    ReadFile();

    if (!LaDoThiEuler()) {
        cout << 0 << endl;
    }
    else {
        cout << 1 << endl;
        vector<int> ct = ChuTrinhEuler(1); // bắt đầu từ đỉnh 1
        for (int i = ct.size() - 1; i >= 0; i--) { // đảo ngược kết quả
            cout << ct[i];
            if (i > 0) cout << " ";
        }
        cout << endl;
    }

    return 0;
}
