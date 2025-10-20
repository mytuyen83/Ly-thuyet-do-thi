#include <iostream>
#include <fstream>
#include <vector>
#include <queue>
using namespace std;

const int MAX = 100005;
vector<int> ke[MAX]; // danh sách kề của mỗi đỉnh
bool visited[MAX]; // đánh dấu các đỉnh đã thăm
int n, x, y, z;

// Hàm đọc dữ liệu từ file
void readFile() {
    ifstream fi("DOTHI4.INP");
    if (!fi) {
        cout << "Khong mo duoc file!\n";
        exit(1);
    }
    fi >> n >> x >> y >> z;
    for (int i = 1; i <= n; i++) {
        int u;
        while (fi >> u && u != -1) ke[i].push_back(u);
    }
    fi.close();
}

// BFS từ start, đánh dấu visited
void BFS(int start) {
    queue<int> q;
    q.push(start);
    visited[start] = true;

    while (!q.empty()) {
        int u = q.front(); q.pop();
        for (int v : ke[u]) {
            if (!visited[v]) {
                visited[v] = true;
                q.push(v); // thêm đỉnh kề chưa thăm vào queue
            }
        }
    }
}

// Kiểm tra cạnh cầu
bool CanhCau(int u, int v) {
    // tạm xóa cạnh u-v
    for (auto it = ke[u].begin(); it != ke[u].end(); ++it) {
        if (*it == v) { ke[u].erase(it); break; }
    }
    for (auto it = ke[v].begin(); it != ke[v].end(); ++it) {
        if (*it == u) { ke[v].erase(it); break; }
    }

    fill(visited, visited + n + 1, false);
    BFS(u);
    bool result = !visited[v]; // nếu v không thăm được → là cầu

    // thêm lại cạnh
    ke[u].push_back(v);
    ke[v].push_back(u);
    return result;
}

// Kiểm tra đỉnh khớp
bool DinhKhop(int node) {
    fill(visited, visited + n + 1, false);
    visited[node] = true; // bỏ qua đỉnh cần kiểm tra

    // tìm 1 đỉnh khác node để BFS
    int start = 1;
    if (start == node) start = 2;
    BFS(start);

    for (int i = 1; i <= n; i++) {
        if (!visited[i]) return true; // có đỉnh chưa thăm → node là đỉnh khớp
    }
    return false; // tất cả đỉnh còn lại đã thăm → không phải đỉnh khớp
}

int main() {
    readFile();
    if (CanhCau(x, y)) cout << "canh cau\n";
    else cout << "khong la canh cau\n";
    if (DinhKhop(z)) cout << "dinh khop\n";
    else cout << "khong la dinh khop\n";
    return 0;
}