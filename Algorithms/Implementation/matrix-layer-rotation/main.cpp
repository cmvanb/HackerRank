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

    int get_shell_number_from_row_column(int r, int c)
    {
        // min(c, columns - 1 - c) = shortest horizontal distance to edge of matrix
        // min(r, rows - 1 - c) = shortest vertical distance to edge of matrix
        // Whichever of the above two distances is shortest, that's the shell number. Hence:
        return min(min(c, columns - 1 - c), min(r, rows - 1 - r));
    }

    int get_index_from_row_column(int r, int c)
    {
        return (r * columns) + c;
    }

    int get_rotated_element(int r, int c)
    {
        int shell = get_shell_number_from_row_column(r, c);
        int shellRight = columns - 1 - shell;
        int shellBottom = rows - 1 - shell;

        // [r, c] is in the left-most column of the shell (excluding top-left)
        // which means it's rotated value comes from the element above it [r - 1, c]
        if (c == shell && r > shell && r <= shellBottom)
        {
            r -= 1;
        }
        // [r, c] is in the top-most row of the shell (excluding top-right)
        // which means it's rotated value comes from the element to the right [r, c + 1]
        else if (r == shell && c >= shell && c < shellRight)
        {
            c += 1;
        }
        // [r, c] is in the right-most column of the shell (excluding bottom-right)
        // which means it's rotated value comes from the element below it [r + 1, c]
        else if (c == shellRight && r >= shell && r < shellBottom)
        {
            r += 1;
        }
        // [r, c] is in the bottom-most row of the shell (excluding bottom-left)
        // which means it's rotated value comes from the element to the left [r, c - 1]
        else if (r == shellBottom && c > shell && c <= shellRight)
        {
            c -= 1;
        }

        int index = get_index_from_row_column(r, c);
        return elements[index];
    }

    void rotate_once_ccw()
    {
        vector<int> rotatedElements;

        for (int r = 0; r < rows; ++r)
        {
            for (int c = 0; c < columns; ++c)
            {
                int rotatedElement = get_rotated_element(r, c);
                rotatedElements.push_back(rotatedElement);
            }
        }

        elements = rotatedElements;
    }

    void rotate_ccw(int rotations)
    {
        for (int i = 0; i < rotations; ++i)
        {
            rotate_once_ccw();
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

    // NOTE: Un-used functions left here for potential future usefulness.
    /*
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

    int get_shell_count()
    {
        return divide_rounding_up(max(rows, columns), 2);
    }

    Matrix get_shell_matrix()
    {
        vector<int> shellNumbers;

        for (int i = 0; i < elements.size(); ++i)
        {
            int r = get_row_from_index(i);
            int c = get_column_from_index(i);
            int shellNumber = get_shell_number_from_row_column(r, c);
            shellNumbers.push_back(shellNumber);
        }

        return {
            rows,
            columns,
            shellNumbers
        };
    }
    
    int get_row_from_index(int i)
    {
        return i / columns;
    }

    int get_column_from_index(int i)
    {
        return i % columns;
    }
    */
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

    // rotate matrix N times
    matrix.rotate_ccw(rotations);

    // print result
    cout << matrix.to_hackerrank_string() << endl;
}

int main()
{
    matrix_layer_rotation();
    return 0;
}
