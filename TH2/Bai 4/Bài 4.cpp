#include <iostream>
#include <fstream>
#include <set>
using namespace std;

#define MAX 100000

ifstream fi;
ofstream fo;

int n, m;
int bac[MAX + 5];
set<pair<int, int>> tapcanh; // dùng set để bỏ cạnh trùng

void Nhap() {
    fi.open("DANHSACHCANH.INP");
    if (!fi) {
        cout << "Khong mo duoc file!\n";
        return;
    }

    fi >> n >> m;

    for (int i = 1; i <= n; i++) {
        bac[i] = 0;
    }

    for (int i = 1; i <= m; i++) {
        int u, v;
        fi >> u >> v;
        if (u > v) swap(u, v); // chuẩn hoá: cạnh (u,v) với u < v
        tapcanh.insert({ u, v });
    }

    fi.close();

    // tính bậc sau khi loại cạnh trùng
    for (auto canh : tapcanh) {
        int u = canh.first;
        int v = canh.second;
        bac[u]++;
        bac[v]++;
    }
}

void Xuat() {
    fo.open("DANHSACHCANH.OUT");
    if (!fo) {
        cout << "Khong tao duoc file!\n";
        return;
    }

    fo << n << endl;
    for (int i = 1; i <= n; i++) {
        fo << bac[i] << endl;
    }

    fo.close();
}

int main() {
    Nhap();
    Xuat();
    return 0;
}
