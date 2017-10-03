#include <cmath>
#include <cstdio>
#include <vector>
#include <iostream>
#include <algorithm>
#include <string>
using namespace std;

void birthday_cake_candles()
{
    int numCandles;
    cin >> numCandles;

    vector<int> candleHeights;

    string s;
    while (cin >> s)
    {
        candleHeights.push_back(
            atoi(s.c_str()));

        if (candleHeights.size() >= numCandles)
        {
            break;
        }
    }

    int tallestCandleCount = 0;
    int tallestCandleHeight = 0;

    for (auto&& candleHeight : candleHeights)
    {
        if (candleHeight > tallestCandleHeight)
        {
            tallestCandleCount = 0;
            tallestCandleHeight = candleHeight;
        }

        if (candleHeight == tallestCandleHeight)
        {
            ++tallestCandleCount;
        }
    }

    cout << tallestCandleCount << endl;
}

int main()
{
    birthday_cake_candles();
    return 0;
}
