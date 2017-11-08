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

    int get_row_from_index(int i)
    {
        return i / columns;
    }

    int get_column_from_index(int i)
    {
        return i % columns;
    }

    int get_index_from_row_column(int r, int c)
    {
        return (r * columns) + c;
    }

    //int get_shell_number_from_row_column(int r, int c)
    //{
    //    // min(c, columns - 1 - c) = shortest horizontal distance to edge of matrix
    //    // min(r, rows - 1 - c) = shortest vertical distance to edge of matrix
    //    // whichever of the above two distances is shortest, that's the shell number. hence:
    //    return min(min(c, columns - 1 - c), min(r, rows - 1 - r));
    //}

    int get_shell_unrolled_length(int shellNumber)
    {
        int shellColumns = columns - (shellNumber * 2);
        int shellRows = rows - (shellNumber * 2);
        int shellSize = (shellColumns * 2) + (shellRows * 2) - 4;
        return shellSize > 0 ? shellSize : 0;
    }

    int get_shell_count()
    {
        return divide_rounding_up(max(rows, columns), 2);
    }

    // TODO: Finish implementing algorithm. Double check math.
    vector<int> get_row_column_from_shell_index(int shellNumber, int shellIndex)
    {
        vector<int> result;
        int shellColumns = columns - (shellNumber * 2);
        int shellRows = rows - (shellNumber * 2);
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
            result.push_back(shellTopRightIndex + (shellIndex - shellTopRightIndex));
            result.push_back(shellColumns - 1);
        }
        // bottom row
        else if (shellIndex >= shellBottomRightIndex && shellIndex <= shellBottomLeftIndex)
        {
            result.push_back(shellRows - 1);
            result.push_back(shellColumns - (shellIndex - shellBottomRightIndex));
        }
        // left column
        else if (shellIndex > shellBottomLeftIndex)
        {
            // TODO: Finish implementing algorithm.
            result.push_back(-1);
            result.push_back(shellNumber);
        }

        return result;
    }

    vector<int> get_shell_next_row_column(int shellNumber, int r, int c)
    {
        vector<int> result;
        //int shellNumber = get_shell_number_from_row_column(r, c);
        int shellRight = columns - 1 - shellNumber;
        int shellBottom = rows - 1 - shellNumber;

        // [r, c] is in the left-most column of the shell (excluding top-left)
        // which means the next value comes from the element above it [r - 1, c]
        if (c == shellNumber && r > shellNumber && r <= shellBottom)
        {
            result.push_back(r - 1);
            result.push_back(c);
        }
        // [r, c] is in the right-most column of the shell (excluding bottom-right)
        // which means the next value comes from the element below it [r + 1, c]
        else if (c == shellRight && r >= shellNumber && r < shellBottom)
        {
            result.push_back(r + 1);
            result.push_back(c);
        }
        // [r, c] is in the top-most row of the shell (excluding top-right)
        // which means the next value comes from the element to the right [r, c + 1]
        else if (r == shellNumber && c >= shellNumber && c < shellRight)
        {
            result.push_back(r);
            result.push_back(c + 1);
        }
        // [r, c] is in the bottom-most row of the shell (excluding bottom-left)
        // which means the next value comes from the element to the left [r, c - 1]
        else if (r == shellBottom && c > shellNumber && c <= shellRight)
        {
            result.push_back(r);
            result.push_back(c - 1);
        }

        return result;
    }

    vector<int> get_shell_elements(int shellNumber)
    {
        vector<int> result;
        int r, c;

        for (int i = 0; i < get_shell_unrolled_length(shellNumber); ++i)
        {
            // Get r, c from shell index i.
            vector<int> rowColumn = get_row_column_from_shell_index(shellNumber, i);

            // Get next r, c in shell.
            vector<int> nextRowColumn = get_shell_next_row_column(shellNumber, rowColumn[0], rowColumn[1]);

            // Add element at next r, c to elements vector.
            int index = get_index_from_row_column(nextRowColumn[0], nextRowColumn[1]);
            int element = elements[index];
            result.push_back(element);
        }

        return result;
    }

    vector<int> rotate_shell_cw(vector<int> shellElements, int rotations)
    {
        vector<int> rotatedShell;

        for (int i = 0; i < shellElements.size(); ++i)
        {
            int rotatedIndex = (rotations + i) % shellElements.size();
            rotatedShell.push_back(shellElements[rotatedIndex]);
        }

        return rotatedShell;
    }

    void set_shell_elements(int shellNumber, vector<int> elements)
    {
        // TODO: implement
    }

    void rotate_cw(int rotations)
    {
        for (int i = 0; i < get_shell_count(); ++i)
        {
            // unroll shell
            vector<int> shellElements = get_shell_elements(i);

            // rotate shell
            shellElements = rotate_shell_cw(shellElements, rotations);

            // re-roll shell
            set_shell_elements(i, shellElements);
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
    matrix.rotate_cw(rotations);

    // print result
    cout << matrix.to_hackerrank_string() << endl;
}

int main()
{
    matrix_layer_rotation();
    return 0;
}
