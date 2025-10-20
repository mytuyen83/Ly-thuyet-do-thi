#include <iostream>
#include <fstream>
#include <vector>
#include <queue>
#include <algorithm>
using namespace std;

const int MAX = 100005;
vector<int> ke[MAX]; // danh sách kề của mỗi đỉnh
int truoc[MAX]; // lưu nút trước của mỗi đỉnh trong đường đi
bool visited[MAX];// đánh dấu các đỉnh đã thăm
int n, x, y; // số đỉnh, đỉnh xuất phát và đích

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
    }
    fi.close();
}

// Hàm BFS tìm đường đi từ đỉnh start
void BFS(int start) {
    queue<int> q;
    q.push(start);
    visited[start] = true;
    truoc[start] = 0; // 0 nghĩa là không có nút trước

    while (!q.empty()) {
        int u = q.front(); q.pop();
        for (int v : ke[u]) {
            if (!visited[v]) {
                visited[v] = true;
                truoc[v] = u; // lưu nút trước để dựng đường đi sau
                q.push(v);
            }
        }
    }
}

void Xuat(int start, int end) {
    if (!visited[end]) {
        cout << "Khong co duong di\n";
        return;
    }

    vector<int> duongdi;
    for (int v = end; v != 0; v = truoc[v]) { // dựng đường đi từ end về start
        duongdi.push_back(v);
    }
    reverse(duongdi.begin(), duongdi.end()); // đảo ngược để bắt đầu từ start

    cout << duongdi.size() << "\n";
    for (int v : duongdi) {
        cout << v << " ";
    }
    cout << "\n";
}

int main() {
    readFile();
    BFS(x);
    Xuat(x, y);
    return 0;
}
