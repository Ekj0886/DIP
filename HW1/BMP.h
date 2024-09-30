// BMP.h
#ifndef BMP_H
#define BMP_H

#include <iostream>
#include <fstream>
#include <vector>

#pragma pack(push, 1)  // Disable padding to match BMP file structure

// BMP File Header (14 bytes)
struct BMPFileHeader { 
    uint16_t fileType   { 0x4D42 };  // File type, always "BM"
    uint32_t fileSize   { 0 };       // Size of the file in bytes
    uint16_t reserved1  { 0 };       // Reserved, must be 0
    uint16_t reserved2  { 0 };       // Reserved, must be 0
    uint32_t dataOffset { 0 };       // Offset to the start of pixel data
};

// DIB Header (40 bytes for BITMAPINFOHEADER)
struct BMPInfoHeader {
    uint32_t headerSize      { 0 };  // Size of this header (40 bytes)
    int32_t  width           { 0 };  // Width of the image
    int32_t  height          { 0 };  // Height of the image
    uint16_t planes          { 1 };  // Number of color planes (must be 1)
    uint16_t bitsPerPixel    { 0 };  // Bits per pixel (e.g., 24 for RGB)
    uint32_t compression     { 0 };  // Compression method (0 for no compression)
    uint32_t imageSize       { 0 };  // Size of the raw bitmap data
    int32_t  xPixelsPerMeter { 0 };  // Horizontal resolution
    int32_t  yPixelsPerMeter { 0 };  // Vertical resolution
    uint32_t colorsUsed      { 0 };  // Number of colors in the palette
    uint32_t importantColors { 0 };  // Important colors (0 if all are important)
};

#pragma pack(pop)  // Restore default padding


// Function for loading a BMP file

bool LoadBMP(const std::string& filePath, BMPFileHeader& fileHeader, BMPInfoHeader& infoHeader, std::vector<uint8_t>& pixelData) {
    std::ifstream file(filePath, std::ios::binary);
    if (!file) {
        std::cerr << "Error opening file: " << filePath << std::endl;
        return false;
    }

    // Read BMP File Header
    file.read(reinterpret_cast<char*>(&fileHeader), sizeof(BMPFileHeader));

    // Check if the file is a valid BMP file
    if (fileHeader.fileType != 0x4D42) {  // 'BM' in little-endian
        std::cerr << "Not a valid BMP file!" << std::endl;
        return false;
    }

    // Read DIB Header (BMP Info Header)
    file.read(reinterpret_cast<char*>(&infoHeader), sizeof(BMPInfoHeader));

    // Check if the BMP is 24-bit uncompressed
    if (infoHeader.bitsPerPixel != 24) {
        std::cerr << "Only 24-bit BMP files are supported." << std::endl;
        return false;
    }

    // Move to the pixel data in the file
    file.seekg(fileHeader.dataOffset, std::ios::beg);

    // Calculate the size of the pixel data (each row is padded to a multiple of 4 bytes)
    size_t rowSize = (infoHeader.width * 3 + 3) & ~3;  // Align row to the next multiple of 4 bytes
    size_t dataSize = rowSize * abs(infoHeader.height);  // Total size of the pixel data

    // Read the pixel data
    pixelData.resize(dataSize);
    file.read(reinterpret_cast<char*>(pixelData.data()), dataSize);

    file.close();
    return true;
}

#endif
