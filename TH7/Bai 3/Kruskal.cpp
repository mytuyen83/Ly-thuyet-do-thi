#include <iostream>
#include <vector>
#include <algorithm>
#include <fstream>

using namespace std;

// Cấu trúc lưu cạnh
struct Canh {
    int u, v, w;
};

// Biến toàn cục
int n, m;                    // n: số đỉnh, m: số cạnh
vector<Canh> edges;          // Danh sách tất cả các cạnh
vector<Canh> MST;            // Danh sách cạnh thuộc MST
int parent[1001];            // Mảng Union-Find

// Hàm tìm tập cha của đỉnh x (Find với path compression)
int timCha(int x) {
    if (parent[x] == x) return x;
    return parent[x] = timCha(parent[x]);
}

// Hàm hợp nhất hai tập (Union)
void hopNhat(int x, int y) {
    int fx = timCha(x);
    int fy = timCha(y);
    if (fx != fy) parent[fx] = fy;
}

// Hàm đọc dữ liệu từ file
void docDuLieu(const string& tenFile) {
    ifstream fin(tenFile);
    if (!fin.is_open()) {
        cout << "Khong mo duoc file!\n";
        return;
    }
    fin >> n >> m;
    edges.resize(m);
    for (int i = 0; i < m; i++) {
        fin >> edges[i].u >> edges[i].v >> edges[i].w;
    }
    fin.close();
}

// Hàm ghi kết quả ra file
void ghiKetQua(const string& tenFile, long long tong) {
    ofstream fout(tenFile);
    if (!fout.is_open()) {
        cout << "Khong mo duoc file!\n";
        return;
    }
    fout << MST.size() << " " << tong << "\n";
    for (auto e : MST) {
        fout << e.u << " " << e.v << " " << e.w << "\n";
    }
    fout.close();
}

// Hàm Kruskal tìm cây khung
void Kruskal() {
    // Sắp xếp cạnh theo trọng số tăng dần
    sort(edges.begin(), edges.end(), [](Canh a, Canh b) { return a.w < b.w; });

    // Khởi tạo Union-Find
    for (int i = 1; i <= n; i++) parent[i] = i;

    long long tong = 0;

    for (auto e : edges) {
        int fu = timCha(e.u);
        int fv = timCha(e.v);
        if (fu != fv) {          // Nếu hai đỉnh chưa cùng tập → thêm vào MST
            MST.push_back(e);
            tong += e.w;
            hopNhat(fu, fv);     // Hợp nhất hai tập
            if (MST.size() == n - 1) break; // đủ n-1 cạnh thì dừng
        }
    }

    ghiKetQua("KRUSKAL.OUT", tong);
}

int main() {
    docDuLieu("KRUSKAL.INP");
    Kruskal();                 
    return 0;
}
