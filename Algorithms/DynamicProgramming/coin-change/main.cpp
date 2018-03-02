#include <cmath>
#include <cstdio>
#include <vector>
#include <iostream>
#include <algorithm>
#include <string>
using namespace std;

long get_ways(int n, int m, vector<int> c)
{
    int division, remainder;
    for (int i = 0; i < m; ++i)
    {
        // can't do anything with divisor greater than dividend
        if (c[i] > n)
        {
            continue;
        }

        if (c[i] == n)
        {
            ++solutionsCount;
        }

        division = n / c[i];
        remainder = n % c[i];
        cout << n << " / " << c[i] << " = " << division << ", remainder = " << remainder << endl;
    }

    return 0;
}

void coin_change()
{
    // gather input
    int n, m;
    cin >> n;
    cin >> m;

    vector<int> c;
    int ci;
    for (int i = 0; i < m; ++i)
    {
        cin >> ci;
        c.push_back(ci);
    }

    // solve problem
    long solutionsCount = get_ways(n, m, c);
    cout << solutionsCount << endl;
}

int main()
{
    coin_change();
    return 0;
}
