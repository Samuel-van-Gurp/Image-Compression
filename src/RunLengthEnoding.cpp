#include "RunLengthEnoding.h"

std::vector<std::pair<int, int>> RunLengthEnoding::RunLengthEncode(const std::vector<int> &vector) const
{
    if (vector.empty())
    {
        return {};
    }
    std::vector<std::pair<int, int>> encodedVector;

    int count = 1;
    for (std::size_t i = 1; i < vector.size(); ++i)
    {
        if (vector[i] == vector[i - 1])
        {
            // same as prev do increment count
            ++count;
        }
        else
        {

            encodedVector.push_back(std::make_pair(vector[i - 1], count));
            count = 1; // Reset count
        }
    }
    // Don't forget the last element and its count!
    encodedVector.push_back(std::make_pair(vector.back(), count));
    return encodedVector;
}

std::vector<std::vector<std::pair<int,int>>> RunLengthEnoding::RunLengthEncodeImageBlocks(const std::vector<std::vector<int>>& vector) const
{
    std::vector<std::vector<std::pair<int,int>>> encodedVector;
    for (const std::vector<int>& imageBlock : vector)
    {
        encodedVector.push_back(RunLengthEncode(imageBlock));
    }
    return encodedVector;
}

std::vector<std::vector<int>> RunLengthEnoding::RunLengthDecodeImageBlocks(const std::vector<std::vector<std::pair<int,int>>>& encodedVector) const
{
    std::vector<std::vector<int>> decodedVector;
    for (const std::vector<std::pair<int,int>>& imageBlock : encodedVector)
    {
        decodedVector.push_back(RunLengthDecode(imageBlock));
    }
    return decodedVector;
}

std::vector<int> RunLengthEnoding::RunLengthDecode(const std::vector<std::pair<int, int>> &encodedVector) const
{
    std::vector<int> decodedVector;
    for (const std::pair<int, int> element : encodedVector)
    {
        for (int i = 0; i < element.second; i++)
        {
            decodedVector.push_back(element.first);
        }
    }

    return decodedVector;
}
