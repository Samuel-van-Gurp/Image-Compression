#ifndef RUN_LENGTH_ENCODING_H
#define RUN_LENGTH_ENCODING_H

#include <vector>

class RunLengthEnoding
{
public:
    template <typename T>
    std::vector<std::vector<std::pair<T, int>>> RunLengthEncodeImageBlocks(const std::vector<std::vector<T>> &vector) const
    {
        std::vector<std::vector<std::pair<T, int>>> encodedBlocks;
        for (const auto &block : vector)
        {
            auto encodedBlock = RunLengthEncode(block);
            encodedBlocks.push_back(encodedBlock);
        }
        return encodedBlocks;
    }

    template <typename T>
    std::vector<std::vector<T>> RunLengthDecodeImageBlocks(const std::vector<std::vector<std::pair<T, int>>> &encodedVector) const
    {
        std::vector<std::vector<T>> decodedBlocks;
        for (const auto &block : encodedVector)
        {
            auto decodedBlock = RunLengthDecode(block);
            decodedBlocks.push_back(decodedBlock);
        }
        return decodedBlocks;
    }

    template <typename T>
    std::vector<std::pair<T, int>> RunLengthEncode(const std::vector<T> &vector) const
    {
        std::vector<std::pair<T, int>> encoded;
        if (vector.empty())
            return encoded;

        T currentValue = vector[0];
        int count = 1;

        for (size_t i = 1; i < vector.size(); i++)
        {
            if (vector[i] == currentValue)
            {
                count++;
            }
            else
            {
                encoded.push_back({currentValue, count});
                currentValue = vector[i];
                count = 1;
            }
        }
        encoded.push_back({currentValue, count});
        return encoded;
    }

    template <typename T>
    std::vector<T> RunLengthDecode(const std::vector<std::pair<T, int>> &encodedVector) const
    {
        std::vector<T> decodedVector;
        for (const auto &element : encodedVector)
        {
            for (int i = 0; i < element.second; i++)
            {
                decodedVector.push_back(element.first);
            }
        }
        return decodedVector;
    }
};

#endif // RUN_LENGTH_ENCODING_H
