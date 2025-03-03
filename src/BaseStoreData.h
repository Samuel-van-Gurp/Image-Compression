#ifndef BASE_STORE_DATA_H
#define BASE_STORE_DATA_H

#include "BaseCompressedImageHolder.h"
#include <memory>
#include <string>

class BaseStoreData
{
public:
    virtual ~BaseStoreData() = default;

    virtual void writeToBinary(const std::string &fileName, const std::string &filePath, const BaseCompressedImageHolder &compressedData)  = 0;
    virtual std::unique_ptr<BaseCompressedImageHolder> readFromBinary(const std::string &fileName, const std::string &filePath)  = 0;
};

#endif