#include <iostream>
#include <vector>
#include <algorithm>
#include <fstream>
#include <limits>
#include <iomanip>

using namespace std;

// Định nghĩa hằng số
const long long INF = 1000000000000000000LL;

// Biến toàn cục
int n, m; // Số đỉnh, số cung
// Ma trận khoảng cách, sử dụng long long cho trọng số lớn
vector<vector<long long>> D;

//Hàm ReadFile: Đọc dữ liệu từ file FLOYD.INP
void ReadFile() {
    ifstream fin("FLOYD.INP");

    if (!fin.is_open()) {
        cout << "Khong the mo file!" << endl;
        exit(1);
    }

    // Đọc n, m
    fin >> n >> m;

    // Khởi tạo ma trận D
    D.assign(n + 1, vector<long long>(n + 1, INF));

    // Thiết lập khoảng cách từ đỉnh đến chính nó bằng 0
    for (int i = 1; i <= n; ++i) {
        D[i][i] = 0;
    }

    // Đọc m cạnh (u, v, w) và cập nhật ma trận D
    for (int i = 0; i < m; ++i) {
        int u, v;
        long long w;
        fin >> u >> v >> w;

        // Đồ thị vô hướng: Cập nhật cả hai chiều
        D[u][v] = min(D[u][v], w);
        D[v][u] = min(D[v][u], w);
    }

    fin.close();
}

//Thuật toán Floyd-Warshall
void FloydWarshall()
{
    // K: Đỉnh trung gian (1 đến n)
    for (int k = 1; k <= n; k++)
    {
        // I: Đỉnh xuất phát (1 đến n)
        for (int i = 1; i <= n; i++)
        {
            // J: Đỉnh kết thúc (1 đến n)
            for (int j = 1; j <= n; j++)
            {
                // Kiểm tra điều kiện để tránh tràn số (Overflow)
                if (D[i][k] != INF && D[k][j] != INF)
                {
                    // Cập nhật (Relaxation)
                    D[i][j] = min(D[i][j], D[i][k] + D[k][j]);
                }
            }
        }
    }
}

//Hàm xuất kết quả: In ma trận khoảng cách ngắn nhất
void Xuat() {
    FloydWarshall();

    // In ra ma trận n x n
    for (int i = 1; i <= n; i++)
    {
        for (int j = 1; j <= n; j++)
        {
            cout << D[i][j] << (j == n ? "" : " ");
        }
        cout << endl;
    }
}

int main()
{
    ReadFile();
    Xuat();

    return 0;
}