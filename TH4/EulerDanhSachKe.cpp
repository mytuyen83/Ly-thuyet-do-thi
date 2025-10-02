#include <iostream>
#include <fstream>
#include <vector>
#include <stack>
#include <list>
using namespace std;

int n;
vector<list<int>> ke; // danh sách kề

// Đọc dữ liệu từ file (ma trận kề) rồi chuyển sang danh sách kề
void ReadFile() {
    ifstream fi("DOTHI_EULER.INP");
    if (!fi.is_open()) {
        cout << "Khong mo duoc file!\n";
        exit(1);
    }
    fi >> n;
    ke.assign(n + 1, list<int>());
    for (int i = 1; i <= n; i++) {
        for (int j = 1; j <= n; j++) {
            int x; fi >> x;
            if (x > 0) {
                for (int k = 0; k < x; k++) { // nếu có nhiều cạnh song song
                    ke[i].push_back(j);
                }
            }
        }
    }
    fi.close();
}

// Kiểm tra Euler: tất cả bậc chẵn
bool LaDoThiEuler() {
    for (int i = 1; i <= n; i++) {
        if (ke[i].size() % 2 != 0) return false;
    }
    return true;
}

// Chu trình Euler (không đệ quy) trên danh sách kề
vector<int> ChuTrinhEuler(int start) {
    vector<int> kq;
    stack<int> st;
    vector<list<int>> g = ke; // copy để xoá cạnh

    st.push(start);

    while (!st.empty()) {
        int u = st.top();
        if (!g[u].empty()) {
            int v = g[u].front(); // lấy 1 đỉnh kề
            g[u].pop_front();
            g[v].remove(u); // xoá cạnh đối xứng
            st.push(v);
        }
        else {
            kq.push_back(u);
            st.pop();
        }
    }

    return kq;
}

int main() {
    ReadFile();

    if (!LaDoThiEuler()) {
        cout << 0 << endl;
    }
    else {
        cout << 1 << endl;
        vector<int> ct = ChuTrinhEuler(1); // bắt đầu từ đỉnh 1
        for (int i = ct.size() - 1; i >= 0; i--) {
            cout << ct[i];
            if (i > 0) cout << " ";
        }
        cout << endl;
    }

    return 0;
}
