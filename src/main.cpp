#include "Image.h"

#include "DFT/DFTCompressor.h"
#include "DFT/SparseRepresentation.h"
#include "DFT/StoringData.h"

#include "DCT/DCT.h"
#include "DCT/ImageChopper.h"
#include "DCT/DCTCompression.h"
#include "DCT/DCTEncoding.h"
#include "DCT/ZigzagDCTcoefficientsOrder.h"
#include "DCT/DCTTransformationHandler.h"
#include "DCT/DCTCompression.h"
#include "DCT/StoreDCTData.h"

#include "RunLengthEnoding.h"

#include <opencv2/opencv.hpp>
#include <iostream>

int main()
{

    // Image img = Image("C:/Users/svangurp/Desktop/projects/ImageCompression/images/GrayscaleTestImg/camera.tif");

    // DFTCompressor compressor = DFTCompressor();

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

    DCTCompression dctCompression;

    StoreDCTData storeDCTData = StoreDCTData();

    Image img = Image("C:/Users/svangurp/Desktop/projects/ImageCompression/images/GrayscaleTestImg/camera.tif");
    img.displayImage();

    auto img_vec = img.getImageAsVector();

    CompressedDCTImageHolder compressedImage = dctCompression.DCTCompress(img_vec, CompressionLevel::VERY_HIGH);

    storeDCTData.writeToBinary("camera.samuelDCT", "C:/Users/svangurp/Desktop/projects/ImageCompression/images/imgOUT/", compressedImage);

    auto compressedImageHolderReadFormFile = storeDCTData.readFromBinary("camera.samuelDCT", "C:/Users/svangurp/Desktop/projects/ImageCompression/images/imgOUT/");

    auto reconstructedImage = dctCompression.DCTDecompress(compressedImageHolderReadFormFile);

    Image decompressedImg = Image(reconstructedImage);

    decompressedImg.scaleIntensity();

    decompressedImg.displayImage("Reconstructed Image");

    return 0;
}
