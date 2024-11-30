#include "empty_converter.h"


uint16_t TEmptyConverter::Convert(const TAudioFormat& file) const {
    uint16_t convertedSample;
    convertedSample = file.GetSample(1);

    return convertedSample;
}