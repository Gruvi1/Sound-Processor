#include "converter_factory.h"


std::unique_ptr<IConverter> TConverterFactory::MakeConverter(std::string_view typeConverter) {
    if (typeConverter == "mute") {
        return std::make_unique<TMuteConverter>();
    }
    else if (typeConverter == "mix") {
        return std::make_unique<TMixConverter>();
    }
    else if (typeConverter == "echo") {
        return std::make_unique<TEchoConverter>();
    }
    else {
        return std::make_unique<TEmptyConverter>();
    }
}