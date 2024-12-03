#include "audio_format.h"


TAudioFormat::TAudioFormat(TWav* fileOut) {
    ptrWavOut = fileOut;
}

void TAudioFormat::Open(TWavReader* fileIn) {
    ptrWavIn = fileIn;
}

int16_t TAudioFormat::GetSample() const {
    return ptrWavOut->GetSample();
}

int16_t TAudioFormat::GetExtraSample() const {
    return ptrWavIn->GetSample();
}

uint32_t TAudioFormat::GetSampleRate() const {
    return ptrWavOut->GetHeader().sampleRate;
}

size_t TAudioFormat::GetLastSample() const {
    uint32_t subchunk2Size = ptrWavOut->GetHeader().subchunk2Size;
    uint32_t blockAlign = ptrWavOut->GetHeader().blockAlign;
    size_t lastSample = subchunk2Size / blockAlign;

    return lastSample;
}

void TAudioFormat::SendSample(const int16_t& sample) {
    ptrWavOut->SendSample(sample);
}

void TAudioFormat::Seekp(size_t shift, std::ios_base::seekdir dir) {
    ptrWavOut->Seekp(shift, dir);
}

void TAudioFormat::Seekg(size_t shift, std::ios_base::seekdir dir) {
    ptrWavIn->Seekg(shift, dir);
}

size_t TAudioFormat::GetCurrentInPosition() {
    return ptrWavIn->GetCurrentPosition();
}

size_t TAudioFormat::GetCurrentOutPosition() {
    return ptrWavOut->GetCurrentPosition();
}

void TAudioFormat::SetInPosition(size_t position) {
    ptrWavIn->SetPosition(position);
}

void TAudioFormat::SetOutPosition(size_t position) {
    ptrWavOut->SetPosition(position);
}