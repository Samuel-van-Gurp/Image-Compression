#include <vector>

class DCTEncoder
{
public:
    DCTEncoder(int CHUNCK_SIZE = 8);
    std::vector<std::vector<int>> encode(std::vector<std::vector<std::vector<int>>> &imageChuncks) const;

private:
    const int m_CHUNCK_SIZE;
    std::vector<int> mZigZagOrder;

    std::vector<int> jpegZigzagtraversal(const std::vector<std::vector<int>> &imageBlock);
};
