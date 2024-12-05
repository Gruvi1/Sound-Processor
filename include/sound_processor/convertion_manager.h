#pragma once

#include "config_parser.h"
#include "audio_format.h"
#include "converter_factory.h"

class TConvertionManager {
private:
    std::vector<std::unique_ptr<TWavReader>> filesIn;
    std::unique_ptr<TWav> fileOut;
    std::vector<std::vector<std::string>> config;

public:
    TConvertionManager(const int& argc, char* argv[]);
    ~TConvertionManager() = default;
    void ConvertByConfig();

private:
    void CopyData(TWavFormat& AudioFormat, const std::string& strFileNum);
};