#include <cmath>
#include <cstdio>
#include <vector>
#include <iostream>
#include <algorithm>
#include <string>
using namespace std;

bool kangaroo(int x1, int v1, int x2, int v2)
{
    if (x1 - x2 != 0 && v1 - v2 == 0)
    {
        return false;
    }

    if ((x1 - x2) / (v1 - v2) >= 0)
    {
        return false;
    }

    return (x1 - x2) % (v2 - v1) == 0 ? true : false; 
}

int main()
{
    int x1, v1, x2, v2;

    cin >> x1;
    cin >> v1;
    cin >> x2;
    cin >> v2;

    bool collided = kangaroo(x1, v1, x2, v2);

    if (collided)
    {
        cout << "YES" << endl;
    }
    else
    {
        cout << "NO" << endl;
    }

    return 0;
}