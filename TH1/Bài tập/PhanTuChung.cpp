#include <iostream>
#include <set>
using namespace std;

int main() {
    int nx, ny, nz;
    set<int> tapX, tapY, tapZ;

    cin >> nx;
    for (int i = 0; i < nx; i++) {
        int so; cin >> so;
        tapX.insert(so);
    }
    cin >> ny;
    for (int i = 0; i < ny; i++) {
        int so; cin >> so;
        tapY.insert(so);
    }
    cin >> nz;
    for (int i = 0; i < nz; i++) {
        int so; cin >> so;
        tapZ.insert(so);
    }

    set<int> giaoXY, giaoXYZ;
    for (int so : tapX) if (tapY.count(so)) giaoXY.insert(so);
    for (int so : giaoXY) if (tapZ.count(so)) giaoXYZ.insert(so);

    cout << giaoXYZ.size() << endl;
    for (int so : giaoXYZ) cout << so << " ";
    cout << endl;

    return 0;
}
