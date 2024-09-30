#include <bits/stdc++.h>
#include "IMAGE.h"

#define F first 
#define S second

using namespace std;

// functions defined in header file

// void splitBMPData(const std::vector<uint8_t>& pixelData, 
//                   vector<vector<PIXEL>>& pixel,
//                   int width, int height) {
//     // Reserve memory for the channels based on image size
//     size_t pixelCount = width * height;
//     pixel.reserve(pixelCount);

//     // Single pass to populate the channels
//     for (size_t i = 0; i < pixelCount; ++i) {
//         size_t index = i * 3; // Each pixel has 3 bytes (BGR)
//         PIXEL p;
//         p.R = pixelData[index];
//         p.G = pixelData[index + 1];
//         p.B = pixelData[index + 2];
//         // blueChannel.push_back(pixelData[index]);       // Blue
//         // greenChannel.push_back(pixelData[index + 1]); // Green
//         // redChannel.push_back(pixelData[index + 2]);   // Red
//         pixel[].push_back(p);
//     }
// }

void IMAGE::LoadImage(string file) {
    if(bmp_image.LoadBMP(file)) cout << "Image loaded" << endl;
    else cerr << "Failed to load image" << endl;

    W = bmp_image.GetW();
    H = bmp_image.GetH();
    bit = bmp_image.GetBit();

    // load 
    cout << bmp_image.GetPixel().size() << endl;
    pixel.resize(H, vector<PIXEL>(W));

    // Get raw pixel data from the BMP image (assuming RGB 8-bit per channel)
    vector<uint8_t> raw_data = bmp_image.GetPixel(); 

    // Assuming each pixel is stored as 3 consecutive bytes (R, G, B)
    int index = 0;  // Index in the raw data array
    for (int i = 0; i < H; ++i) {
        for (int j = 0; j < W; ++j) {
            // Read RGB values from the raw pixel data
            int R = raw_data[index++];
            int G = raw_data[index++];
            int B = raw_data[index++];

            // Assign the RGB values to the PIXEL struct
            pixel[i][j] = PIXEL(R, G, B);
        }
    }

}

void IMAGE::PrintPixel() {
    
    for(int i = 0; i < H; i++) {
        for(int q = 0; q < W; q++) {
            cout << pixel[i][q].R << " ";
        }cout << endl;
    }
    cout << endl << endl;
    for(int i = 0; i < H; i++) {
        for(int q = 0; q < W; q++) {
            cout << pixel[i][q].G << " ";
        }cout << endl;
    }
    cout << endl << endl;
    for(int i = 0; i < H; i++) {
        for(int q = 0; q < W; q++) {
            cout << pixel[i][q].B << " ";
        }cout << endl;
    }

}

void IMAGE::Flip() {

    

}