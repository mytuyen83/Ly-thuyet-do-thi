#include <iostream>
#include <fstream>
#include <vector>
#include <algorithm>
using namespace std;

int n, x; // n = số đỉnh, x = đỉnh bắt đầu DFS
vector<vector<int>> ke; // danh sách kề của đồ thị
vector<char> visited; // đánh dấu đỉnh đã thăm

// Hàm đọc dữ liệu từ file
void readfile() {
    ifstream fi("DOTHI1.INP");
    if (!fi.is_open()) {
        cout << "Khong mo duoc file!\n";
        exit(1);
    }

    fi >> n >> x; 
    ke.assign(n + 1, {}); // khởi tạo danh sách kề

    for (int i = 1; i <= n; i++) {
        int v;
        while (fi >> v) {
            if (v == -1) break; // kết thúc danh sách kề của đỉnh i
            ke[i].push_back(v);
        }
        sort(ke[i].begin(), ke[i].end()); // sắp xếp đỉnh kề tăng dần để DFS thăm theo thứ tự
    }
    fi.close();
}

// DFS đệ quy từ đỉnh u
void DFS(int u, vector<int>& kq) {
    visited[u] = 1; // đánh dấu đã thăm
    kq.push_back(u); // thêm đỉnh vào kết quả
    for (int v : ke[u]) { // duyệt các đỉnh kề
        if (!visited[v]) DFS(v, kq); // nếu chưa thăm, gọi DFS đệ quy
    }
}

int main() {
    readfile();                 
    visited.assign(n + 1, 0);   
    vector<int> kq;          

    DFS(x, kq); 

    cout << kq.size() << "\n";
    for (int v : kq) cout << v << " ";
    cout << "\n";
    return 0;
}
