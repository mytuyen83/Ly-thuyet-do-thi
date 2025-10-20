#include <iostream>
#include <fstream>
#include <vector>
using namespace std;

const int MAX = 100005;
vector<int> ke[MAX]; // danh sách kề
int n;
int color[MAX]; // 0 hoặc 1, -1 nghĩa là chưa tô màu
bool ok = true; // cờ kiểm tra phân đôi

// Hàm đọc dữ liệu từ file
void readFile() {
    ifstream fi("DOTHI5.INP");
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
    }
    fi.close();
}

// DFS kiểm tra phân đôi từ đỉnh u
void DFS(int u) {
    for (int v : ke[u]) {
        if (color[v] == -1) {
            color[v] = 1 - color[u]; // tô màu đối
            DFS(v);
        }
        else if (color[v] == color[u]) { // xung đột màu
            ok = false;
            return;
        }
    }
}

int main() {
    readFile();
    for (int i = 1; i <= n; i++) color[i] = -1;

    for (int i = 1; i <= n; i++) {
        if (color[i] == -1) {
            color[i] = 0; // tô màu 0 cho đỉnh chưa thăm
            DFS(i);
        }
    }

    if (ok) cout << "Do thi phan doi\n";
    else cout << "Do thi khong phan doi\n";

    return 0;
}
