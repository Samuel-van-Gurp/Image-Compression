#include <vector>

class RunLengthEnoding
{
public:
    std::vector<std::pair<int, int>> RunLengthEncode(const std::vector<int> &vector) const;
    std::vector<int> RunLengthDecode(const std::vector<std::pair<int, int>> &encodedVector) const;

private:
};
