#ifndef COMPLEX_ROW_COLUMN_VALUE_H
#define COMPLEX_ROW_COLUMN_VALUE_H

struct ComplexRowColumnValue
{
    int m_row;
    int m_col;
    float m_real;
    float m_imag;

    ComplexRowColumnValue() = default;
    ComplexRowColumnValue(int row, int col, float real, float imag);
};
#endif
