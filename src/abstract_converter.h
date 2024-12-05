#pragma once

#include "audio_format.h"
#include <iostream>

class IConverter {
public:
    virtual void Convert(IAudioFormat& file, std::vector<std::string>& instruction) const = 0;
    virtual ~IConverter() = default;
};