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
};