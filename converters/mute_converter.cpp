#include "mute_converter.h"


uint16_t TMuteConverter::Convert(const TAudioFormat& file) const {
    uint16_t convertedSample;
    convertedSample = file.GetSample(1) * 0;

    // size_t startTime = std::stoull(instruction[instruction.size() - 2]);
    // size_t endTime = std::stoull(instruction[instruction.size() - 1]);

    // size_t startSample = file.GetSampleRate() * startTime;
    // size_t endSample = file.GetSampleRate() * endTime;
    // size_t lastSample = file.GetLastSample();

    // for (size_t i = 0; i != startSample; ++i) {
    //     uint16_t sample = file.GetSample(1);
    //     convertedSamples.push_back(sample);
    // }

    // for (size_t i = startSample; i != endSample; ++i) {
    //     uint16_t sample = file.GetSample(1) * 0;
    //     convertedSamples.push_back(sample);
    // }

    // for (size_t i = endSample; i != lastSample; ++i) {
    //     uint16_t sample = file.GetSample(1);
    //     convertedSamples.push_back(sample);
    // }

    return convertedSample;
}