#include <iostream>
#include <vector>
#include <algorithm>
#include <fstream>
#include <limits>

using namespace std;

// Hằng số và biến toàn cục
const long long INF = 1000000000000000000LL;
int n, m, s, t, x; // s: nguồn, t: đích, x: trung gian
vector<vector<pair<int, long long>>> adjList; // Danh sách kề: {đỉnh_kề, trọng_số}
vector<long long> dist;
vector<int> pre;
vector<bool> label;

//Đọc dữ liệu từ file NNTRUNGGIAN.INP
void ReadFile() {
    ifstream fin("NNTRUNGGIAN.INP");

    if (!fin.is_open()) {
        cerr << "Khong the mo file!" << endl;
        exit(1);
    }

    // Đọc n, m, s, t, x
    fin >> n >> m >> s >> t >> x;

    adjList.resize(n + 1);

    // Đọc m cạnh (u, v, w)
    for (int i = 0; i < m; ++i) {
        int u, v;
        long long w;
        fin >> u >> v >> w;
        adjList[u].push_back({ v, w });
    }

    fin.close();
}

//Thuật toán Dijkstra: Tìm đường đi ngắn nhất từ đỉnh 'start'.
void Dijkstra(int start)
{
    // B1: Khởi tạo
    dist.assign(n + 1, INF);
    pre.assign(n + 1, -1);
    label.assign(n + 1, false);
    dist[start] = 0;

    // B2: Lặp (Cố định n đỉnh)
    for (int k = 0; k < n; k++)
    {
        // 1. Chọn u: Tìm đỉnh u chưa xét và có dist[u] nhỏ nhất
        int u = -1;
        long long min_dist = INF;

        for (int v = 1; v <= n; v++)
        {
            if (!label[v] && dist[v] < min_dist)
            {
                min_dist = dist[v];
                u = v;
            }
        }

        if (u == -1) break; // Không còn đỉnh nào có thể đến được

        // 2. Cố định u
        label[u] = true;

        // 3. Cập nhật (Relaxation) cho các đỉnh kề v
        for (const auto& edge : adjList[u])
        {
            int v = edge.first;
            long long w = edge.second;

            // Kiểm tra dist[u] != INF để tránh tràn số khi cộng
            if (!label[v] && dist[u] != INF && dist[u] + w < dist[v])
            {
                dist[v] = dist[u] + w;
                pre[v] = u;
            }
        }
    }
}

//Hàm truy vết đường đi từ 'start' đến 'end' (sử dụng mảng pre hiện tại)
vector<int> TimDuong(int start, int end)
{
    vector<int> path;
    if (dist[end] == INF) return path;

    for (int u = end; u != -1; u = pre[u])
    {
        path.push_back(u);
        if (u == start) break;
    }

    reverse(path.begin(), path.end());
    return path;
}

//Hàm chính giải quyết bài toán và xuất kết quả
void XulyVaXuat() {
    // 1. Chặng 1: S -> X
    Dijkstra(s);
    long long dist1 = dist[x];
    vector<int> path1 = TimDuong(s, x);

    // 2. Chặng 2: X -> T
    Dijkstra(x);
    long long dist2 = dist[t];
    vector<int> path2 = TimDuong(x, t);

    // Kiểm tra xem có đường đi không
    if (dist1 == INF || dist2 == INF) {
        cout << 0 << " " << 0 << endl;
        return;
    }

    // 3. Ghép kết quả
    long long total_dist = dist1 + dist2;
    vector<int> final_path = path1;

    // Nối path2 vào final_path, bỏ qua đỉnh x (vì x đã có trong path1)
    if (path2.size() > 1) {
        for (size_t i = 1; i < path2.size(); ++i) { // Bắt đầu từ index 1 (bỏ qua x)
            final_path.push_back(path2[i]);
        }
    }

    // Xuất kết quả
    // Dòng 1: Số đỉnh đường đi và độ dài đường đi
    cout << final_path.size() << " " << total_dist << endl;

    // Dòng 2: Danh sách các đỉnh
    for (size_t i = 0; i < final_path.size(); ++i) {
        cout << final_path[i] << (i == final_path.size() - 1 ? "" : " ");
    }
    cout << endl;
}

int main()
{
    ReadFile();
    XulyVaXuat();
    return 0;
}