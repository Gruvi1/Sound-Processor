#include "audio_format.h"


TWavFormat::TWavFormat(TWav* fileOut) {
    ptrWavOut = fileOut;
}

void TWavFormat::Open(TWavReader* fileIn) {
    ptrWavIn = fileIn;
}

int16_t TWavFormat::GetSample() const {
    return ptrWavOut->GetSample();
}

int16_t TWavFormat::GetExtraSample() const {
    return ptrWavIn->GetSample();
}

uint32_t TWavFormat::GetSampleRate() const {
    return ptrWavOut->GetHeader().sampleRate;
}

size_t TWavFormat::GetLastSample() const {
    uint32_t subchunk2Size = ptrWavOut->GetHeader().subchunk2Size;
    uint32_t blockAlign = ptrWavOut->GetHeader().blockAlign;
    size_t lastSample = subchunk2Size / blockAlign;

    return lastSample;
}

void TWavFormat::SendSample(const int16_t& sample) {
    ptrWavOut->SendSample(sample);
}

size_t TWavFormat::GetCurrentInPosition() {
    return ptrWavIn->GetCurrentPosition();
}

size_t TWavFormat::GetCurrentOutPosition() {
    return ptrWavOut->GetCurrentPosition();
}

void TWavFormat::SetInPosition(size_t position) {
    ptrWavIn->Seekg(position);
}

void TWavFormat::SetInPosition(size_t position, std::ios_base::seekdir dir) {
    ptrWavIn->Seekg(position, dir);
}

void TWavFormat::SetOutPosition(size_t position) {
    ptrWavOut->Seekp(position);
}

void TWavFormat::SetOutPosition(size_t position, std::ios_base::seekdir dir) {
    ptrWavOut->Seekp(position, dir);
}