#pragma once

#include <memory>
#include "empty_converter.h"
#include "mute_converter.h"
#include "mix_converter.h"
#include "echo_converter.h"


class TConverterFactory {
public:
    std::unique_ptr<IConverter> MakeConverter(std::string_view typeConverter);
};