#pragma once

#include "abstract_converter.h"


class TMixConverter: public IConverter {
public:
    TMixConverter() = default;
    ~TMixConverter() override = default;
    int16_t Convert(const TAudioFormat& file) const override;
};