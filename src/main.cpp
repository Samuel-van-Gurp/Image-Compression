#include "Image.h"

#include "DFT/DFTCompressor.h"
#include "DFT/CompressedDFTImageHolder.h"
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

    Image img = Image("C:/Users/svangurp/Desktop/projects/ImageCompression/images/GrayscaleTestImg/camera.tif");

    DFTCompressor compressor = DFTCompressor();

    // img.displayImage();

    std::unique_ptr<BaseCompressedImageHolder> sparseRepr = compressor.compress(img, CompressionLevel::MEDIUM);

    StoringDFTData storingData = StoringDFTData();

    storingData.writeToBinary("camera.samuel", "C:/Users/svangurp/Desktop/projects/ImageCompression/images/imgOUT/", *sparseRepr);

    auto sparseReprloaded = storingData.readFromBinary("camera.samuel", "C:/Users/svangurp/Desktop/projects/ImageCompression/images/imgOUT/");

    // Explicitly cast the BaseCompressedImageHolder reference to a CompressedDCTImageHolder reference
    CompressedDFTImageHolder &derivedHolder = dynamic_cast<CompressedDFTImageHolder&>(*sparseReprloaded);

    Image decompressedImage = compressor.decompress(derivedHolder);

    decompressedImage.displayImage();

    ////////////////////////
    //  DCT compression   //
    ////////////////////////

    // DCTCompression dctCompression;

    // StoreDCTData storeDCTData = StoreDCTData();

    // Image img = Image("C:/Users/svangurp/Desktop/projects/ImageCompression/images/GrayscaleTestImg/camera.tif");
    
    // // img.displayImage();

    // std::unique_ptr<BaseCompressedImageHolder> compressedImage = dctCompression.compress(img, CompressionLevel::ULTRA_HIGH);

    // storeDCTData.writeToBinary("camera.samuelDCT", "C:/Users/svangurp/Desktop/projects/ImageCompression/images/imgOUT/", *compressedImage);

    // auto compressedImageHolderReadFormFile = storeDCTData.readFromBinary("camera.samuelDCT", "C:/Users/svangurp/Desktop/projects/ImageCompression/images/imgOUT/");

    // // Explicitly cast the BaseCompressedImageHolder reference to a CompressedDCTImageHolder reference
    // CompressedDCTImageHolder &derivedHolder = dynamic_cast<CompressedDCTImageHolder&>(*compressedImageHolderReadFormFile);

    // auto reconstructedImage = dctCompression.decompress(derivedHolder);

    // // Image decompressedImg = Image(reconstructedImage);

    // reconstructedImage.scaleIntensity();

    // reconstructedImage.displayImage("Reconstructed Image");

    return 0;
}
