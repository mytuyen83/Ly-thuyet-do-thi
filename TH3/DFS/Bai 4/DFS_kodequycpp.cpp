#include <iostream>
#include <fstream>
#include <vector>
#include <stack>
#include <algorithm>
using namespace std;

const int MAX = 100005;
vector<int> ke[MAX]; // danh sách kề
bool visited[MAX];
int n;

// Hàm đọc dữ liệu từ file
void readFile() {
    ifstream fi("DOTHI6.INP");
    if (!fi) {
        cout << "Khong mo duoc file!\n";
        exit(1);
    }

    fi >> n;
    for (int i = 1; i <= n; i++) {
        int v;
        while (fi >> v && v != -1) {
            ke[i].push_back(v);
        }
        // sắp xếp danh sách kề tăng dần để DFS thăm đỉnh nhỏ trước
        sort(ke[i].begin(), ke[i].end());
    }
    fi.close();
}

// DFS không đệ quy từ đỉnh start
vector<int> DFS_kodequy(int start) {
    vector<int> kq;
    stack<int> st;
    st.push(start);
    visited[start] = true;

    while (!st.empty()) {
        int u = st.top(); st.pop();
        kq.push_back(u);
        // duyệt các đỉnh kề theo thứ tự ngược để stack ra đúng thứ tự DFS
        for (auto it = ke[u].rbegin(); it != ke[u].rend(); ++it) {
            int v = *it;
            if (!visited[v]) {
                visited[v] = true;
                st.push(v);
            }
        }
    }
    return kq;
}

int main() {
    readFile();
    for (int i = 1; i <= n; i++) visited[i] = false;

    int start = 1; // có thể thay đổi đỉnh bắt đầu
    vector<int> kq = DFS_kodequy(start);

    cout << kq.size() << "\n";
    for (size_t i = 0; i < kq.size(); i++) {
        cout << kq[i];
        if (i != kq.size() - 1) cout << " ";
    }
    cout << "\n";

    return 0;
}
