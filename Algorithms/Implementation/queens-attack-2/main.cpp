#include <cmath>
#include <cstdio>
#include <vector>
#include <iostream>
#include <algorithm>
#include <string>
#include <tuple>
using namespace std;

void queens_attack_2()
{
    int n_boardSize, k_obstacleCount;
    cin >> n_boardSize;
    cin >> k_obstacleCount;

    int r_q, c_q;
    cin >> r_q; // y
    cin >> c_q; // x

    vector<tuple<int, int>> obstacles;

    for (int i = 0; i < k_obstacleCount; ++i)
    {
        int r_i, c_i;
        cin >> r_i;
        cin >> c_i;

        obstacles.push_back(
            make_tuple(r_i, c_i));
    }

    // for (auto&& o : obstacles)
    // {
    //     cout << get<0>(o) << ", " << get<1>(o) << endl;
    // }

    // TODO: Calculate number of squares queen can attack from her position.

    // TODO: Output result as a single integer.
}

int main()
{
    queens_attack_2();
    return 0;
}
