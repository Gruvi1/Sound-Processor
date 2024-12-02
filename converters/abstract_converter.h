#pragma once

#include "../wav/wav_editor.h"
#include "../audio_format.h"
#include <iostream>


class IConverter {
public:
    virtual void Convert(TAudioFormat& file, std::vector<std::string>& instruction) const = 0;
    virtual ~IConverter() = default;
};