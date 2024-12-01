#include "mix_converter.h"


int16_t TMixConverter::Convert(const TAudioFormat& file) const {
    int16_t convertedSample;
    convertedSample = (file.GetSample() + file.GetExtraSample())/2;

    return convertedSample;
}
