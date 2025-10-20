#include <iostream>
#include <fstream>
#include <vector>
#include <queue>
using namespace std;

const int MAX = 100005;
vector<int> ke[MAX]; // danh sách kề của mỗi đỉnh
bool visited[MAX]; // đánh dấu các đỉnh đã thăm
int n; // số đỉnh

// Hàm đọc dữ liệu từ file
void readFile() {
    ifstream fi("DOTHI3.INP");
    if (!fi) {
        cout << "Khong mo duoc file!\n";
        exit(1);
    }

    fi >> n;
    for (int i = 1; i <= n; i++) {
        int u;
        while (fi >> u && u != -1) {
            ke[i].push_back(u);
        }
    }
    fi.close();
}

// BFS từ một đỉnh, trả về các đỉnh trong 1 thành phần liên thông
vector<int> BFS_c(int start) {
    vector<int> c; // danh sách đỉnh của 1 thành phần liên thông
    queue<int> q;
    q.push(start);
    visited[start] = true;

    while (!q.empty()) {
        int u = q.front(); q.pop();
        c.push_back(u); // thêm đỉnh vào thành phần
        for (int v : ke[u]) {
            if (!visited[v]) {
                visited[v] = true;
                q.push(v);
            }
        }
    }

    return c;
}

// Hàm liệt kê tất cả các thành phần liên thông
void lietke() {
    vector<vector<int>> tatca; // lưu tất cả các thành phần

    for (int i = 1; i <= n; i++) {
        if (!visited[i]) {
            vector<int> c = BFS_c(i);
            tatca.push_back(c);
        }
    }

    // Xuất kết quả
    cout << tatca.size() << "\n";
    for (auto& c : tatca) {
        for (int v : c) {
            cout << v << " ";
        }
        cout << "\n";
    }
}

int main() {
    readFile();
    lietke();
    return 0;
}
