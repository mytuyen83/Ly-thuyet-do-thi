#include <iostream>
#include <fstream>
#include <vector>
using namespace std;

const int INF = 1e9;
int dx[4] = { -1, 1, 0, 0 };
int dy[4] = { 0, 0, -1, 1 };

struct O {
    int x, y;
};

// Đọc dữ liệu
void DocFile(int& n, int& m, int& xi, int& yi, int& xj, int& yj, vector<vector<int>>& a) {
    ifstream fin("MINTABLE.INP");
    fin >> n >> m >> xi >> yi >> xj >> yj;
    a.assign(n + 1, vector<int>(m + 1));
    for (int i = 1; i <= n; i++)
        for (int j = 1; j <= m; j++)
            fin >> a[i][j];
    fin.close();
}

// Ghi kết quả
void GhiFile(int coDuong, int tongChiPhi, vector<O> duong) {
    ofstream fout("MINTABLE.OUT");
    fout << coDuong << endl;
    if (coDuong == 1) {
        fout << tongChiPhi << endl;
        for (auto o : duong)
            fout << o.x << " " << o.y << endl;
    }
    fout.close();
}

// Tìm đường đi ngắn nhất
void DijkstraBang(int n, int m, int xi, int yi, int xj, int yj, const vector<vector<int>>& a) {
    vector<vector<int>> d(n + 1, vector<int>(m + 1, INF));
    vector<vector<O>> truoc(n + 1, vector<O>(m + 1, { -1, -1 }));
    vector<vector<bool>> daXet(n + 1, vector<bool>(m + 1, false));

    d[xi][yi] = 0;

    while (true) {
        int u = -1, v = -1, minCost = INF;
        // Tìm ô có chi phí nhỏ nhất chưa xét
        for (int i = 1; i <= n; i++)
            for (int j = 1; j <= m; j++)
                if (!daXet[i][j] && d[i][j] < minCost) {
                    minCost = d[i][j];
                    u = i; v = j;
                }

        if (u == -1) break; // không còn ô để xét
        daXet[u][v] = true;

        // Cập nhật 4 hướng kề
        for (int k = 0; k < 4; k++) {
            int nx = u + dx[k];
            int ny = v + dy[k];
            if (nx < 1 || ny < 1 || nx > n || ny > m || a[nx][ny] == 0) continue;

            int newCost = d[u][v] + ((nx == xj && ny == yj) ? 0 : a[nx][ny]);
            if (newCost < d[nx][ny]) {
                d[nx][ny] = newCost;
                truoc[nx][ny] = { u, v };
            }
        }
    }

    // Không có đường đi
    if (d[xj][yj] == INF) {
        GhiFile(0, 0, {});
        return;
    }

    // Truy vết đường đi
    vector<O> path;
    int cx = xj, cy = yj;
    while (cx != -1 && cy != -1) {
        path.push_back({ cx, cy });
        O t = truoc[cx][cy];
        cx = t.x;
        cy = t.y;
    }
    reverse(path.begin(), path.end());

    GhiFile(1, d[xj][yj], path);
}

int main() {
    int n, m, xi, yi, xj, yj;
    vector<vector<int>> a;
    DocFile(n, m, xi, yi, xj, yj, a);
    DijkstraBang(n, m, xi, yi, xj, yj, a);
    return 0;
}
