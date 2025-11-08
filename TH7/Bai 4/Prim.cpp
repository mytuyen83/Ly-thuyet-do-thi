#include <iostream>
#include <vector>
#include <fstream>
#include <queue>
#include <utility>
using namespace std;

struct Canh {
    int u, v, w;
};

int n, m;
vector<pair<int, int>> ke[1001]; // danh sách kề: (đỉnh kề, trọng số)
vector<Canh> MST;

// Hàm đọc dữ liệu
void docDuLieu(const string& tenFile) {
    ifstream fin(tenFile);
    fin >> n >> m;
    for (int i = 0; i < m; i++) {
        int u, v, w;
        fin >> u >> v >> w;
        ke[u].push_back({ v,w });
        ke[v].push_back({ u,w });
    }
    fin.close();
}

// Hàm ghi kết quả MST ra file
void ghiKetQua(const string& tenFile, long long tong) {
    ofstream fout(tenFile);
    fout << MST.size() << " " << tong << "\n";
    for (auto e : MST)
        fout << e.u << " " << e.v << " " << e.w << "\n";
    fout.close();
}

// Hàm Prim
void Prim(int start) {
    vector<int> key(n + 1, 1e9);
    vector<int> parent(n + 1, -1);
    vector<bool> visited(n + 1, false);

    key[start] = 0;
    long long tong = 0;

    // min-heap: (trọng số, đỉnh)
    priority_queue<pair<int, int>, vector<pair<int, int>>, greater<pair<int, int>>> pq;
    pq.push({ 0,start });

    while (!pq.empty()) {
        int u = pq.top().second;
        int w_u = pq.top().first;
        pq.pop();

        if (visited[u]) continue;
        visited[u] = true;

        if (parent[u] != -1) {
            MST.push_back({ parent[u], u, key[u] });
            tong += key[u];
        }

        for (auto p : ke[u]) {
            int v = p.first, w = p.second;
            if (!visited[v] && w < key[v]) {
                key[v] = w;
                parent[v] = u;
                pq.push({ key[v], v });
            }
        }
    }

    ghiKetQua("PRIM.OUT", tong);
}

int main() {
    docDuLieu("PRIM.INP");
    Prim(1); // bắt đầu từ đỉnh 1
    return 0;
}
