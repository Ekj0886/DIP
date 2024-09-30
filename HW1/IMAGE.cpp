#include <bits/stdc++.h>
#include "IMAGE.h"

#define F first 
#define S second

using namespace std;

// functions defined in header file

void IMAGE::LoadImage(string file) {
    if(!bmp_image.LoadBMP(file)) {
        cerr << "Failed to load image" << endl;
        exit(0);
    }

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
            if(bit == 24) {
                // Read RGB values from the raw pixel data
                uint8_t B = raw_data[index++];
                uint8_t G = raw_data[index++];
                uint8_t R = raw_data[index++];
                // Assign the RGB values to the PIXEL struct
                pixel[i][j] = PIXEL(R, G, B, 0);
            }
            else {
                // Read RGB values from the raw pixel data
                uint8_t B = raw_data[index++];
                uint8_t G = raw_data[index++];
                uint8_t R = raw_data[index++];
                uint8_t A = raw_data[index++];
                // Assign the RGB values to the PIXEL struct
                pixel[i][j] = PIXEL(R, G, B, A);
            }
        }
    }

    cout << "-- Load Image " << file << endl;

}

void IMAGE::DumpImage(string file) {

    bmp_image.UpdateWH(W, H);

    vector<uint8_t> new_pixel;
    if(bit == 24) {
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

void IMAGE::Resolution(int ResBit) {

    if(ResBit != 2 && ResBit != 4 && ResBit != 6) {
        cout << "-- Wrong Resolution Bit num, cancel cropping" << endl;
        return;
    }

    uint8_t mask;
    switch(ResBit) {
        case(2): mask = 0b11000000; break;
        case(4): mask = 0b11110000; break;
        case(6): mask = 0b11111100; break;
    };

    for(int i = 0; i < H; i++) {
        for(int q = 0; q < W; q++) {
            pixel[i][q].R = pixel[i][q].R & mask;
            pixel[i][q].G = pixel[i][q].G & mask;
            pixel[i][q].B = pixel[i][q].B & mask;
        }
    }

}

void IMAGE::Crop(int x, int y, int w, int h) {

    if(x < 0 || x > W || y < 0 || y > H) {
        cout << "-- Crop failed: Coordinates out of bound" << endl;
        return;
    } 

    if(w < 0 || h < 0 || x+w > W || y+h > H) {
        cout << "-- Crop failed: Region out of bound" << endl;
        return;
    }


    W = w;
    H = h;

    vector<vector<PIXEL>> new_pixel(H, vector<PIXEL>(W));
    for(int i = 0; i < h; i++) {
        for(int q = 0; q < w; q++) {

            new_pixel[i][q] = pixel[y+i][x+q];

        }
    }

    pixel = new_pixel;

}