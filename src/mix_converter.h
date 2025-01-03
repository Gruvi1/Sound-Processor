#pragma once

#include "abstract_converter.h"


class TMixConverter: public IConverter {
public:
    TMixConverter() = default;
    ~TMixConverter() override = default;
    void Convert(IAudioFormat& file, std::vector<std::string>& instruction) const override;
};