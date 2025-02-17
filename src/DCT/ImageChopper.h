#include <opencv2/opencv.hpp>

class ImageChopper
{
public:
    std::vector<std::vector<std::vector<float>>> chopImage(const std::vector<std::vector<float>> &Image, const int chopSize) const;

private:
    std::vector<std::vector<std::vector<float>>> getImageBlocks(const std::vector<std::vector<float>> &paddedImage, const int chopSize, const int numberOfChops) const;
    void extractImageBlock(const std::vector<std::vector<float>> &paddedImage, int row, int col, int chopSize, std::vector<std::vector<std::vector<float>>> &chops) const;
    std::vector<std::vector<float>> padImage(const std::vector<std::vector<float>> &Image, const int chopSize) const;
};
