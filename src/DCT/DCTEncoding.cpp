#include "DCTEncoding.h"

DCTEncoding::DCTEncoding(RunLengthEnoding runLengthEnoding, ZigzagDCTcoefficientsOrder zigzagDCTcoefficientsOrder)
    : m_runlengthEnoding(runLengthEnoding), m_zigzagDCTcoefficientsOrder(zigzagDCTcoefficientsOrder)
{
}
