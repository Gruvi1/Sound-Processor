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

    uint16_t GetSample(size_t n) const;
    uint32_t GetSampleRate() const;
    size_t GetLastSample() const;

    void SendSample(const uint16_t& sample);
};


class IAudioFormat {
public:
    virtual ~IAudioFormat() = default;
};
