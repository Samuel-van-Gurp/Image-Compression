#ifndef COMPLEX_ROW_COLUMN_VALUE_H
#define COMPLEX_ROW_COLUMN_VALUE_H

#include "BaseCompressedImageHolder.h"

struct CompressedDFTImageHolder : public BaseCompressedImageHolder
{
    int m_row;
    int m_col;
    float m_real;
    float m_imag;

    CompressedDFTImageHolder() = default;
    CompressedDFTImageHolder(int row, int col, float real, float imag);
};
#endif
