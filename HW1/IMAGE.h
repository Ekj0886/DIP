#ifndef IMAGE_H
#define IMAGE_H
#include <bits/stdc++.h>
#include "BMP.h"

#define F first 
#define S second

using namespace std;

class IMAGE {

private:
    BMP bmp_image;
    int W;
    int H;
    int bit;
    vector<uint8_t> pixel[3];
    
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