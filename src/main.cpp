#include "Image.h"
#include "Compressor.h"
#include "SparseRepresentation.h"
#include "StoringData.h"
#include <opencv2/opencv.hpp>
#include <iostream>

int main()
{

    Image img = Image("C:/Users/svangurp/Desktop/projects/ImageCompression/images/GrayscaleTestImg/camera.tif");

    Compressor compressor = Compressor();

    // img.displayImage();

    SparseRepresentation sparseRepr = compressor.compress(img, 10);

    StoringData storingData = StoringData();

    // std::cout<< "sparseRepr.getSize().first" << sparseRepr.getSize().first<<std::endl;
    storingData.SaveFile("camera.samuel", "C:/Users/svangurp/Desktop/projects/ImageCompression/images/imgOUT/", sparseRepr);

    auto sparseReprloaded = storingData.LoadFile("camera.samuel", "C:/Users/svangurp/Desktop/projects/ImageCompression/images/imgOUT/");

    // std::cout<< "sparseReprloaded.getSize().first" << sparseReprloaded.getSize().first<<std::endl;

    Image decompressedImage = compressor.decompress(sparseReprloaded);

    decompressedImage.displayImage();

    return 0;
}
