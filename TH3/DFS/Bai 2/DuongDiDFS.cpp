#include <iostream>
#include <fstream>
#include <vector>
#include <algorithm>
using namespace std;

const int MAX = 100005;
vector<int> ke[MAX]; // danh sách kề của mỗi đỉnh
int truoc[MAX]; // lưu nút trước của mỗi đỉnh trong đường đi
bool visited[MAX]; // đánh dấu các đỉnh đã thăm
int n, x, y;
bool found = false; // cờ để dừng DFS khi đã tìm thấy y

// Hàm đọc dữ liệu
void readFile() {
    ifstream fi("DOTHI2.INP");
    if (!fi) {
        cout << "Khong mo duoc file!\n";
        exit(1);
    }

    fi >> n >> x >> y;
    for (int i = 1; i <= n; i++) {
        int u;
        while (fi >> u && u != -1) {
            ke[i].push_back(u);
        }
        sort(ke[i].begin(), ke[i].end()); // sắp xếp tăng để DFS thăm theo thứ tự
    }
    fi.close();
}

// DFS đệ quy từ u
void DFS(int u) {
    visited[u] = true;
    if (u == y) { // nếu tìm thấy đích thì dừng
        found = true;
        return;
    }
    for (int v : ke[u]) {
        if (!visited[v] && !found) {
            truoc[v] = u; // lưu nút trước
            DFS(v);
        }
    }
}

// Hàm xuất đường đi
void Xuat(int start, int end) {
    if (!visited[end]) {
        cout << "Khong co duong di\n";
        return;
    }

    vector<int> duongdi;
    int v = end;
    while (v != start) { // dựng đường đi từ end về start
        duongdi.push_back(v);
        v = truoc[v];
    }
    duongdi.push_back(start); // thêm đỉnh bắt đầu
    reverse(duongdi.begin(), duongdi.end());

    cout << duongdi.size() << "\n";
    for (int val : duongdi) cout << val << " ";
    cout << "\n";
}

int main() {
    readFile();
    fill(visited, visited + MAX, false);
    fill(truoc, truoc + MAX, 0);
    DFS(x);
    Xuat(x, y);
    return 0;
}
