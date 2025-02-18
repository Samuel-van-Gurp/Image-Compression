#include "Image.h"
#include "Compressor.h"
#include "SparseRepresentation.h"
#include "StoringData.h"
#include "DCT/DCT.h"
#include "DCT/ImageChopper.h"
#include "DCT/DCTCompression.h"
#include <opencv2/opencv.hpp>
#include <iostream>

int main()
{

    // Image img = Image("C:/Users/svangurp/Desktop/projects/ImageCompression/images/GrayscaleTestImg/camera.tif");

    // Compressor compressor = Compressor();

    // // img.displayImage();

    // SparseRepresentation sparseRepr = compressor.compress(img, 50);

    // StoringData storingData = StoringData();

    // // std::cout<< "sparseRepr.getSize().first" << sparseRepr.getSize().first<<std::endl;
    // storingData.SaveFile("camera.samuel", "C:/Users/svangurp/Desktop/projects/ImageCompression/images/imgOUT/", sparseRepr);

    // auto sparseReprloaded = storingData.LoadFile("camera.samuel", "C:/Users/svangurp/Desktop/projects/ImageCompression/images/imgOUT/");

    // // std::cout<< "sparseReprloaded.getSize().first" << sparseReprloaded.getSize().first<<std::endl;

    // Image decompressedImage = compressor.decompress(sparseReprloaded);

    // decompressedImage.displayImage();

    ////////////////////////
    //  DCT compression   //
    ////////////////////////

    Image img = Image("C:/Users/svangurp/Desktop/projects/ImageCompression/images/GrayscaleTestImg/camera.tif");
    img.displayImage();
    DCTCompression dctCompression;

    auto img_vec = img.getImageAsVector();

    auto compressedImage = dctCompression.DCTCompress(img_vec, CompressionLevel::ULTRA_HIGH);

    auto decompressedImage = dctCompression.DCTDecompress(compressedImage, CompressionLevel::ULTRA_HIGH, static_cast<int>(img_vec.size()), static_cast<int>(img_vec[0].size()));

    Image decompressedImg = Image(decompressedImage);

    decompressedImg.displayImage("Decompressed Image");

    decompressedImg.DisplayDiffImage(img);

    return 0;
}
