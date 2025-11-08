#include <iostream>
#include <vector>
#include <fstream>
#include <algorithm>
using namespace std;

const int MAXN = 1000;

int n, m;
vector<int> ke[MAXN + 1];
bool daTham[MAXN + 1];
vector<pair<int, int>> cayKhung;

// Hàm DFS tìm cây khung
void DFS(int u) {
    daTham[u] = true;
    for (int v : ke[u]) {
        if (!daTham[v]) {
            cayKhung.push_back({ u, v });
            DFS(v);
        }
    }
}

// Hàm đọc dữ liệu từ file
void docDuLieu() {
    ifstream fin("CAYKHUNG_DFS.INP");
    if (!fin.is_open()) {
        cout << "Khong mo duoc file!\n";
        return;
    }
    fin >> n >> m;
    for (int i = 0; i < m; i++) {
        int u, v;
        fin >> u >> v;
        ke[u].push_back(v);
        ke[v].push_back(u);
    }
    fin.close();

    // Sắp xếp danh sách kề để đảm bảo duyệt theo thứ tự tăng dần
    for (int i = 1; i <= n; i++)
        sort(ke[i].begin(), ke[i].end());
}

// Hàm ghi kết quả ra file
void ghiKetQua() {
    ofstream fout("CAYKHUNG_DFS.OUT");
    fout << cayKhung.size() << "\n";
    for (auto e : cayKhung)
        fout << e.first << " " << e.second << "\n";
    fout.close();
}

int main() {
    docDuLieu();
    DFS(1); // Gọi DFS từ đỉnh 1
    ghiKetQua();
    return 0;
}
