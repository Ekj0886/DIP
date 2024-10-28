#ifndef IMAGE_H
#define IMAGE_H
#include <bits/stdc++.h>
#include "BMP.h"

#define F first 
#define S second

using namespace std;

struct PIXEL {
    uint8_t R, G, B, A;
    double Y, Cb, Cr;
    PIXEL(uint8_t r = 0, uint8_t g = 0, uint8_t b = 0, uint8_t a = 0) : R(r), G(g), B(b), A(a) {}
};

class IMAGE {

private:
    string name;
    BMP bmp_image;
    vector<vector<PIXEL>> pixel;
    int W;
    int H;
    int bit;
    
public:
    // constructor
    IMAGE() {};
    IMAGE(string file) { LoadImage(file); name = file;}
    
    // member function
    void LoadImage(string);
    int  GetW() { return W; }    
    int  GetH() { return H; }
    int  GetBit() { return bit; }
    double Clamp(double, double, double);
    void To_YCbCr();
    void To_RGB();
    void DumpImage(string);

    // Add new function here
    void Flip();
    void Resolution(int ResBit);
    void Crop(int x, int y, int w, int h);
    void IncreaseLuma();

};

#endif