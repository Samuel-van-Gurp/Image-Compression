#include "DCTEncoder.h"

DCTEncoder::DCTEncoder(int CHUNCK_SIZE)
    : m_CHUNCK_SIZE(CHUNCK_SIZE)
{
}

std::vector<int> jpegZigzagOrder(const std::vector<std::vector<int>> &imageBlock)
{
    int n = static_cast<int>(imageBlock.size());
    std::vector<int> result;
    // There are 2*n - 1 "diagonals" in an n x n block.
    for (int sum = 0; sum < 2 * n - 1; ++sum)
    {
        // Determine the bounds for the row index.
        int rowStart = std::max(0, sum - (n - 1));
        int rowEnd = std::min(sum, n - 1);

        if (sum % 2 == 0)
        {
            // For even sums, traverse from rowEnd down to rowStart.
            for (int i = rowEnd; i >= rowStart; --i)
            {
                int j = sum - i;
                result.push_back(imageBlock[i][j]);
            }
        }
        else
        {
            // For odd sums, traverse from rowStart up to rowEnd.
            for (int i = rowStart; i <= rowEnd; ++i)
            {
                int j = sum - i;
                result.push_back(imageBlock[i][j]);
            }
        }
    }
    return result;
}