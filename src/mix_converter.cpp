#include "mix_converter.h"


void TMixConverter::Convert(IAudioFormat& file, std::vector<std::string>& instruction) const {
    size_t curInPosition = file.GetCurrentInPosition();
    size_t curOutPosition = file.GetCurrentOutPosition();

    size_t startSample = file.GetSampleRate() * std::stoull(instruction[2]);
    size_t endSample = file.GetSampleRate() * (std::stoull(instruction[3]) - std::stoull(instruction[2]));

    file.SetOutPosition(sizeof(int16_t) * startSample, std::ios::cur);
    file.SetInPosition(sizeof(int16_t) * startSample, std::ios::cur);

    std::cout << "Copying successful" << std::endl;

    for (size_t i = 0; i != endSample; ++i) {
        int16_t convertedSample = file.GetSample()/2 + file.GetExtraSample()/2;
        file.SetOutPosition(-sizeof(convertedSample), std::ios::cur);
        file.SendSample(convertedSample);
    }

    file.SetInPosition(curInPosition);
    file.SetOutPosition(curOutPosition);

    std::cout << "Converting successful" << std::endl;
}