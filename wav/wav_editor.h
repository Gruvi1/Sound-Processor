#pragma once

#include <cstdint>
#include <array>
#include <vector>
#include <string>
#include <fstream>


class IWavFile {
protected:
    struct THeader {
        // be - big endian
        // le - little endian

        std::array<char, 4> chunkId; // (be) символы "RIFF" в ASCII кодировке
        uint32_t chunkSize; // (le) размер файла, начиная с этой позиции (size - 8)
        std::array<char, 4> format; // (be) символы "WAVE"
        std::array<char, 4> subchunk1Id; // (be) символы "fmt"
        uint32_t subchunk1Size; // (le) размер подструктуры (для PCM 16)
        int16_t audioFormat; // (le) аудиоформат (PCM = 1)
        int16_t numChannels; // (le) количество каналов
        uint32_t sampleRate; // (le) частота дискретизации (кол-во сэмплов в секунду)
        uint32_t byteRate; // (le) количество байт в секунду (все каналы) [sampleRate * numChannels * bitsPerSample / 8]
        int16_t blockAlign; // (le) количество байт в сэмпле (все каналы) [numChannels * bitsPerSample / 8]
        int16_t bitsPerSample; // (le) количество бит в сэмпле (глубина)
        std::array<char, 4> subchunk2Id; // (be) символы "data"
        uint32_t subchunk2Size; // (le) количество байт в области данных [byteRate * duration]
    };

    std::string pathFile;
    THeader header;

public:
    virtual ~IWavFile() = default;
};


class TWavReader: public virtual IWavFile {
private:
    std::ifstream file;

public:
    TWavReader() = default;
    TWavReader(const std::string& pathFile);
    ~TWavReader() override;
    int16_t GetSample();
    const THeader& GetHeader() const;
    size_t GetCurrentInPosition();
    void SetInPosition(size_t position);
};


class TWav: public virtual IWavFile {
private:
    std::fstream file;

public:
    TWav() = default;
    TWav(const std::string& pathFile);
    ~TWav() override;
    void CopyHeader(const TWavReader& otherWav);
    void WriteHeader();
    int16_t GetSample();
    void SendSample(const int16_t& sample);
    const THeader& GetHeader() const;

    size_t GetCurrentPosition();
    void SetPosition(size_t position);
    void Seekp(size_t shift, std::ios_base::seekdir dir);
};