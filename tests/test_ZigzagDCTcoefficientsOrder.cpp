#include "gtest/gtest.h"
#include "DCT/ZigzagDCTcoefficientsOrder.h"

TEST(ZigzagDCTcoefficientsOrder, test_encoding)
{
    std::vector<std::vector<std::vector<float>>> imageBlock = {{{1.0f, 2.0f, 6.0f, 7.0f},
                                                                {3.0f, 5.0f, 8.0f, 13.0f},
                                                                {4.0f, 9.0f, 12.0f, 14.0f},
                                                                {10.0f, 11.0f, 15.0f, 16.0f}}};
    ZigzagDCTcoefficientsOrder encoder;
    auto zigzagOrder = encoder.ZigZagOrderImageBlocks(imageBlock);
    std::vector<std::vector<float>> expected = {{1.0f, 2.0f, 3.0f, 4.0f, 5.0f, 6.0f, 7.0f, 8.0f, 9.0f, 10.0f, 11.0f, 12.0f, 13.0f, 14.0f, 15.0f, 16.0f}};
    ASSERT_EQ(zigzagOrder, expected);
}

TEST(ZigzagDCTcoefficientsOrder, test_decoding)
{
    ZigzagDCTcoefficientsOrder encoder;
    std::vector<std::vector<float>> diagonalised = {{1.0f, 2.0f, 3.0f, 4.0f, 5.0f, 6.0f, 7.0f, 8.0f, 9.0f, 10.0f, 11.0f, 12.0f, 13.0f, 14.0f, 15.0f, 16.0f}};
    auto Imageblocks = encoder.deZigZagOrderImageBlocks(diagonalised);

    std::vector<std::vector<std::vector<float>>> expectedImageBlock = {{{1.0f, 2.0f, 6.0f, 7.0f},
                                                                        {3.0f, 5.0f, 8.0f, 13.0f},
                                                                        {4.0f, 9.0f, 12.0f, 14.0f},
                                                                        {10.0f, 11.0f, 15.0f, 16.0f}}};

    ASSERT_EQ(Imageblocks, expectedImageBlock);
}