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
    size_t endSample = AudioFormat.GetSampleRate() * interval.second - startSample;
    size_t lastSample = AudioFormat.GetLastSample() - endSample;

    for (size_t i = 0; i != startSample; ++i) {
        int16_t sample = AudioFormat.GetSample();
        AudioFormat.Seekp(-sizeof(sample), std::ios::cur);
        AudioFormat.SendSample(sample);
        int16_t temp = AudioFormat.GetExtraSample();
    }
        std::cout << "hhhhhhhhhhhhhhhhhh" << std::endl;

    for (size_t i = 0; i != endSample; ++i) {
        int16_t sample = converter->Convert(AudioFormat);
        AudioFormat.Seekp(-sizeof(sample), std::ios::cur);
        AudioFormat.SendSample(sample);
    }
        std::cout << "hhhhhhhhhhhhhhhhhh" << std::endl;

    // for (size_t i = 0; i != lastSample - 1; ++i) {
    //     int16_t sample = AudioFormat.GetSample();
    //     AudioFormat.Seekp(-sizeof(sample), std::ios::cur);
    //     AudioFormat.SendSample(sample);
    // }
    //     std::cout << "hhhhhhhhhhhhhhhhhh" << std::endl;
}

void TConvertionManager::ConvertByConfig() {
    TConverterFactory ConverterFactory;
    std::unique_ptr<IConverter> converter;
    TAudioFormat AudioFormat(fileOut.get());

    CopyData(AudioFormat, config[0][1]);


    for (size_t i = 0; i != config.size(); ++i) {
        std::vector<std::string> instruction = config[i];

        converter = ConverterFactory.MakeConverter(instruction[0]);

        size_t fileNum = std::stoull(instruction[1].erase(0, 1));
        AudioFormat.Open(filesIn[fileNum - 1].get());


        size_t startTime = std::stoull(instruction[2]);
        size_t endTime = std::stoull(instruction[3]);
        std::pair<size_t, size_t> interval = {startTime, endTime};

        size_t curPositionIn = filesIn[fileNum - 1].get()->GetCurrentInPosition();
        size_t curPositionOut = fileOut.get()->GetCurrentPosition();
        UseConverter(converter.get(), interval, AudioFormat);
        filesIn[fileNum - 1].get()->SetInPosition(curPositionIn);
        fileOut.get()->SetPosition(curPositionOut);
    }
}

void TConvertionManager::CopyData(TAudioFormat& AudioFormat, const std::string& strFileNum) {
    std::string temp = strFileNum;
    size_t fileNum = std::stoull(temp.erase(0, 1));
    fileOut.get()->CopyHeader(*(filesIn[fileNum - 1].get()));
    fileOut.get()->WriteHeader();
    AudioFormat.Open(filesIn[fileNum - 1].get());

    size_t curPositionIn = filesIn[fileNum - 1].get()->GetCurrentInPosition();
    size_t curPositionOut = fileOut.get()->GetCurrentPosition();

    size_t lastSample = AudioFormat.GetLastSample();


    for (size_t i = 0; i != lastSample - 1; ++i) {
        int16_t sample = AudioFormat.GetExtraSample();
        AudioFormat.SendSample(sample);
    }

    filesIn[fileNum - 1].get()->SetInPosition(curPositionIn);
    fileOut.get()->SetPosition(curPositionOut);
}
