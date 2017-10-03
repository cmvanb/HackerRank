// https://www.hackerrank.com/challenges/mini-max-sum
#include <cmath>
#include <cstdio>
#include <vector>
#include <iostream>
#include <algorithm>
#include <string>
using namespace std;

void mini_max_sum()
{
    vector<long long> integers;

    string s;
    while (cin >> s)
    {
        integers.push_back(
            atoll(s.c_str()));

        if (integers.size() >= 5)
        {
            break;
        }
    }

    long long smallest = integers[0];
    long long biggest = integers[0];
    long long sum = 0;

    for (auto&& integer : integers)
    {
        smallest = min<long long>(integer, smallest);
        biggest = max<long long>(integer, biggest);
        sum = sum + integer;
    }

    long long smallestSum = sum - biggest;
    long long biggestSum = sum - smallest;

    cout << smallestSum << " " << biggestSum << endl;
}

int main()
{
    mini_max_sum();
    return 0;
}
