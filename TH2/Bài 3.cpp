#include <iostream>
#include <fstream>
#include <sstream>
using namespace std;

#define MAX 1000

ifstream fi;
ofstream fo;

int n;
int bac[MAX];
string dongDS[MAX]; // lưu tạm danh sách kề

void Nhap() {
    fi.open("DANHSACHKE.INP");
    if (!fi) {
        cout << "Khong mo duoc file!\n";
        return;
    }

    fi >> n;
    fi.ignore(); // bỏ ký tự xuống dòng sau n

    for (int i = 1; i <= n; i++) {
        getline(fi, dongDS[i]);
    }

    fi.close();
}

void XuLy() {
    for (int i = 1; i <= n; i++) {
        bac[i] = 0;
        stringstream ss(dongDS[i]);
        int dinh;
        while (ss >> dinh) {
            bac[i]++;  // đếm số đỉnh kề
        }
    }
}

void Xuat() {
    fo.open("DANHSACHKE.OUT");
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
    XuLy();
    Xuat();
    return 0;
}
