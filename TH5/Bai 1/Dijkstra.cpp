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
int n, m, s, t; // Số đỉnh, số cạnh, đỉnh nguồn, đỉnh đích
// adjList[u] là danh sách các cặp {v, w} với v là đỉnh kề, w là trọng số
vector<vector<pair<int, long long>>> adjList;
vector<long long> dist; // Khoảng cách ngắn nhất từ s
vector<int> pre;      // Đỉnh trước đó trên đường đi ngắn nhất

// Hàm chính của thuật toán Dijkstra
void Dijkstra()
{
    // B1: Khởi tạo
    dist.assign(n + 1, INF);
    pre.assign(n + 1, -1);
    dist[s] = 0;

    // Hàng đợi ưu tiên: {khoảng_cách, đỉnh}
    priority_queue<pair<long long, int>,
        vector<pair<long long, int>>,
        greater<pair<long long, int>>> pq;

    pq.push({ 0, s });

    // B2: Lặp
    while (!pq.empty())
    {
        long long d = pq.top().first;
        int u = pq.top().second;
        pq.pop();

        if (d > dist[u]) continue;

        // Thư giãn (Relaxation) cho các đỉnh kề v
        for (const auto& edge : adjList[u])
        {
            int v = edge.first;
            long long w = edge.second;

            if (dist[u] != INF && dist[u] + w < dist[v])
            {
                dist[v] = dist[u] + w;
                pre[v] = u;
                pq.push({ dist[v], v });
            }
        }
    }
}

// Hàm truy vết đường đi từ s đến t
vector<int> TimDuong(int s, int t)
{
    vector<int> path;
    if (dist[t] == INF) {
        return path; // Không có đường đi
    }

    // Truy vết ngược từ t về s
    for (int u = t; u != -1; u = pre[u])
    {
        path.push_back(u);
        if (u == s) break;
    }

    reverse(path.begin(), path.end());
    return path;
}

// Hàm đọc dữ liệu từ file DIJKSTRA.INP
void ReadFile() {
    ifstream fin("DIJKSTRA.INP");
    if (!fin.is_open()) {
        cout << "Khong the mo file!" << endl;
        exit(1);
    }

    // Đọc n, m, s, t
    fin >> n >> m >> s >> t;

    adjList.resize(n + 1);

    // Đọc m cạnh
    for (int i = 0; i < m; ++i) {
        int u, v;
        long long w;
        fin >> u >> v >> w;
        adjList[u].push_back({ v, w });
    }

    fin.close();
}

// Hàm xuất kết quả ra màn hình theo định dạng yêu cầu (Số_đỉnh Độ_dài)
void Xuat() {
    vector<int> path = TimDuong(s, t);

    // Dòng 1: Số lượng đỉnh và Độ dài
    if (dist[t] == INF) {
        cout << 0 << " " << 0 << endl;
    }
    else {
        // Output format: Số_đỉnh (path.size()) Độ_dài (dist[t])
        cout << path.size() << " " << dist[t] << endl;
    }

    // Dòng 2: Chuỗi các đỉnh
    if (!path.empty()) {
        for (int i = 0; i < path.size(); ++i) {
            cout << path[i] << (i == path.size() - 1 ? "" : " ");
        }
        cout << endl;
    }
}

int main()
{
    ReadFile();
    Dijkstra();
    Xuat();

    return 0;
}