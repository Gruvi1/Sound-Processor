#pragma once

#include "../wav/wav_editor.h"
#include "../audio_format.h"


class IConverter {
public:
    virtual uint16_t Convert(const TAudioFormat& file) const = 0;
    // virtual std::vector<uint16_t> Convert(const TAudioFormat& file, const std::vector<std::string>& instruction) const = 0;
    virtual ~IConverter() = default;
};