#ifndef DCT_ENCODING_H
#define DCT_ENCODING_H

#include "ZigzagDCTcoefficientsOrder.h"
#include "RunLengthEnoding.h"
#include <vector>

class DCTEncoding
{
public:
    // constructor dependency injection
    DCTEncoding(RunLengthEnoding runLengthEnoding, ZigzagDCTcoefficientsOrder zigzagDCTcoefficientsOrder);

    template <typename T>
    std::vector<std::vector<std::pair<T, int>>> encodeImageBlocks(std::vector<std::vector<std::vector<T>>> &imageChuncks) const
    {
        auto zigzagOrder = m_zigzagDCTcoefficientsOrder.ZigZagOrderImageBlocks(imageChuncks);
        return m_runlengthEnoding.RunLengthEncodeImageBlocks<T>(zigzagOrder);
    }

    template <typename T>
    std::vector<std::vector<std::vector<T>>> decodeImageBlocks(const std::vector<std::vector<std::pair<T, int>>> &encodeImageBlocks) const
    {
        auto decodedBlocks = m_runlengthEnoding.RunLengthDecodeImageBlocks<T>(encodeImageBlocks);
        return m_zigzagDCTcoefficientsOrder.deZigZagOrderImageBlocks(decodedBlocks);
    }

private:
    RunLengthEnoding m_runlengthEnoding;
    ZigzagDCTcoefficientsOrder m_zigzagDCTcoefficientsOrder;
};

#endif // DCT_ENCODING_H
