#include <bits/stdc++.h>
#include "IMAGE.h"

#define F first 
#define S second

using namespace std;

// functions defined in header file

void IMAGE::LoadImage(string file) {
    if(!bmp_image.LoadBMP(file) && file != "-h") {
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

    std::cout << "-- Load Image " << file << endl;

}

double IMAGE::Clamp(double d, double low, double high) {
    if(d < low) return low;
    if(d > high) return high;
    return d;
}

void IMAGE::To_YCbCr() {
    for (int i = 0; i < H; i++) {
        for (int j = 0; j < W; j++) {
            double R = static_cast<double>(pixel[i][j].R);
            double G = static_cast<double>(pixel[i][j].G);
            double B = static_cast<double>(pixel[i][j].B);

            // Rec. 601 conversion
            double Y  =  0.299 * R + 0.587 * G + 0.114 * B;
            double Cb = -0.168736 * R - 0.331264 * G + 0.5 * B + 128;
            double Cr =  0.5 * R - 0.418688 * G - 0.081312 * B + 128;
            
            pixel[i][j].Y  = Clamp(Y, 0, 255);
            pixel[i][j].Cb = Clamp(Cb, 0, 255);
            pixel[i][j].Cr = Clamp(Cr, 0, 255);
        }
    }
}

void IMAGE::To_RGB() {
    for (int i = 0; i < H; i++) {
        for (int j = 0; j < W; j++) {

            pixel[i][j].Y  = Clamp(pixel[i][j].Y, 0, 255);
            double Y  = static_cast<double>(pixel[i][j].Y);
            double Cb = static_cast<double>(pixel[i][j].Cb) - 128;
            double Cr = static_cast<double>(pixel[i][j].Cr) - 128;

            // Convert YCbCr back to RGB with precise coefficients
            int R = static_cast<int>(Y + 1.402 * Cr);
            int G = static_cast<int>(Y - 0.344136 * Cb - 0.714136 * Cr);
            int B = static_cast<int>(Y + 1.772 * Cb);

            // Clamp and assign back to the pixel
            pixel[i][j].R = static_cast<uint8_t>(std::min(255, std::max(0, R)));
            pixel[i][j].G = static_cast<uint8_t>(std::min(255, std::max(0, G)));
            pixel[i][j].B = static_cast<uint8_t>(std::min(255, std::max(0, B)));
        }
    }
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
    std::cout << "-- Dump Image " << name << " to " << file << endl;
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
    std::cout << "-- Flip Image " << name << endl;

}

void IMAGE::Resolution(int ResBit) {

    if(ResBit != 2 && ResBit != 4 && ResBit != 6) {
        std::cout << "-- Wrong Resolution Bit num, cancel cropping" << endl;
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
    std::cout << "-- Resolution " << ResBit << " " << name << endl; 

}

void IMAGE::Crop(int x, int y, int w, int h) {

    if(x < 0 || x > W || y < 0 || y > H) {
        std::cout << "-- Crop failed: Coordinates out of bound" << endl;
        return;
    } 

    if(w < 0 || h < 0 || x+w > W || y+h > H) {
        std::cout << "-- Crop failed: Region out of bound" << endl;
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

double sigmoid(double x, double alpha, double beta) {
    return 1 / (1 + exp(-alpha * (x - beta)));
}

void IMAGE::IncreaseLuma() {
    To_YCbCr();
    for(int i = 0; i < H; i++) {
        for(int j = 0; j < W; j++) {
            pixel[i][j].Y += 35 * (255-pixel[i][j].Y)/255;
        }
    }
    To_RGB();
}