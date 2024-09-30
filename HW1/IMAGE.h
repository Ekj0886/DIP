#ifndef IMAGE_H
#define IMAGE_H
#include <bits/stdc++.h>
#include "BMP.h"

#define F first 
#define S second

using namespace std;

class IMAGE {

private:
    BMPFileHeader fileheader;
    BMPInfoHeader infoheader;
    vector<uint8_t> pixel;
    
public:

    IMAGE() {};
    IMAGE(string file) { LoadImage(file); }
    void LoadImage(string);
    int GetW() { return infoheader.width; }    
    int GetH() { return infoheader.height; }
    int GetBit() { return infoheader.bitsPerPixel; }
    void PrintPixel();
    void Flip();

};

#endif