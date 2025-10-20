#include <iostream>
#include <fstream>
using namespace std;

#define FI "MATRANKE.INP"
#define FO "MATRANKE.OUT"
#define MAX 1000

ifstream fi;
ofstream fo;

int n;
int A[MAX][MAX];
int bac[MAX];

void Nhap() {
    fi.open(FI); // mở file 
    if (!fi) {
        cout << "Khong mo duoc file!\n";
        return;
    }
    fi >> n; // đọc số đỉnh
    for (int i = 0; i < n; i++) { // đọc ma trận
        for (int j = 0; j < n; j++) {
            fi >> A[i][j];
        }
    }
    fi.close();
}

void XuLy() {
    for (int i = 0; i < n; i++) { //tính bậc của đỉnh
        bac[i] = 0;
        for (int j = 0; j < n; j++) {
            if (A[i][j] == 1) bac[i]++;
        }
    }
}

void Xuat() {
    fo.open(FO); //xuất kq
    if (!fo) {
        cout << "Khong tao duoc file!\n";
        return;
    }
    fo << n << endl;
    for (int i = 0; i < n; i++) {
        fo << bac[i] << " \n";
    }
    fo.close();
}

int main() {
    Nhap();
    XuLy();
    Xuat();
    return 0;
}
