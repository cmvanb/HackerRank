#include <cmath>
#include <cstdio>
#include <vector>
#include <iostream>
#include <algorithm>
#include <string>
#include <sstream>
using namespace std;

int divide_rounding_up(int dividend, int divisor)
{
    return (dividend + divisor - 1) / divisor;
}

struct Matrix
{
    int rows;
    int columns;
    vector<int> elements;

    string to_string()
    {
        ostringstream stream;
        for (int r = 0; r < rows; ++r)
        {
            for (int c = 0; c < columns; ++c)
            {
                if (c == 0)
                {
                    stream << "|";
                }

                int index = get_index_from_row_column(r, c);
                stream << elements[index];
                
                if (c < columns - 1)
                {
                    stream << ", ";
                }
                else
                {
                    stream << "| \n";
                }
            }
        }
        return stream.str();
    }

    void rotate_once()
    {

    }

    Matrix get_shell_number_matrix()
    {
        vector<int> shellNumbers;

        for (int i = 0; i < elements.size(); ++i)
        {
            int r = get_row_from_index(i);
            int c = get_column_from_index(i);
            int shellNumber = calculate_shell_number_from_row_column(r, c);
            shellNumbers.push_back(shellNumber);
        }

        return {
            rows,
            columns,
            shellNumbers
        };
    }

    int calculate_shell_number_from_row_column(int r, int c)
    {
        int distanceLeft = c;
        int distanceRight = columns - 1 - c;
        int distanceTop = r;
        int distanceBottom = rows - 1 - r;

        return min(min(distanceLeft, distanceRight), min(distanceTop, distanceBottom));
    }
    
    int get_index_from_row_column(int r, int c)
    {
        return (r * columns) + c;
    }

    int get_row_from_index(int i)
    {
        return i / columns;
    }

    int get_column_from_index(int i)
    {
        return i % columns;
    }
};

void matrix_layer_rotation()
{
    // get input
    int rows, columns, rotations;
    cin >> rows;
    cin >> columns;
    cin >> rotations;

    // get matrix elements input
    vector<int> elements;
    for (int i = 0; i < rows; ++i)
    {
        for (int j = 0; j < columns; ++j)
        {
            int element;
            cin >> element;
            elements.push_back(element);
        }
    }

    // initialize matrix
    Matrix matrix = {
        rows,
        columns,
        elements
    };

    cout << "original matrix" << endl;
    cout << matrix.to_string() << endl;

    // TODO: implement rotation
    // matrix.rotate_once();

    // cout << "one rotation" << endl;
    // cout << matrix.to_string() << endl;

    cout << "matrix shell numbers" << endl;
    cout << matrix.get_shell_number_matrix().to_string() << endl;
}

int main()
{
    matrix_layer_rotation();
    return 0;
}
