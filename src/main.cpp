#include "Image.h"
#include "Compressor.h"
#include "SparseRepresentation.h"
#include <opencv2/opencv.hpp>
#include <iostream>

int main() {
    
    Image img = Image("C:/Users/svangurp/Desktop/projects/ImageCompression/images/GrayscaleTestImg/lena1.tif");

    Compressor compressor = Compressor();
    
    img.displayImage();

    SparseRepresentations sparseRepr = compressor.compress(img, 1);

    Image decompressedImage = compressor.decompress(sparseRepr);

    decompressedImage.displayImage();

    return 0;
}
