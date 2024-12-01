#include "mute_converter.h"


int16_t TMuteConverter::Convert(const TAudioFormat& file) const {
    int16_t convertedSample;
    convertedSample = file.GetSample() * 0;
    
    return convertedSample;
}