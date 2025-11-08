#include <iostream>
#include <vector>
#include <queue>
#include <fstream>
#include <algorithm>
using namespace std;

const int MAXN = 1000;

int n, m;
vector<int> ke[MAXN + 1];
bool daTham[MAXN + 1];
vector<pair<int, int>> cayKhung;

// Hàm BFS tìm cây khung
void BFS(int start) {
    queue<int> q;
    daTham[start] = true;
    q.push(start);

    while (!q.empty()) {
        int u = q.front(); q.pop();
        for (int v : ke[u]) {
            if (!daTham[v]) {
                daTham[v] = true;
                cayKhung.push_back({ u, v });
                q.push(v);
            }
        }
    }
}

// Hàm đọc dữ liệu từ file
void docDuLieu() {
    ifstream fin("CAYKHUNG_BFS.INP");
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

    // Sắp xếp danh sách kề để duyệt theo thứ tự tăng dần
    for (int i = 1; i <= n; i++)
        sort(ke[i].begin(), ke[i].end());
}

// Hàm ghi kết quả ra file
void ghiKetQua() {
    ofstream fout("CAYKHUNG_BFS.OUT");
    fout << cayKhung.size() << "\n";
    for (auto e : cayKhung)
        fout << e.first << " " << e.second << "\n";
    fout.close();
}

int main() {
    docDuLieu();
    BFS(1); // Gọi BFS từ đỉnh 1
    ghiKetQua();
    return 0;
}
