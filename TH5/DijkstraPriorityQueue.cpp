#include <iostream>
#include <vector>
#include <queue>
#include <algorithm>
#include <fstream>
#include <limits>

using namespace std;

// Định nghĩa hằng số
const long long INF = numeric_limits<long long>::max();

// Biến toàn cục
int n, m, s, t, x_unused; // x_unused: Đọc vào nhưng không dùng do yêu cầu bài toán chỉ là s -> t
vector<vector<pair<int, long long>>> adjList; // {đỉnh_kề, trọng_số}
vector<long long> dist;
vector<int> pre;

// Thuật toán Dijkstra với Hàng đợi Ưu tiên
void Dijkstra()
{
    // B1: Khởi tạo
    dist.assign(n + 1, INF);
    pre.assign(n + 1, -1);
    dist[s] = 0;

    // Hàng đợi Ưu tiên: lưu {khoảng_cách, đỉnh}. 
    // Dùng 'greater' để khoảng cách nhỏ nhất ở trên cùng (min-heap)
    priority_queue<pair<long long, int>,
        vector<pair<long long, int>>,
        greater<pair<long long, int>>> pq;

    pq.push({ 0, s }); // Thêm đỉnh nguồn vào hàng đợi

    // B2: Lặp
    while (!pq.empty())
    {
        // Lấy đỉnh u có dist[u] nhỏ nhất (Bước tìm đỉnh u - O(logV))
        long long d = pq.top().first;
        int u = pq.top().second;
        pq.pop();

        // Kiểm tra lỗi thời (Stale entry): Nếu d > dist[u], bỏ qua
        if (d > dist[u]) continue;

        // Cập nhật (Relaxation) cho các đỉnh kề v
        for (const auto& edge : adjList[u])
        {
            int v = edge.first;
            long long w = edge.second;

            if (dist[u] != INF && dist[u] + w < dist[v])
            {
                dist[v] = dist[u] + w;
                pre[v] = u;
                // Đẩy entry mới vào PQ. Việc này tạo ra O(E log V)
                pq.push({ dist[v], v });
            }
        }
    }
}

// Hàm truy vết đường đi từ s đến t
vector<int> TimDuong(int s, int t)
{
    vector<int> path;
    if (dist[t] == INF) return path;

    for (int u = t; u != -1; u = pre[u])
    {
        path.push_back(u);
        if (u == s) break;
    }

    reverse(path.begin(), path.end());
    return path;
}

// Đọc dữ liệu từ file
void ReadFile() {
    ifstream fin("DIJKSTRA.INP");

    if (!fin.is_open()) {
        cout << "Khong the mo file!" << endl;
        exit(1);
    }

    // Đọc n, m, s, t
    fin >> n >> m >> s >> t;

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

// Hàm xuất kết quả
void Xuat() {
    Dijkstra();
    vector<int> path = TimDuong(s, t);

    // Dòng 1: Số đỉnh và Độ dài
    if (dist[t] == INF) {
        cout << 0 << " " << 0 << endl;
    }
    else {
        // Output format: Số_đỉnh (path.size()) Độ_dài (dist[t])
        cout << path.size() << " " << dist[t] << endl;
    }

    // Dòng 2: Chuỗi các đỉnh
    if (!path.empty()) {
        for (size_t i = 0; i < path.size(); ++i) {
            cout << path[i] << (i == path.size() - 1 ? "" : " ");
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