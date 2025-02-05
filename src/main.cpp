#include "Image.h"
#include "Compressor.h"
#include <opencv2/opencv.hpp>
#include <iostream>

int main() {
    
    
    
    Image img = Image("C:/Users/svangurp/Desktop/projects/ImageCompression/images/GrayscaleTestImg/lena1.tif");

    img.displayImage();

    Compressor compressor = Compressor();

    // get the DFT of the image
    cv::Mat dftImage = compressor.DFT(img.getImage());

    // get the IDFT of the image
    Image reconImg = Image(compressor.IDFT(dftImage));

    // display the IDFT image
    reconImg.displayImage();
    
    return 0;
}
