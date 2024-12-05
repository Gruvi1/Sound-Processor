#pragma once

#include "abstract_converter.h"


class TEchoConverter: public IConverter {
public:
    TEchoConverter() = default;
    ~TEchoConverter() override = default;
    void Convert(IAudioFormat& file, std::vector<std::string>& instruction) const override;
};