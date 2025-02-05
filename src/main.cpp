#include "Image.h"
#include "Compressor.h"
#include <opencv2/opencv.hpp>
#include <iostream>

int main() {
    
    Image img = Image("C:/Users/svangurp/Desktop/projects/ImageCompression/images/GrayscaleTestImg/lena1.tif");

    Compressor compressor = Compressor();
    
    img.displayImage();

    Image compressedImage = compressor.compress(img, 1);

    compressedImage.displayImage();

    return 0;
}
