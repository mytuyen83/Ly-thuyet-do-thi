#include <iostream>
#include <fstream>
#include <vector>
#include <queue>
using namespace std;

int n, x; // số đỉnh và đỉnh bắt đầu
vector<vector<int>> ke; // danh sách kề
vector<char> visited; // đánh dấu đỉnh đã thăm

// Hàm đọc dữ liệu
void readfile() {
    ifstream fi("DOTHI1.INP");
    if (!fi.is_open()) {
        cout << "Khong mo duoc file!\n";
        exit(1);
    }

    fi >> n >> x;
    ke.assign(n + 1, {});

    for (int i = 1; i <= n; i++) {
        int v;
        while (fi >> v) {
            if (v == -1) break;
            ke[i].push_back(v);
        }
    }
    fi.close();
}

// Hàm BFS từ đỉnh x
vector<int> BFS(int s) {
    visited.assign(n + 1, 0);
    vector<int> kq;
    queue<int> q;

    visited[s] = 1;
    q.push(s);

    while (!q.empty()) {
        int u = q.front(); q.pop();
        for (int v : ke[u]) {
            if (!visited[v]) {
                visited[v] = 1;
                kq.push_back(v);
                q.push(v);
            }
        }
    }
    return kq;
}

int main() {
    readfile();
    vector<int> kq = BFS(x);

    cout << kq.size() << "\n";
    for (int v : kq) cout << v << " ";
    cout << "\n";
    return 0;
}
