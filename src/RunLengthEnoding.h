#ifndef RUN_LENGTH_ENCODING_H
#define RUN_LENGTH_ENCODING_H

#include <vector>

class RunLengthEnoding
{
public:

    std::vector<std::vector<std::pair<int, int>>> RunLengthEncodeImageBlocks(const std::vector<std::vector<int>> &vector) const;
    std::vector<std::vector<int>> RunLengthDecodeImageBlocks(const std::vector<std::vector<std::pair<int, int>>> &encodedVector) const;


    std::vector<std::pair<int, int>> RunLengthEncode(const std::vector<int> &vector) const;
    std::vector<int> RunLengthDecode(const std::vector<std::pair<int, int>> &encodedVector) const;

private:
};

#endif // RUN_LENGTH_ENCODING_H
