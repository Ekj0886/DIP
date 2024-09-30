#include <bits/stdc++.h>
#include "IMAGE.h"

#define F first 
#define S second

using namespace std;

// functions defined in header file

void IMAGE::LoadImage(string file) {
    if(!bmp_image.LoadBMP(file)) cerr << "Failed to load image" << endl;

    W = bmp_image.GetW();
    H = bmp_image.GetH();
    bit = bmp_image.GetBit();

    // load 
    pixel.resize(H, vector<PIXEL>(W));

    // Get raw pixel data from the BMP image (assuming RGB 8-bit per channel)
    vector<uint8_t> raw_data = bmp_image.GetPixel(); 

    // Assuming each pixel is stored as 3 consecutive bytes (R, G, B)
    int index = 0;  // Index in the raw data array
    for (int i = 0; i < H; ++i) {
        for (int j = 0; j < W; ++j) {
            if(bmp_image.GetBit() == 24) {
                // Read RGB values from the raw pixel data
                int B = raw_data[index++];
                int G = raw_data[index++];
                int R = raw_data[index++];
                // Assign the RGB values to the PIXEL struct
                pixel[i][j] = PIXEL(R, G, B, 0);
            }
            else {
                // Read RGB values from the raw pixel data
                int B = raw_data[index++];
                int G = raw_data[index++];
                int R = raw_data[index++];
                int A = raw_data[index++];
                // Assign the RGB values to the PIXEL struct
                pixel[i][j] = PIXEL(R, G, B, A);
            }
        }
    }

    cout << "-- Load Image " << file << endl;

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

void IMAGE::DumpImage(string file) {
    vector<uint8_t> new_pixel;

    if(bmp_image.GetBit() == 24) {
        for(int i = 0; i < H; i++) {
            for(int q = 0; q < W; q++) {
                new_pixel.push_back(uint8_t(pixel[i][q].B));
                new_pixel.push_back(uint8_t(pixel[i][q].G));
                new_pixel.push_back(uint8_t(pixel[i][q].R));
            }
        }
    }
    else {
        for(int i = 0; i < H; i++) {
            for(int q = 0; q < W; q++) {
                new_pixel.push_back(uint8_t(pixel[i][q].B));
                new_pixel.push_back(uint8_t(pixel[i][q].G));
                new_pixel.push_back(uint8_t(pixel[i][q].R));
                new_pixel.push_back(uint8_t(pixel[i][q].A));
            }
        }
    }
    bmp_image.UpdatePixel(new_pixel);
    bmp_image.DumpImageToBMP(file);
    cout << "-- Dump Image " << name << " to " << file << endl;
}

void IMAGE::Flip() {

    for(int i = 0; i < H; i++) {
        for(int q = 0; q < ceil(W/2); q++) {
            PIXEL temp;
            temp = pixel[i][q];
            pixel[i][q] = pixel[i][W-q-1];
            pixel[i][W-q-1] = temp;
        }
    }
    cout << "-- Flip Image " << name << endl;

}