#include <iostream>
#include <fstream>
#include <vector>
using namespace std;

int n;
vector<vector<int>> ke;
vector<int> path;
vector<bool> visited;
bool found = false;

// Đọc dữ liệu từ file
void ReadFile() {
    ifstream fi("DOTHI_HAMILTON.INP");
    if (!fi.is_open()) {
        cout << "Khong mo duoc file!\n";
        exit(1);
    }
    fi >> n;
    ke.assign(n + 1, vector<int>(n + 1, 0));
    for (int i = 1; i <= n; i++) {
        for (int j = 1; j <= n; j++) {
            fi >> ke[i][j];
        }
    }
    fi.close();
}

// Quay lui tìm chu trình Hamilton
void Try(int k) {
    if (found) return; // nếu đã tìm được thì dừng

    if (k == n) {
        // Nếu có cạnh nối về đỉnh đầu tiên thì tạo thành chu trình
        if (ke[path[k - 1]][path[0]] == 1) {
            path.push_back(path[0]); // quay về đầu
            found = true;
        }
        return;
    }

    for (int v = 1; v <= n; v++) {
        if (!visited[v] && ke[path[k - 1]][v] == 1) {
            path[k] = v;
            visited[v] = true;
            Try(k + 1);
            if (found) return;
            visited[v] = false;
        }
    }
}

int main() {
    ReadFile();

    path.assign(n + 1, 0);
    visited.assign(n + 1, false);

    path[0] = 1; // bắt đầu từ đỉnh 1
    visited[1] = true;

    Try(1);

    if (!found) {
        cout << 0 << endl;
    }
    else {
        cout << 1 << endl;
        for (int i = 0; i <= n; i++) { // có thêm đỉnh quay về đầu
            cout << path[i];
            if (i < n) cout << " ";
        }
        cout << endl;
    }

    return 0;
}
