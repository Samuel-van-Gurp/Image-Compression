#include "BaseCompressedImageHolder.h"
#include "ICompressionStrategy.h"
#include "BaseStoreData.h"
#include "Image.h"
#include "CompressionLevel.h"

#include "DCT/DCTCompression.h"
#include "DFT/DFTCompression.h"
#include "DFT/StoreDFTData.h"
#include "DCT/StoreDCTData.h"

#include <memory>

enum class Method
{
    DCT, // Discrete Cosine Transform (JPEG-like)
    DFT  // Discrete Fourier Transform
};

class ImageCompressionAPI
{
public:
    static ImageCompressionAPI create(Method method); 
    
    ImageCompressionAPI(std::unique_ptr<ICompressionStrategy> compressionStrategy,
                        std::unique_ptr<BaseStoreData> dataStoreStrategy);

    std::unique_ptr<BaseCompressedImageHolder> compress(const Image &image,CompressionLevel level = CompressionLevel::HIGH);

    Image decompress(BaseCompressedImageHolder &compressedData);

    void saveCompressed(const BaseCompressedImageHolder &compressedData, const std::string &fileName, const std::string &filePath);

    std::unique_ptr<BaseCompressedImageHolder> loadCompressed(const std::string &fileName, const std::string &filePath);

private:
    std::unique_ptr<ICompressionStrategy> m_CompressionStrategy;
    std::unique_ptr<BaseStoreData> m_DataStoreStrategy;
};
