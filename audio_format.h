#pragma once

#include "wav/wav_editor.h"


class TAudioFormat {
private:
    TWavReader* ptrWavIn;
    TWav* ptrWavOut;

public:
    TAudioFormat(TWav* fileOut);
    ~TAudioFormat() = default;
    void Open(TWavReader* file);
    int16_t GetSample() const;
    int16_t GetExtraSample() const;
    uint32_t GetSampleRate() const;
    size_t GetLastSample() const;
    void SendSample(const int16_t& sample);
    void Seekp(size_t shift, std::ios_base::seekdir dir);
    void Seekg(size_t shift, std::ios_base::seekdir dir);
    size_t GetCurrentInPosition();
    size_t GetCurrentOutPosition();
    void SetInPosition(size_t position);
    void SetOutPosition(size_t position);
};