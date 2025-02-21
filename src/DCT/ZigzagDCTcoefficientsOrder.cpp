#include "ZigzagDCTcoefficientsOrder.h"

std::vector<std::vector<int>> ZigzagDCTcoefficientsOrder::ZigZagOrderImageBlocks(std::vector<std::vector<std::vector<int>>> &imageChuncks) const
{
    std::vector<std::vector<int>> results;

    for (const auto &ImageBlock : imageChuncks)
    {
        auto mZigZagOrder = ZigzagOrder(ImageBlock);

        results.push_back(mZigZagOrder);
    }

    return results;
}

std::vector<int> ZigzagDCTcoefficientsOrder::ZigzagOrder(const std::vector<std::vector<int>> &imageBlock) const
{
    int n = static_cast<int>(imageBlock.size());
    std::vector<int> result;

    for (int sum = 0; sum < 2 * n - 1; ++sum)
    {
        auto diagonal = extractZigzagDiagonal(imageBlock, sum);
        result.insert(result.end(), diagonal.begin(), diagonal.end());
    }
    return result;
}

std::vector<int> ZigzagDCTcoefficientsOrder::extractZigzagDiagonal(const std::vector<std::vector<int>> &imageBlock, int sum) const
{
    int n = static_cast<int>(imageBlock.size());
    std::vector<int> diagonal;
    int rowStart = std::max(0, sum - (n - 1));
    int rowEnd = std::min(sum, n - 1);

    if (sum % 2 == 0)
    {
        for (int i = rowEnd; i >= rowStart; --i)
        {
            int j = sum - i;
            diagonal.push_back(imageBlock[i][j]);
        }
    }
    else
    {
        for (int i = rowStart; i <= rowEnd; ++i)
        {
            int j = sum - i;
            diagonal.push_back(imageBlock[i][j]);
        }
    }
    return diagonal;
}

std::vector<std::vector<std::vector<int>>> ZigzagDCTcoefficientsOrder::deZigZagOrderImageBlocks(std::vector<std::vector<int>> &encodedImageBlocks) const
{
    std::vector<std::vector<std::vector<int>>> decodedImageBlocks;
    for (const auto &zigzagOrder : encodedImageBlocks)
    {
        auto imageBlock = ReverseZigzagtraversal(zigzagOrder);
        decodedImageBlocks.push_back(imageBlock);
    }
    return decodedImageBlocks;
}

std::vector<std::vector<int>> ZigzagDCTcoefficientsOrder::ReverseZigzagtraversal(const std::vector<int> &zigzagOrder) const
{
    int dctBlockSize = static_cast<int>(std::sqrt(zigzagOrder.size()));
    std::vector<std::vector<int>> imageBlock(dctBlockSize, std::vector<int>(dctBlockSize, 0));
    int index = 0;

    for (int sum = 0; sum < 2 * dctBlockSize - 1; ++sum)
    {
        fillZigzagDiagonal(imageBlock, zigzagOrder, sum, dctBlockSize, index);
    }

    return imageBlock;
}

void ZigzagDCTcoefficientsOrder::fillZigzagDiagonal(std::vector<std::vector<int>> &imageBlock,
                                                    const std::vector<int> &zigzagOrder,
                                                    int sum,
                                                    int dctBlockSize,
                                                    int &index) const
{
    int rowStart = std::max(0, sum - (dctBlockSize - 1));
    int rowEnd = std::min(sum, dctBlockSize - 1);

    if (sum % 2 == 0)
    {
        for (int i = rowEnd; i >= rowStart; --i)
        {
            int j = sum - i;
            imageBlock[i][j] = zigzagOrder[index++];
        }
    }
    else
    {
        for (int i = rowStart; i <= rowEnd; ++i)
        {
            int j = sum - i;
            imageBlock[i][j] = zigzagOrder[index++];
        }
    }
}
