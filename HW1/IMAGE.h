#ifndef IMAGE_H
#define IMAGE_H
#include <bits/stdc++.h>
#include "BMP.h"

#define F first 
#define S second

using namespace std;

struct PIXEL {
    int R, G, B, A;
    PIXEL(int r = 0, int g = 0, int b = 0, int a = 0) : R(r), G(g), B(b), A(a) {}
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
    int GetW() { return W; }    
    int GetH() { return H; }
    int GetBit() { return bit; }
    void DumpImage(string);
    void Flip();

    void PrintPixel();

};

#endif