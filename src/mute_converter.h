#pragma once

#include "abstract_converter.h"


class TMuteConverter: public IConverter {
public:
    TMuteConverter() = default;
    ~TMuteConverter() override = default;
    void Convert(TAudioFormat& file, std::vector<std::string>& instruction) const override;
};