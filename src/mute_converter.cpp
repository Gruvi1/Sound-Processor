#include "mute_converter.h"


void TMuteConverter::Convert(IAudioFormat& file, std::vector<std::string>& instruction) const {
    size_t curOutPosition = file.GetCurrentOutPosition();

    size_t startTime = std::stoull(instruction[instruction.size() - 2]);
    size_t endTime = std::stoull(instruction[instruction.size() - 1]);
    size_t startSample = file.GetSampleRate() * startTime;
    size_t endSample = file.GetSampleRate() * (endTime - startTime);

    file.SetOutPosition(sizeof(int16_t) * startSample, std::ios::cur);

    std::cout << "Copying successful" << std::endl;

    for (size_t i = 0; i != endSample; ++i) {
        int16_t convertedSample = 0;
        file.SendSample(convertedSample);
    }

    file.SetOutPosition(curOutPosition);

    std::cout << "Converting successful" << std::endl;
}