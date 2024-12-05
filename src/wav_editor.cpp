#include "wav_editor.h"

TWavReader::TWavReader(const std::string& pathFile) {
    file.open(pathFile, std::ios::in | std::ios::binary);

    file.read(reinterpret_cast<char*>(&header.chunkId), sizeof(header.chunkId));
    file.read(reinterpret_cast<char*>(&header.chunkSize), sizeof(header.chunkSize));
    file.read(reinterpret_cast<char*>(&header.format), sizeof(header.format));


    size_t curPosition = file.tellg();
    int count = 0;
    std::string wordFmt = "fmt ";
    while (count != 4) {
        count = 0;
        file.seekg(curPosition, std::ios::beg);
        for (int i = 0; i != header.subchunk1Id.size(); ++i) {
            file.get(header.subchunk1Id[i]);
            if (header.subchunk1Id[i] == wordFmt[i]) {
                ++count;
            }
        }
        file.read(reinterpret_cast<char*>(&header.subchunk1Size), sizeof(header.subchunk1Size));
        curPosition += header.subchunk1Size + sizeof(header.subchunk1Size) + sizeof(header.subchunk1Id);
    }



    file.read(reinterpret_cast<char*>(&header.audioFormat), sizeof(header.audioFormat));
    if (header.audioFormat != 1) {

        this->~TWavReader();
        exit(EXIT_FAILURE);
    }
    if (header.audioFormat != 1) {

        this->~TWavReader();
        exit(EXIT_FAILURE);
    }
    file.read(reinterpret_cast<char*>(&header.numChannels), sizeof(header.numChannels));
    if (header.numChannels != 1) {
        this->~TWavReader();
        exit(EXIT_FAILURE);
    }
    if (header.numChannels != 1) {
        this->~TWavReader();
        exit(EXIT_FAILURE);
    }
    file.read(reinterpret_cast<char*>(&header.sampleRate), sizeof(header.sampleRate));
    if (header.sampleRate != 44100) {
        this->~TWavReader();
        exit(EXIT_FAILURE);
    }
    file.read(reinterpret_cast<char*>(&header.byteRate), sizeof(header.byteRate));
    file.read(reinterpret_cast<char*>(&header.blockAlign), sizeof(header.blockAlign));
    file.read(reinterpret_cast<char*>(&header.bitsPerSample), sizeof(header.bitsPerSample));
    if (header.bitsPerSample != 16) {
        this->~TWavReader();
        exit(EXIT_FAILURE);
    }
    if (header.bitsPerSample != 16) {
        this->~TWavReader();
        exit(EXIT_FAILURE);
    }

    curPosition = file.tellg();
    count = 0;
    std::string wordData = "data";
    while (count != 4) {
        count = 0;
        file.seekg(curPosition, std::ios::beg);
        for (int i = 0; i != header.subchunk2Id.size(); ++i) {
            file.get(header.subchunk2Id[i]);
            if (header.subchunk2Id[i] == wordData[i]) {
                ++count;
            }
        }
        file.read(reinterpret_cast<char*>(&header.subchunk2Size), sizeof(header.subchunk2Size));
        curPosition += header.subchunk2Size + sizeof(header.subchunk2Size) + sizeof(header.subchunk2Id);
    }
}

TWavReader::~TWavReader() {
    file.close();
}

int16_t TWavReader::GetSample() {
    int16_t sample;
    file.read(reinterpret_cast<char*>(&sample), sizeof(sample));

    return sample;
}

const TWavReader::THeader& TWavReader::GetHeader() const {
    return header;
}

size_t TWavReader::GetCurrentPosition() {
    return file.tellg();
}

void TWavReader::Seekg(size_t shift) {
    file.seekg(shift);
}

void TWavReader::Seekg(size_t shift, std::ios_base::seekdir dir) {
    file.seekg(shift, dir);
}


TWav::TWav(const std::string& pathFile) {
    file.open(pathFile, std::ios::out);
    file.close();

    file.open(pathFile, std::ios::in | std::ios::out | std::ios::binary);
}

TWav::~TWav() {
    file.close();
}

void TWav::CopyHeader(const TWavReader& otherWav) {
    header = otherWav.GetHeader();
}

void TWav::WriteHeader() {
    file.seekp(0);
    file.write(reinterpret_cast<const char*>(&header), sizeof(header));
}

int16_t TWav::GetSample() {
    int16_t sample;
    file.read(reinterpret_cast<char*>(&sample), sizeof(sample));
    return sample;
}

void TWav::SendSample(const int16_t& sample) {
    file.write(reinterpret_cast<const char*>(&sample), sizeof(sample));
}

const TWav::THeader& TWav::GetHeader() const {
    return header;
}

size_t TWav::GetCurrentPosition() {
    return file.tellp();
}

void TWav::Seekp(size_t shift) {
    file.seekp(shift);
}

void TWav::Seekp(size_t shift, std::ios_base::seekdir dir) {
    file.seekp(shift, dir);
}