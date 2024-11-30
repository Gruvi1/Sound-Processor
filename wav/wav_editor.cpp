#include "wav_editor.h"

TWavReader::TWavReader(const std::string& pathFile) {
    file.open(pathFile, std::ios::in | std::ios::binary);

    file.read(reinterpret_cast<char*>(&header.chunkId), sizeof(header.chunkId));
    file.read(reinterpret_cast<char*>(&header.chunkSize), sizeof(header.chunkSize));
    file.read(reinterpret_cast<char*>(&header.format), sizeof(header.format));
    file.read(reinterpret_cast<char*>(&header.subchunk1Id), sizeof(header.subchunk1Id));
    file.read(reinterpret_cast<char*>(&header.subchunk1Size), sizeof(header.subchunk1Size));
    file.read(reinterpret_cast<char*>(&header.audioFormat), sizeof(header.audioFormat));
    file.read(reinterpret_cast<char*>(&header.numChannels), sizeof(header.numChannels));
    file.read(reinterpret_cast<char*>(&header.sampleRate), sizeof(header.sampleRate));
    file.read(reinterpret_cast<char*>(&header.byteRate), sizeof(header.byteRate));
    file.read(reinterpret_cast<char*>(&header.blockAlign), sizeof(header.blockAlign));
    file.read(reinterpret_cast<char*>(&header.bitsPerSample), sizeof(header.bitsPerSample));

    size_t curPosition = file.tellg();
    int count = 0;
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

uint16_t TWavReader::GetSample() {
    uint16_t sample;
    file.read(reinterpret_cast<char*>(&sample), sizeof(sample));
    return sample;
}

const TWavReader::THeader& TWavReader::GetHeader() const {
    return header;
}

size_t TWavReader::GetCurrentInPosition() {
    return file.tellg();
}

void TWavReader::SetInPosition(size_t position) {
    file.seekg(position, std::ios::beg);
}


TWav::TWav(const std::string& pathFile) {
    file.open(pathFile, std::ios::out | std::ios::binary);
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

void TWav::SendSample(const uint16_t& sample) {
    file.write(reinterpret_cast<const char*>(&sample), sizeof(sample));
}

size_t TWav::GetCurrentOutPosition() {
    return file.tellp();
}

// size_t TWav::GetCurrentInPosition() {
//     return file.tellg();
// }

void TWav::SetOutPosition(size_t position) {
    file.seekp(position);
}

// void TWav::SetInPosition(size_t position) {
//     file.seekg(position);
// }