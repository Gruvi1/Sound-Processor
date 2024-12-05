#pragma once

#include "abstract_converter.h"


class TChorusConverter: public IConverter {
public:
    TChorusConverter() = default;
    ~TChorusConverter() override = default;
    void Convert(IAudioFormat& file, std::vector<std::string>& instruction) const override;
};