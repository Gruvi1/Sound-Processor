#pragma once

#include "abstract_converter.h"


class TMuteConverter: public IConverter {
public:
    TMuteConverter() = default;
    ~TMuteConverter() override = default;
    int16_t Convert(const TAudioFormat& file) const override;
};