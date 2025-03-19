#include "Image.h"
#include "API/ImageCompressionAPI.h"
#include <chrono>  

int main()
{

    ImageCompressionAPI api = ImageCompressionAPI::create(Method::DCT);


    Image img = Image("C:/Users/svangurp/Desktop/projects/ImageCompression/images/GrayscaleTestImg/ALTEN.jpg");
    // img.displayImage();
    auto start = std::chrono::high_resolution_clock::now();
    auto compressedImage = api.compress(img, CompressionLevel::VERY_HIGH);
    auto end = std::chrono::high_resolution_clock::now();
    std::chrono::duration<double> duration = end - start;

    std::cout<<"Time taken to compress: "<<duration.count()<<" seconds"<<std::endl;
    // api.saveCompressed(*compressedImage, "ALTEN.samuel", "C:/Users/svangurp/Desktop/projects/ImageCompression/images/imgOUT/");

    // auto compressedImageHolderReadFormFile = api.loadCompressed("ALTEN.samuel", "C:/Users/svangurp/Desktop/projects/ImageCompression/images/imgOUT/");

    // Image reconImage = api.decompress(*compressedImageHolderReadFormFile);

    // float compressionRatio = compressedImageHolderReadFormFile->getCompressionRatio();

    // reconImage.displayImage("Reconstructed Image (compression ratio: " + std::to_string(compressionRatio) + ")" );

    return 0;
}
