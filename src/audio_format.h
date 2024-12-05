#pragma once

#include "wav_editor.h"

class IAudioFormat {
public:
    virtual ~IAudioFormat() = default;
    virtual int16_t GetSample() const = 0;
    virtual int16_t GetExtraSample() const = 0;
    virtual uint32_t GetSampleRate() const = 0;
    virtual size_t GetLastSample() const = 0;
    virtual void SendSample(const int16_t& sample)  = 0;
    virtual size_t GetCurrentInPosition()  = 0;
    virtual size_t GetCurrentOutPosition()  = 0;
    virtual void SetInPosition(size_t shift)  = 0;
    virtual void SetInPosition(size_t shift, std::ios_base::seekdir dir) = 0;
    virtual void SetOutPosition(size_t shift) = 0;
    virtual void SetOutPosition(size_t shift, std::ios_base::seekdir dir) = 0;
};


class TWavFormat: public IAudioFormat {
private:
    TWavReader* ptrWavIn;
    TWav* ptrWavOut;

public:
    TWavFormat(TWav* fileOut);
    ~TWavFormat() override = default;
    void Open(TWavReader* file);
    int16_t GetSample() const override;
    int16_t GetExtraSample() const override;
    uint32_t GetSampleRate() const override;
    size_t GetLastSample() const override;
    void SendSample(const int16_t& sample) override;
    size_t GetCurrentInPosition() override;
    size_t GetCurrentOutPosition() override;
    void SetInPosition(size_t shift) override;
    void SetInPosition(size_t shift, std::ios_base::seekdir dir) override;
    void SetOutPosition(size_t shift) override;
    void SetOutPosition(size_t shift, std::ios_base::seekdir dir) override;
};