#include "convertion_manager.h"

TConvertionManager::TConvertionManager(const int& argc, char* argv[]) {
    for (size_t i = 1; i != argc - 2; ++i) {
        TWavReader file(argv[i]);
        filesIn.push_back(std::make_unique<TWavReader>(argv[i]));
    }

    fileOut = std::make_unique<TWav>(argv[argc - 2]);

    TConfigParser ConfigParser;
    config = ConfigParser.Parse(argv[argc - 1]);
}

void TConvertionManager::UseConverter(const IConverter* converter, std::pair<size_t, size_t> interval, TAudioFormat& AudioFormat) {
    size_t startSample = AudioFormat.GetSampleRate() * interval.first;
    size_t endSample = AudioFormat.GetSampleRate() * interval.second;
    size_t lastSample = AudioFormat.GetLastSample();

    for (size_t i = 0; i != startSample; ++i) {
        uint16_t sample = AudioFormat.GetSample(1);
        AudioFormat.SendSample(sample);
    }

    for (size_t i = startSample; i != endSample; ++i) {
        uint16_t sample = converter->Convert(AudioFormat);
        AudioFormat.SendSample(sample);
    }

    for (size_t i = endSample; i != lastSample; ++i) {
        uint16_t sample = AudioFormat.GetSample(1);
        AudioFormat.SendSample(sample);
    }
}

void TConvertionManager::ConvertByConfig() {
    TConverterFactory ConverterFactory;
    std::unique_ptr<IConverter> converter;
    TAudioFormat AudioFormat(fileOut.get());

    for (size_t i = 0; i != config.size(); ++i) {
        std::vector<std::string> instruction = config[i];

        converter = ConverterFactory.MakeConverter(instruction[0]);

        size_t fileNum = std::stoull(instruction[1].erase(0, 1));
        AudioFormat.Open(filesIn[fileNum - 1].get());
        fileOut.get()->CopyHeader(*(filesIn[fileNum - 1].get()));
        fileOut.get()->WriteHeader();

        size_t startTime = std::stoull(instruction[2]);
        size_t endTime = std::stoull(instruction[3]);
        std::pair<size_t, size_t> interval = {startTime, endTime};

        size_t curPositionIn = filesIn[fileNum - 1].get()->GetCurrentInPosition();
        size_t curPositionOut = fileOut.get()->GetCurrentOutPosition();
        // size_t curPositionIn2 = fileOut.get()->GetCurrentInPosition();
        UseConverter(converter.get(), interval, AudioFormat);
        filesIn[fileNum - 1].get()->SetInPosition(curPositionIn);
        fileOut.get()->SetOutPosition(curPositionOut);
        // fileOut.get()->SetInPosition(curPositionIn2);
    }
}