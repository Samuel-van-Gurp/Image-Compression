#include "Image.h"
#include "API/ImageCompressionAPI.h"

#include <opencv2/opencv.hpp>
#include <iostream>

int main()
{
    ImageCompressionAPI api = ImageCompressionAPI(Method::DFT);

    Image img = Image("C:/Users/svangurp/Desktop/projects/ImageCompression/images/GrayscaleTestImg/camera.tif");

    auto compressedImage = api.compress(img, CompressionLevel::LOW);

    api.saveCompressed(*compressedImage, "camera.samuel", "C:/Users/svangurp/Desktop/projects/ImageCompression/images/imgOUT/");

    auto compressedImageHolderReadFormFile = api.loadCompressed("camera.samuel", "C:/Users/svangurp/Desktop/projects/ImageCompression/images/imgOUT/");

    Image reconImage = api.decompress(*compressedImageHolderReadFormFile);

    reconImage.displayImage("Reconstructed Image");

    return 0;
}
