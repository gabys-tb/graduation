#include <iostream>
#include <vector>
#define INF 0x3f3f3f3f
using namespace std;

int min_ligas(int demanda, vector<int>& ligas) {
    int n = ligas.size();
    vector<int> v(demanda + 1, INF);
    v[0] = 0;

    for (int i = 1; i <= demanda; i++) {
        for (int j = 0; j < n; j++) {
            if (ligas[j] <= i) {
                v[i] = min(v[i], 1 + v[i - ligas[j]]);
            }
        }
    }

    return v[demanda];
}

int main() {
    int T;
    cin >> T;

    while (T--) {
        int N, W;
        cin >> N >> W;

        vector<int> ligas(N);
        for (int i = 0; i < N; i++) {
            cin >> ligas[i];
        }

        int minimo_ligas = min_ligas(W, ligas);

        cout << minimo_ligas << endl;
    }

    return 0;
}

