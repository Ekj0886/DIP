// BMP.h
#ifndef BMP_H
#define BMP_H

#include <bits/stdc++.h>

using namespace std;

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

class BMP {

private:
    BMPFileHeader fileheader;
    BMPInfoHeader infoheader;
    vector<uint8_t> BMP_pixel;

public:
    bool LoadBMP(string filePath);
    void UpdateWH(int w, int h) { infoheader.width = w; infoheader.height = h; }
    void UpdatePixel(vector<uint8_t>& new_pixel) { BMP_pixel = new_pixel; }
    bool DumpImageToBMP(const string& file_name);
    int GetW() { return infoheader.width; }    
    int GetH() { return infoheader.height; }
    int GetBit() { return infoheader.bitsPerPixel; }
    vector<uint8_t> GetPixel() { return BMP_pixel; }

};

#endif
