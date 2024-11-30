#pragma once

#include <memory>
#include "mute_converter.h"
#include "empty_converter.h"


class TConverterFactory {
public:
    std::unique_ptr<IConverter> MakeConverter(std::string_view typeConverter);
};