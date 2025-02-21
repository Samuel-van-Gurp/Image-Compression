#include "gtest/gtest.h"
#include "DCT/ZigzagDCTcoefficientsOrder.h"

TEST(ZigzagDCTcoefficientsOrder, test_encoding)
{
    std::vector<std::vector<std::vector<int>>> imageBlock = {{{1, 2, 6, 7},
                                                              {3, 5, 8, 13},
                                                              {4, 9, 12, 14},
                                                              {10, 11, 15, 16}}};
    ZigzagDCTcoefficientsOrder encoder;
    auto zigzagOrder = encoder.ZigZagOrderImageBlocks(imageBlock);
    std::vector<std::vector<int>> expected = {{1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12, 13, 14, 15, 16}};
    ASSERT_EQ(zigzagOrder, expected);
}

TEST(ZigzagDCTcoefficientsOrder, test_decoding)
{
    ZigzagDCTcoefficientsOrder encoder;
    std::vector<std::vector<int>> diagonalised = {{1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12, 13, 14, 15, 16}};
    auto Imageblocks = encoder.deZigZagOrderImageBlocks(diagonalised);

    std::vector<std::vector<std::vector<int>>> expectedImageBlock = {{{1, 2, 6, 7},
                                                                      {3, 5, 8, 13},
                                                                      {4, 9, 12, 14},
                                                                      {10, 11, 15, 16}}};

    ASSERT_EQ(Imageblocks, expectedImageBlock);
}