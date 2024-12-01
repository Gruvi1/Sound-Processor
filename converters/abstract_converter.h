#pragma once

#include "../wav/wav_editor.h"
#include "../audio_format.h"

#include <iostream>

class IConverter {
public:
    virtual int16_t Convert(const TAudioFormat& file) const = 0;
    virtual ~IConverter() = default;
};