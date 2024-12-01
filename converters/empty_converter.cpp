#include "empty_converter.h"


int16_t TEmptyConverter::Convert(const TAudioFormat& file) const {
    int16_t convertedSample;
    convertedSample = file.GetSample();

    return convertedSample;
}