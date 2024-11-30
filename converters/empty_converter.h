#pragma once

#include "abstract_converter.h"


class TEmptyConverter: public IConverter {
public:
    TEmptyConverter() = default;
    ~TEmptyConverter() override = default;
    uint16_t Convert(const TAudioFormat& file) const override;
};