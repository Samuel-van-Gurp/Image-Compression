#include <opencv2/opencv.hpp>

#ifndef IMAGECHOPPER_H
#define IMAGECHOPPER_H

#include <vector>

class ImageChopper
{
public:
    std::vector<std::vector<std::vector<float>>> chopImage(const std::vector<std::vector<float>> &image, int chopSize) const;
    std::vector<std::vector<float>> reconstructImage(const std::vector<std::vector<std::vector<float>>> &choppedImage, int originalHeight, int originalWidth) const;

private:
    bool areSidesMultipleOfBlockSize(int height, int width, int chopSize) const;
    std::vector<std::vector<float>> padImage(const std::vector<std::vector<float>> &image, int chopSize) const;
    std::vector<std::vector<float>> extractImageBlock(const std::vector<std::vector<float>> &image, int row, int col, int chopSize) const;
    void insertImageBlock(std::vector<std::vector<float>> &image, const std::vector<std::vector<float>> &block, int row, int col) const;
};

#endif // IMAGECHOPPER_H
