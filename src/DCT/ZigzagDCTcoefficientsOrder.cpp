#include "ZigzagDCTcoefficientsOrder.h"

std::vector<std::vector<float>> ZigzagDCTcoefficientsOrder::ZigZagOrderImageBlocks(std::vector<std::vector<std::vector<float>>> &imageChuncks) const
{
    std::vector<std::vector<float>> results;

    for (const auto &ImageBlock : imageChuncks)
    {
        auto mZigZagOrder = ZigzagOrder(ImageBlock);

        results.push_back(mZigZagOrder);
    }

    return results;
}

std::vector<float> ZigzagDCTcoefficientsOrder::ZigzagOrder(const std::vector<std::vector<float>> &imageBlock) const
{
    int n = static_cast<int>(imageBlock.size());
    std::vector<float> result;

    for (int sum = 0; sum < 2 * n - 1; ++sum)
    {
        auto diagonal = extractZigzagDiagonal(imageBlock, sum);
        result.insert(result.end(), diagonal.begin(), diagonal.end());
    }
    return result;
}

std::vector<float> ZigzagDCTcoefficientsOrder::extractZigzagDiagonal(const std::vector<std::vector<float>> &imageBlock, int sum) const
{
    int n = static_cast<int>(imageBlock.size());
    std::vector<float> diagonal;
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

std::vector<std::vector<std::vector<float>>> ZigzagDCTcoefficientsOrder::deZigZagOrderImageBlocks(const std::vector<std::vector<float>> &encodedImageBlocks) const
{
    std::vector<std::vector<std::vector<float>>> decodedImageBlocks;
    for (const auto &zigzagOrder : encodedImageBlocks)
    {
        auto imageBlock = ReverseZigzagtraversal(zigzagOrder);
        decodedImageBlocks.push_back(imageBlock);
    }
    return decodedImageBlocks;
}

std::vector<std::vector<float>> ZigzagDCTcoefficientsOrder::ReverseZigzagtraversal(const std::vector<float> &zigzagOrder) const
{
    int dctBlockSize = static_cast<int>(std::sqrt(zigzagOrder.size()));
    std::vector<std::vector<float>> imageBlock(dctBlockSize, std::vector<float>(dctBlockSize, 0));
    int index = 0;

    for (int sum = 0; sum < 2 * dctBlockSize - 1; ++sum)
    {
        fillZigzagDiagonal(imageBlock, zigzagOrder, sum, dctBlockSize, index);
    }

    return imageBlock;
}

void ZigzagDCTcoefficientsOrder::fillZigzagDiagonal(std::vector<std::vector<float>> &imageBlock,
                                                    const std::vector<float> &zigzagOrder,
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
