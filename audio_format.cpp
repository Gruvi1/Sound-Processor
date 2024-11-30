#include "audio_format.h"

TAudioFormat::TAudioFormat(TWav* fileOut) {
    ptrWavOut = fileOut;
}

void TAudioFormat::Open(TWavReader* fileIn) {
    ptrWavIn = fileIn;
}

uint16_t TAudioFormat::GetSample(size_t n) const {
    return ptrWavIn->GetSample();
}

uint32_t TAudioFormat::GetSampleRate() const {
    return ptrWavIn->GetHeader().sampleRate;
}

// TODO: добавить поддержку разных типов. Если тип файла == wav, то lastSample считается так
size_t TAudioFormat::GetLastSample() const {
    uint32_t subchunk2Size = ptrWavIn->GetHeader().subchunk2Size;
    uint32_t blockAlign = ptrWavIn->GetHeader().blockAlign;
    size_t lastSample = subchunk2Size / blockAlign;

    return lastSample;
}

void TAudioFormat::SendSample(const uint16_t& sample) {
    ptrWavOut->SendSample(sample);
}