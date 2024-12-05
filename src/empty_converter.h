#pragma once

#include "abstract_converter.h"


class TEmptyConverter: public IConverter {
public:
    TEmptyConverter() = default;
    ~TEmptyConverter() override = default;
    void Convert(IAudioFormat& file, std::vector<std::string>& instruction) const override;
};