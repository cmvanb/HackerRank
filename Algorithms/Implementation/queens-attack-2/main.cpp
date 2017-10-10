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
    // base inputs
    int boardSizeN, obstacleCountK;
    cin >> boardSizeN;
    cin >> obstacleCountK;

    int queenR, queenC;
    cin >> queenR; // y
    cin >> queenC; // x

    // these vars keep track of the number of open spaces between the queen and obstacles in the 8 directions
    // the initial values are the number of spaces to the edge of the board
    int spacesW = queenC - 1;
    int spacesE = boardSizeN - queenC;
    int spacesS = queenR - 1;
    int spacesN = boardSizeN - queenR;
    int spacesSW = spacesW < spacesS ? spacesW : spacesS;
    int spacesNE = spacesE < spacesN ? spacesE : spacesN;
    int spacesNW = spacesW < spacesN ? spacesW : spacesN;
    int spacesSE = spacesE < spacesS ? spacesE : spacesS;

    // figure out the closest obstacles to the queen directly after they are inputted
    for (int i = 0; i < obstacleCountK; ++i)
    {
        // input obstacle position
        int r, c;
        cin >> r;
        cin >> c;
        tuple<int, int> obstacle = make_tuple(r, c);

        // calculate relative and absolute difference between obstacle and queen
        int diffC = c - queenC;
        int diffR = r - queenR;
        int columnsOpenToQueen = abs(diffC) - 1;
        int rowsOpenToQueen = abs(diffR) - 1;

        // same horizontal as queen
        if (r == queenR)
        {
            if (diffC < 0 
                && columnsOpenToQueen < spacesW)
            {
                spacesW = columnsOpenToQueen;
            }
            else if (diffC > 0 
                && columnsOpenToQueen < spacesE)
            {
                spacesE = columnsOpenToQueen;
            }
            continue;
        }
        // same vertical as queen
        else if (c == queenC)
        {
            if (diffR < 0 
                && rowsOpenToQueen < spacesS)
            {
                spacesS = rowsOpenToQueen;
            }
            else if (diffR > 0 
                && rowsOpenToQueen < spacesN)
            {
                spacesN = rowsOpenToQueen;
            }
            continue;
        }
        // perfectly equal means obstacle falls on diagonal SW to NE
        else if (diffC == diffR)
        {
            // it doesn't matter if you compare rows or columns here
            if (diffC < 0 
                && columnsOpenToQueen < spacesSW)
            {
                spacesSW = columnsOpenToQueen;
            }
            else if (diffC > 0 
                && columnsOpenToQueen < spacesNE)
            {
                spacesNE = columnsOpenToQueen;
            }
            continue;
        }
        // equal to inverse means obstacle falls on diagonal SE to NW
        else if (diffC == -diffR)
        {
            // so we use both... for aesthetic symmetry :P
            if (diffR < 0 
                && rowsOpenToQueen < spacesSE)
            {
                spacesSE = rowsOpenToQueen;
            }
            else if (diffR > 0 
                && rowsOpenToQueen < spacesNW)
            {
                spacesNW = rowsOpenToQueen;
            }
            continue;
        }

        // otherwise, obstacle doesn't intersect queen's attack lines
    }

    // add up open spaces in the eight cardinal directions to find total attackable squares
    int attackableSquares = spacesW + spacesNW + spacesN + spacesNE + spacesE + spacesSE + spacesS + spacesSW;

    // debug output
    // cout << "spacesW: " << spacesW << endl;
    // cout << "spacesNW: " << spacesNW << endl;
    // cout << "spacesN: " << spacesN << endl;
    // cout << "spacesNE: " << spacesNE << endl;
    // cout << "spacesE: " << spacesE << endl;
    // cout << "spacesSE: " << spacesSE << endl;
    // cout << "spacesS: " << spacesS << endl;
    // cout << "spacesSW: " << spacesSW << endl;

    // final answer
    cout << attackableSquares << endl;
}

int main()
{
    queens_attack_2();
    return 0;
}
