#include <bits/stdc++.h>
#include "IMAGE.h"

#define F first 
#define S second

using namespace std;

// functions defined in header file

void splitBMPData(const std::vector<uint8_t>& pixelData, 
                  std::vector<uint8_t>& redChannel, 
                  std::vector<uint8_t>& greenChannel, 
                  std::vector<uint8_t>& blueChannel, 
                  int width, int height) {
    // Reserve memory for the channels based on image size
    size_t pixelCount = width * height;
    redChannel.reserve(pixelCount);
    greenChannel.reserve(pixelCount);
    blueChannel.reserve(pixelCount);

    // Single pass to populate the channels
    for (size_t i = 0; i < pixelCount; ++i) {
        size_t index = i * 3; // Each pixel has 3 bytes (BGR)
        blueChannel.push_back(pixelData[index]);       // Blue
        greenChannel.push_back(pixelData[index + 1]); // Green
        redChannel.push_back(pixelData[index + 2]);   // Red
    }
}

void IMAGE::LoadImage(string file) {
    if(bmp_image.LoadBMP(file)) cout << "Image loaded" << endl;
    else cerr << "Failed to load image" << endl;

    W = bmp_image.GetW();
    H = bmp_image.GetH();
    bit = bmp_image.GetBit();

    // load 
    cout << bmp_image.GetPixel().size() << endl;
    splitBMPData(bmp_image.GetPixel(), pixel[0], pixel[1], pixel[2], W, H);

}

void IMAGE::PrintPixel() {
    // for(auto p : pixel) cout << int(p) << " ";
    // cout << endl;
    cout << pixel[0].size() << endl;
}

void IMAGE::Flip() {

}