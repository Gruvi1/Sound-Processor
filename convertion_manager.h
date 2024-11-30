#pragma once

#include "config_parser/config_parser.h"
#include "audio_format.h"
#include "converters/converter_factory.h"


class TConvertionManager {
private:
    std::vector<std::unique_ptr<TWavReader>> filesIn;
    std::unique_ptr<TWav> fileOut;
    std::vector<std::vector<std::string>> config;

public:
    TConvertionManager(const int& argc, char* argv[]);
    void ConvertByConfig();

private:
    void UseConverter(const IConverter* converter, std::pair<size_t, size_t> interval, TAudioFormat& AudioFormat);
};