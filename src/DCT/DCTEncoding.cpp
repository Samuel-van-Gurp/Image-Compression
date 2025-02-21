#include "DCTEncoding.h"

DCTEncoding::DCTEncoding(RunLengthEnoding runLengthEnoding, ZigzagDCTcoefficientsOrder zigzagDCTcoefficientsOrder)
    : m_runlengthEnoding(runLengthEnoding), m_zigzagDCTcoefficientsOrder(zigzagDCTcoefficientsOrder)
{
}

std::vector<std::vector<std::pair<int, int>>> DCTEncoding::encodeImageBlocks(std::vector<std::vector<std::vector<int>>>& imageChuncks) const
{
    auto zigzagOrder = m_zigzagDCTcoefficientsOrder.ZigZagOrderImageBlocks(imageChuncks);

    auto runLengthEncoded = m_runlengthEnoding.RunLengthEncodeImageBlocks(zigzagOrder);

    return runLengthEncoded;
}



std::vector<std::vector<std::vector<int>>> DCTEncoding::decodeImageBlocks(std::vector<std::vector<std::pair<int, int>>>& imageChuncks) const
{
    auto zigzagOrder = m_runlengthEnoding.RunLengthDecodeImageBlocks(imageChuncks);

    auto decodedImageBlocks = m_zigzagDCTcoefficientsOrder.deZigZagOrderImageBlocks(zigzagOrder);

    return decodedImageBlocks;
}
