#ifndef IMAGE_H
#define IMAGE_H
#include <bits/stdc++.h>
#include "BMP.h"

#define F first 
#define S second

using namespace std;

struct PIXEL {
    int R, G, B;
    PIXEL(int r = 0, int g = 0, int b = 0) : R(r), G(g), B(b) {}
};

class IMAGE {

private:
    BMP bmp_image;
    int W;
    int H;
    int bit;
    vector<vector<PIXEL>> pixel;
    
public:
    IMAGE() {};
    IMAGE(string file) { LoadImage(file); }
    void LoadImage(string);
    int GetW() { return W; }    
    int GetH() { return H; }
    int GetBit() { return bit; }
    void PrintPixel();
    void Flip();

};

#endif