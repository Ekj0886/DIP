#include <bits/stdc++.h>
#include "IMAGE.h"

#define F first 
#define S second

using namespace std;

// functions defined in header file

void IMAGE::LoadImage(string file) {

    if(LoadBMP(file, fileheader, infoheader, pixel)) cout << "Image loaded" << endl;
    else cerr << "Failed to load image" << endl;

}