#include <cmath>
#include <cstdio>
#include <vector>
#include <iostream>
#include <algorithm>
#include <string>
#include <sstream>
#include <cassert>
using namespace std;

int divide_rounding_up(int dividend, int divisor)
{
    return (dividend + divisor - 1) / divisor;
}

int get_order_of_magnitude(int v)
{
    if (v == 0)
    {
        return 0;
    }

    return (int)log10(v);
}

struct Matrix
{
    int rows;
    int columns;
    vector<int> elements;

    int get_index_from_row_column(int r, int c)
    {
        return (r * columns) + c;
    }

    int get_shell_columns(int shellNumber)
    {
        return columns - (shellNumber * 2);
    }

    int get_shell_rows(int shellNumber)
    {
        return rows - (shellNumber * 2);
    }

    int get_shell_unrolled_length(int shellNumber)
    {
        int shellColumns = get_shell_columns(shellNumber);
        int shellRows = get_shell_rows(shellNumber);
        int result = (shellColumns * 2) + (shellRows * 2) - 4;
        return result > 0 ? result : 0;
    }

    int get_shell_count()
    {
        return divide_rounding_up(min(rows, columns), 2);
    }

    vector<int> get_row_column_from_shell_index(int shellNumber, int shellIndex)
    {
        vector<int> result;
        int shellColumns = get_shell_columns(shellNumber);
        int shellRows = get_shell_rows(shellNumber);
        int shellTopRightIndex = shellColumns - 1;
        int shellBottomRightIndex = shellTopRightIndex + shellRows - 1;
        int shellBottomLeftIndex = shellBottomRightIndex + shellColumns - 1;

        // top row
        if (shellIndex >= 0 && shellIndex <= shellTopRightIndex)
        {
            result.push_back(shellNumber);
            result.push_back(shellNumber + shellIndex);
        }
        // right column
        else if (shellIndex > shellTopRightIndex && shellIndex < shellBottomRightIndex)
        {
            result.push_back(shellNumber + shellIndex - shellTopRightIndex);
            result.push_back(shellNumber + shellColumns - 1);
        }
        // bottom row
        else if (shellIndex >= shellBottomRightIndex && shellIndex <= shellBottomLeftIndex)
        {
            result.push_back(shellNumber + shellRows - 1);
            result.push_back(shellNumber + shellColumns - 1 - (shellIndex - shellBottomRightIndex));
        }
        // left column
        else if (shellIndex > shellBottomLeftIndex)
        {
            result.push_back(shellNumber + shellRows - 1 - (shellIndex - shellBottomLeftIndex));
            result.push_back(shellNumber);
        }

        return result;
    }

    vector<int> get_shell_elements(int shellNumber)
    {
        vector<int> result;
        int shellLength = get_shell_unrolled_length(shellNumber);
        vector<int> rowColumn;

        for (int i = 0; i < shellLength; ++i)
        {
            // Get r, c from shell index i.
            rowColumn = get_row_column_from_shell_index(shellNumber, i);

            // Add element at next r, c to elements vector.
            int index = get_index_from_row_column(rowColumn[0], rowColumn[1]);
            int element = elements[index];
            result.push_back(element);
        }

        return result;
    }

    vector<int> rotate_shell_ccw(vector<int> shellElements, int rotations)
    {
        vector<int> rotatedShell;

        for (int i = 0; i < shellElements.size(); ++i)
        {
            int rotatedIndex = (rotations + i) % shellElements.size();
            rotatedShell.push_back(shellElements[rotatedIndex]);
        }

        return rotatedShell;
    }

    void set_shell_elements(int shellNumber, vector<int> shellElements)
    {
        vector<int> rowColumn;

        for (int i = 0; i < shellElements.size(); ++i)
        {
            // Get r, c from shell index i.
            rowColumn = get_row_column_from_shell_index(shellNumber, i);

            // Add shell element at r, c to matrix elements vector.
            int index = get_index_from_row_column(rowColumn[0], rowColumn[1]);

            elements[index] = shellElements[i];
        }
    }

    void rotate_ccw(int rotations)
    {
        int shellCount = get_shell_count();
        for (int i = 0; i < shellCount; ++i)
        {
            // unroll shell
            vector<int> shellElements = get_shell_elements(i);

            // rotate shell
            vector<int> rotatedElements = rotate_shell_ccw(shellElements, rotations);

            // re-roll shell
            set_shell_elements(i, rotatedElements);
        }
    }

    string to_hackerrank_string()
    {
        // loop through matrix and print each element with formatting
        ostringstream stream;
        for (int r = 0; r < rows; ++r)
        {
            for (int c = 0; c < columns; ++c)
            {
                // lookup element
                int index = get_index_from_row_column(r, c);
                int element = elements[index];

                // append element
                stream << element;

                // formatting
                if (c < columns - 1)
                {
                    stream << " ";
                }
                else
                {
                    stream << endl;
                }
            }
        }
        return stream.str();
    }

    string to_formatted_string()
    {
        // calculate column width, based on the order of magnitude of the biggest element
        int maxElement = *max_element(elements.begin(), elements.end());
        int columnWidth = get_order_of_magnitude(maxElement);

        // loop through matrix and print each element with formatting
        ostringstream stream;
        for (int r = 0; r < rows; ++r)
        {
            for (int c = 0; c < columns; ++c)
            {
                // formatting
                if (c == 0)
                {
                    stream << "|";
                }

                // lookup element
                int index = get_index_from_row_column(r, c);
                int element = elements[index];

                // padding spaces
                int oom = get_order_of_magnitude(element);
                int padding = columnWidth - oom;

                for (int p = 0; p < padding; ++p)
                {
                    stream << " ";
                }

                // append element
                stream << element;

                // formatting
                if (c < columns - 1)
                {
                    stream << ", ";
                }
                else
                {
                    stream << "| " << endl;
                }
            }
        }
        return stream.str();
    }
};

void matrix_layer_rotation(int rows, int columns, int rotations, vector<int> elements)
{
    // initialize matrix
    Matrix matrix = {
        rows,
        columns,
        elements
    };

    // print result
    //cout << "--- input matrix ---" << endl;
    cout << matrix.to_hackerrank_string() << endl;

    // rotate matrix N times
    matrix.rotate_ccw(rotations);

    // print result
    //cout << "--- output matrix ---" << endl;
    cout << matrix.to_hackerrank_string() << endl;
}

int main()
{
    // expected input
    int rows, columns, rotations;
    vector<int> elements;

    cin >> rows;
    cin >> columns;
    cin >> rotations;

    // get matrix elements input
    for (int i = 0; i < rows; ++i)
    {
        for (int j = 0; j < columns; ++j)
        {
            int element;
            cin >> element;
            elements.push_back(element);
        }
    }

    matrix_layer_rotation(rows, columns, rotations, elements);
    return 0;
}
