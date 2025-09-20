#include <iostream>
#include <fstream>
using namespace std;

#define FI "BACVAOBACRA.INP"
#define FO "BACVAOBACRA.OUT"
#define MAX 1000

ifstream fi;
ofstream fo;

int n;
int A[MAX][MAX];
int bacvao[MAX];
int bacra[MAX];

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
    if (n <= 0) return; // nếu chưa đọc được thì thôi
    for (int i = 0; i < n; i++) {
        bacvao[i] = 0;
        bacra[i] = 0;
    }
    // Tính bậc ra (tổng hàng) và bậc vào (tổng cột)
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < n; j++) {
            if (A[i][j] == 1) {
                bacra[i]++;    // cạnh đi ra từ i tới j
            }
            if (A[j][i] == 1) {
                bacvao[i]++;   // cạnh đi vào i từ j
            }

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
        fo << bacvao[i] << " " << bacra[i] << endl;
    }
    fo.close();
}

int main() {
    Nhap();
    XuLy();
    Xuat();
    return 0;
}
