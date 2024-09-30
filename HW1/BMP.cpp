#include <bits/stdc++.h>
#include "BMP.h"

#define F first 
#define S second

using namespace std;

// functions defined in header file

bool BMP::LoadBMP(string filePath) {
    cout << filePath << endl;
    std::ifstream file(filePath, std::ios::binary);
    if (!file) {
        std::cerr << "Error opening file: " << filePath << std::endl;
        return false;
    }

    // Read BMP File Header
    file.read(reinterpret_cast<char*>(&fileheader), sizeof(BMPFileHeader));

    // Check if the file is a valid BMP file
    if (fileheader.fileType != 0x4D42) {  // 'BM' in little-endian
        std::cerr << "Not a valid BMP file!" << std::endl;
        return false;
    }

    // Read DIB Header (BMP Info Header)
    file.read(reinterpret_cast<char*>(&infoheader), sizeof(BMPInfoHeader));

    // Check if the BMP is 24-bit uncompressed
    if (infoheader.bitsPerPixel != 24) {
        std::cerr << "Only 24-bit BMP files are supported." << std::endl;
        return false;
    }

    // Move to the pixel data in the file
    file.seekg(fileheader.dataOffset, std::ios::beg);

    // Calculate the size of the pixel data (each row is padded to a multiple of 4 bytes)
    size_t rowSize = (infoheader.width * 3 + 3) & ~3;  // Align row to the next multiple of 4 bytes
    size_t dataSize = rowSize * abs(infoheader.height);  // Total size of the pixel data

    // Read the pixel data
    BMP_pixel.resize(dataSize);
    file.read(reinterpret_cast<char*>(BMP_pixel.data()), dataSize);

    file.close();
    return true;
}