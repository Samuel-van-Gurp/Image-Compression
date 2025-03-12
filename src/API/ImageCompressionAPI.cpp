#include "ImageCompressionAPI.h"

ImageCompressionAPI ImageCompressionAPI::create(Method method)
{
    switch (method)
    {
    case Method::DCT:
        return ImageCompressionAPI(std::make_unique<DCTCompression>(),
                                   std::make_unique<StoreDCTData>());
    case Method::DFT:
        return ImageCompressionAPI(std::make_unique<DFTCompression>(),
                                   std::make_unique<StoreDFTData>());
    default:
        throw std::invalid_argument("Invalid compression method");
    }
}

ImageCompressionAPI::ImageCompressionAPI(std::unique_ptr<ICompressionStrategy> compressionStrategy, std::unique_ptr<BaseStoreData> dataStoreStrategy)
    : m_CompressionStrategy(std::move(compressionStrategy)), m_DataStoreStrategy(std::move(dataStoreStrategy))
{
}

std::unique_ptr<BaseCompressedImageHolder> ImageCompressionAPI::compress(const Image &image, CompressionLevel level)
{
    return m_CompressionStrategy->compress(image, level);
}

Image ImageCompressionAPI::decompress(BaseCompressedImageHolder &compressedData)
{
    return m_CompressionStrategy->decompress(compressedData);
}

void ImageCompressionAPI::saveCompressed(const BaseCompressedImageHolder &compressedData, const std::string &fileName, const std::string &filePath)
{
    m_DataStoreStrategy->writeToBinary(fileName, filePath, compressedData);
}

std::unique_ptr<BaseCompressedImageHolder> ImageCompressionAPI::loadCompressed(const std::string &fileName, const std::string &filePath)
{
    return m_DataStoreStrategy->readFromBinary(fileName, filePath);
}
