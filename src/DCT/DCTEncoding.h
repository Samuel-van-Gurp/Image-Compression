#include "zigzagDCTcoefficientsOrder.h"
#include "runLengthEnoding.h"
#include <vector>

class DCTEncoding
{
public:
    // constructor dependency injection
    DCTEncoding(RunLengthEnoding runLengthEnoding, ZigzagDCTcoefficientsOrder zigzagDCTcoefficientsOrder);

    std::vector<std::vector<std::pair<int, int>>> encodeImageBlocks(std::vector<std::vector<std::vector<int>>>& imageChuncks) const;

    std::vector<std::vector<std::vector<int>>> decodeImageBlocks(std::vector<std::vector<std::pair<int, int>>> &encodeImageBlocks) const;

private:
    RunLengthEnoding m_runlengthEnoding;

    ZigzagDCTcoefficientsOrder m_zigzagDCTcoefficientsOrder;
};
