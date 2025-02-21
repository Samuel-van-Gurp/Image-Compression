#include "Image.h"

#include "DFT/DFTCompressor.h"
#include "DFT/SparseRepresentation.h"
#include "DFT/StoringData.h"

#include "DCT/DCT.h"
#include "DCT/ImageChopper.h"
#include "DCT/DCTCompression.h"
#include "DCT/DCTEncoding.h"
#include "DCT/ZigzagDCTcoefficientsOrder.h"
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

    // DCTTransformationHandler dctTransformationHandler;
    
    // DCTEncoding dctEncoding = DCTEncoding(RunLengthEnoding(), ZigzagDCTcoefficientsOrder());

    // Image img = Image("C:/Users/svangurp/Desktop/projects/ImageCompression/images/GrayscaleTestImg/camera.tif");
    // img.displayImage();

    // auto img_vec = img.getImageAsVector();

    // auto TransformedImage = dctTransformationHandler.DCTTransformImage(img_vec, QuantizationTable::ultraHighCompressionTable);

    // auto encodedImage = dctEncoding.encodeImageBlocks(TransformedImage);

    // auto decodedImage = dctEncoding.decodeImageBlocks(encodedImage);

    // auto inverseTransformedImage = dctTransformationHandler.inverseDCTTransformImage(decodedImage, QuantizationTable::ultraHighCompressionTable, static_cast<int>(img_vec.size()), static_cast<int>(img_vec[0].size()));

    // Image decompressedImg = Image(inverseTransformedImage);

    // decompressedImg.displayImage("Decompressed Image");

    // decompressedImg.DisplayDiffImage(img);

    return 0;
}
