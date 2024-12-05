#include "echo_converter.h"


void AddEchoForSample(int16_t sample, IAudioFormat& file) {
    int16_t tempSample = 0;
    size_t curOutPosition = file.GetCurrentOutPosition();

    for (int i = 0; i != 3; ++i) {
        // TODO: size_t delay = 5512 (frequency / 8)
        file.SetOutPosition(5512 * 2, std::ios::cur);
        tempSample = (file.GetSample()* 1.1  + sample * (0.5 - 0.1 * i)) / 1.3;
        file.SetOutPosition(-sizeof(tempSample), std::ios::cur);
        file.SendSample(tempSample);
    }

    file.SetOutPosition(curOutPosition);
}

void TEchoConverter::Convert(IAudioFormat& file, std::vector<std::string>& instruction) const {
    size_t curOutPosition = file.GetCurrentOutPosition();

    size_t startTime = std::stoull(instruction[instruction.size() - 2]);
    size_t endTime = std::stoull(instruction[instruction.size() - 1]);
    size_t startSample = file.GetSampleRate() * startTime;
    size_t endSample = file.GetSampleRate() * (endTime - startTime);

    file.SetOutPosition(sizeof(int16_t) * startSample, std::ios::cur);

    std::cout << "Copying successful" << std::endl;

    for (size_t i = 0; i != endSample; ++i) {
        int16_t convertedSample = file.GetSample();
        AddEchoForSample(convertedSample, file);
    }

    file.SetOutPosition(curOutPosition);

    std::cout << "Converting successful" << std::endl;
}