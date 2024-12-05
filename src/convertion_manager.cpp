#include "sound_processor/convertion_manager.h"
#include "../include/sound_processor/convertion_manager.h"


TConvertionManager::TConvertionManager(const int& argc, char* argv[]) {
    for (size_t i = 1; i != argc - 2; ++i) {
        filesIn.push_back(std::make_unique<TWavReader>(argv[i]));
    }

    fileOut = std::make_unique<TWav>(argv[argc - 2]);

    TConfigParser ConfigParser;
    config = ConfigParser.Parse(argv[argc - 1]);
}

void TConvertionManager::ConvertByConfig() {
    TConverterFactory ConverterFactory;
    std::unique_ptr<IConverter> converter;

    TWavFormat AudioFormat(fileOut.get());

    CopyData(AudioFormat, config[0][1]);

    for (size_t i = 0; i != config.size(); ++i) {
        std::vector<std::string> instruction = config[i];

        converter = ConverterFactory.MakeConverter(instruction[0]);

        size_t fileNum;
        if (instruction.size() > 3) {
            fileNum = std::stoull(instruction[1].erase(0, 1));
            AudioFormat.Open(filesIn[fileNum - 1].get());
        }

        converter.get()->Convert(AudioFormat, instruction);
    }
}

void TConvertionManager::CopyData(TWavFormat& AudioFormat, const std::string& strFileNum) {
    std::string temp = strFileNum;
    size_t fileNum = std::stoull(temp.erase(0, 1));

    fileOut.get()->CopyHeader(*(filesIn[fileNum - 1].get()));
    fileOut.get()->WriteHeader();

    AudioFormat.Open(filesIn[fileNum - 1].get());

    size_t curInPosition = filesIn[fileNum - 1].get()->GetCurrentPosition();
    size_t curOutPosition = fileOut.get()->GetCurrentPosition();

    size_t lastSample = AudioFormat.GetLastSample();

    for (size_t i = 0; i != lastSample; ++i) {
        int16_t sample = AudioFormat.GetExtraSample();
        AudioFormat.SendSample(sample);
    }

    filesIn[fileNum - 1].get()->Seekg(curInPosition);
    fileOut.get()->Seekp(curOutPosition);
}
