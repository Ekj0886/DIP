#include <bits/stdc++.h>
#include "BMP.h"

#define F first 
#define S second

using namespace std;

// functions defined in header file

bool BMP::LoadBMP(string filePath) {

    std::ifstream file(filePath, std::ios::binary);
    if (!file) {
        std::cerr << "Error opening file: " << filePath << std::endl;
        return false;
    }

    // Read BMP File Header
    file.read(reinterpret_cast<char*>(&fileheader), sizeof(BMPFileHeader));

    // Check if the file is a valid BMP file
    if (fileheader.fileType != 0x4D42) {  // 'BM' in little-endian
        std::cerr << "Not a valid BMP file" << std::endl;
        return false;
    }

    // Read DIB Header (BMP Info Header)
    file.read(reinterpret_cast<char*>(&infoheader), sizeof(BMPInfoHeader));

    // Check if the BMP is 24-bit uncompressed
    if (infoheader.bitsPerPixel != 24 && infoheader.bitsPerPixel != 32) {
        std::cerr << "Only 24-bit/32-bit BMP files are supported." << std::endl;
        return false;
    }

    // Move to the pixel data in the file
    file.seekg(fileheader.dataOffset, std::ios::beg);

    // Calculate the size of the pixel data (each row is padded to a multiple of 4 bytes)
    size_t bytesPerPixel = infoheader.bitsPerPixel / 8; // 3 for 24-bit, 4 for 32-bit
    size_t rowSize = (infoheader.width * bytesPerPixel + 3) & ~3;  // Align row to the next multiple of 4 bytes
    size_t dataSize = rowSize * abs(infoheader.height);  // Total size of the pixel data

    // Read the pixel data
    BMP_pixel.resize(dataSize);
    file.read(reinterpret_cast<char*>(BMP_pixel.data()), dataSize);

    file.close();
    return true;
}


bool BMP::DumpImageToBMP(const string& file_name) {
    ofstream bmp_file(file_name, ios::binary);
    if (!bmp_file) {
        cerr << "Error: Could not open file for writing: " << file_name << endl;
        return false;
    }
    // Calculate padding for each row (BMP rows are padded to 4-byte boundaries)
    int row_padding = (4 - (infoheader.width * (infoheader.bitsPerPixel / 8)) % 4) % 4;
    // Update file size: file header (14 bytes) + info header (40 bytes) + pixel data (including padding)
    fileheader.fileSize = 14 + 40 + (infoheader.width * 3 + row_padding) * abs(infoheader.height);
    // Set data offset (after the headers)
    fileheader.dataOffset = 14 + 40;
    // Set BMP info header properties
    infoheader.headerSize = 40;  // Size of the DIB header
    infoheader.planes = 1;       // Must be 1
    infoheader.compression = 0;  // No compression
    infoheader.imageSize = (infoheader.width * 3 + row_padding) * abs(infoheader.height); // Pixel data size
    // 1. Write BMP file header (14 bytes)
    bmp_file.write(reinterpret_cast<const char*>(&fileheader), sizeof(fileheader));
    // 2. Write DIB header (40 bytes)
    bmp_file.write(reinterpret_cast<const char*>(&infoheader), sizeof(infoheader));
    // 3. Write pixel data in BGR format
    // Loop through each row, remembering BMP stores pixels from bottom to top
    switch(infoheader.bitsPerPixel) {

        case(24):
            for (int y = 0; y < abs(infoheader.height); ++y) {
                for (int x = 0; x < infoheader.width; ++x) {
                    // BMP stores pixels as BGR, so write in reverse order
                    bmp_file.put(BMP_pixel[(y * infoheader.width + x) * 3 + 0]);  // Blue
                    bmp_file.put(BMP_pixel[(y * infoheader.width + x) * 3 + 1]);  // Green
                    bmp_file.put(BMP_pixel[(y * infoheader.width + x) * 3 + 2]);  // Red
                }
                // Write padding for this row
                bmp_file.write("\0\0\0", row_padding);
            }
            break;

        case(32):
            for (int y = 0; y < abs(infoheader.height); ++y) {
                for (int x = 0; x < infoheader.width; ++x) {
                    // BMP stores pixels as BGR, so write in reverse order
                    bmp_file.put(BMP_pixel[(y * infoheader.width + x) * 4 + 0]);  // Blue
                    bmp_file.put(BMP_pixel[(y * infoheader.width + x) * 4 + 1]);  // Green
                    bmp_file.put(BMP_pixel[(y * infoheader.width + x) * 4 + 2]);  // Red
                    bmp_file.put(BMP_pixel[(y * infoheader.width + x) * 4 + 3]);  // Alpha
                }
                // Write padding for this row
                bmp_file.write("\0\0\0\0", row_padding);
            }
            break;

    };

        
    

    // Close the file
    bmp_file.close();
    // cout << "Image dumped to BMP format: " << file_name << endl;
    return true;
}