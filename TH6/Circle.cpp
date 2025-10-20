#include <iostream>
#include <fstream>
#include <vector>
#include <cmath>
#include <limits>
using namespace std;

// Cấu trúc lưu thông tin mỗi vòng tròn
struct HinhTron {
    double x, y, r; // Tọa độ tâm (x, y) và bán kính r
};

// Đọc dữ liệu
void DocFile(int& N, int& S, int& T, vector<HinhTron>& dsVong) {
    ifstream fin("CIRCLE.INP");
    fin >> N >> S >> T; // Số vòng, đỉnh xuất phát, đỉnh đích
    dsVong.resize(N + 1);
    for (int i = 1; i <= N; ++i)
        fin >> dsVong[i].x >> dsVong[i].y >> dsVong[i].r;
    fin.close();
}

// Tính khoảng cách giữa hai vòng tròn (0 nếu giao nhau hoặc tiếp xúc)
double KhoangCach(const HinhTron& a, const HinhTron& b) {
    double d = sqrt((a.x - b.x) * (a.x - b.x) + (a.y - b.y) * (a.y - b.y));
    double kc = d - a.r - b.r;
    return kc < 0 ? 0 : kc;
}

// Ghi kết quả
void GhiFile(int coDuong, int tongBuoc, int soVong, const vector<int>& duong, const vector<int>& trangThai) {
    ofstream fout("CIRCLE.OUT");
    if (!coDuong) { // Không có đường đi
        fout << 0;
        fout.close();
        return;
    }
    fout << 1 << "\n"; // Có đường đi
    fout << tongBuoc << " " << soVong << "\n"; // Tổng bước và số vòng tròn đi qua
    for (int i = 0; i < soVong; ++i)
        fout << duong[i] << " " << trangThai[i] << "\n";
    fout.close();
}

// Tìm đường đi ngắn nhất giữa hai vòng tròn theo thuật toán Dijkstra
void TimDuongDi(int N, int S, int T, const vector<HinhTron>& dsVong) {
    const double INF = numeric_limits<double>::infinity();
    vector<vector<double>> kc(N + 1, vector<double>(N + 1, INF));

    // Ma trận khoảng cách giữa các vòng
    for (int i = 1; i <= N; ++i)
        for (int j = 1; j <= N; ++j)
            if (i != j)
                kc[i][j] = KhoangCach(dsVong[i], dsVong[j]);

    // Mảng chi phí và mảng truy vết (Dijkstra)
    vector<double> chiPhi(N + 1, INF);
    vector<int> truoc(N + 1, -1);
    vector<bool> daXet(N + 1, false);
    chiPhi[S] = 0;

    // Dijkstra cơ bản
    for (int k = 1; k <= N; ++k) {
        int u = -1;
        double minCost = INF;
        for (int i = 1; i <= N; ++i)
            if (!daXet[i] && chiPhi[i] < minCost) {
                minCost = chiPhi[i];
                u = i;
            }
        if (u == -1) break;
        daXet[u] = true;

        // Cập nhật khoảng cách tới các đỉnh kề
        for (int v = 1; v <= N; ++v)
            if (!daXet[v] && chiPhi[v] > chiPhi[u] + kc[u][v]) {
                chiPhi[v] = chiPhi[u] + kc[u][v];
                truoc[v] = u;
            }
    }

    // Không tìm được đường
    if (chiPhi[T] == INF) {
        GhiFile(0, 0, 0, {}, {});
        return;
    }

    // Truy vết đường đi ngắn nhất
    vector<int> duong;
    for (int v = T; v != -1; v = truoc[v])
        duong.push_back(v);
    reverse(duong.begin(), duong.end());

    // Xác định trạng thái từng bước: 0 = chạm, 1 = bay
    vector<int> trangThai(duong.size(), 0);
    int tongBuoc = 0;
    for (size_t i = 0; i + 1 < duong.size(); ++i) {
        double d = KhoangCach(dsVong[duong[i]], dsVong[duong[i + 1]]);
        trangThai[i] = (d == 0 ? 0 : 1);
        if (d > 0) tongBuoc++;
    }

    GhiFile(1, tongBuoc, (int)duong.size(), duong, trangThai);
}

int main() {
    int N, S, T;
    vector<HinhTron> dsVong;
    DocFile(N, S, T, dsVong);
    TimDuongDi(N, S, T, dsVong);
    return 0;
}
