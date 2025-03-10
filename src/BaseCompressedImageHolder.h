#pragma once

class BaseCompressedImageHolder
{
public:
    virtual ~BaseCompressedImageHolder() = default;

    virtual float getCompressionRatio() const = 0;
};
