#include <bits/stdc++.h>
#include <getopt.h> 
#include "IMAGE.h"

#define F first 
#define S second

using namespace std;

int main(int argc, char *argv[]) {

    if(argc < 2) {
        cerr << "missing input or output file" << endl;
        return 0;
    }    

    string input_file  = argv[argc - 2];
    string output_file = argv[argc - 1]; 
    IMAGE* image = new IMAGE(input_file);
    IMAGE* OriginImage;

    static struct option long_options[] = {
        {"originimage", required_argument, nullptr, 'o'},
        {"luminosity",  required_argument, nullptr, 'l'},
        {"flip",        no_argument,       nullptr, 'f'},
        {"resolution",  required_argument, nullptr, 'r'},
        {"crop",        no_argument,       nullptr, 'c'},
        {"sharpness",   required_argument, nullptr, 's'},
        {"median",      required_argument, nullptr, 'm'},
        {"evaluate",    no_argument,       nullptr, 'e'},
        {"gaussian",    required_argument, nullptr, 'g'},
        {nullptr,       0,                 nullptr,  0 } 
    };

    int opt;
    while ((opt = getopt_long(argc, argv, "o:fr:cl:s:m:eg:", long_options, nullptr)) != -1) {
        switch (opt) {
            case 'o':
                OriginImage = new IMAGE(optarg);
                break;
            case 'f':
                image->Flip();
                break;
            case 'r':
                image->Resolution( atoi(optarg) );
                break; 
            case 'c':
                cout << "-- Crop Image " << input_file << endl;
                cout << "   Enter < x y w h > in order: ";
                int x, y, w, h;
                cin >> x >> y >> w >> h;
                image->Crop(x, y, w, h);
                break;
            case 'l':
                cout << "-- improve luminosity " << input_file << endl;
                image->EnhanceLuma(atof(optarg));
                break;
            case 's':
                cout << "-- improve sharpness " << input_file << endl;
                image->EnhanceSharpness(atoi(optarg));
                break;
            case 'm':
                cout << "-- Apply Median filter " << input_file << endl;
                image->MedianFilter(atoi(optarg));
                break;
            case 'e':
                image->SSIM(OriginImage);
                break;
            case 'g':
                if(atoi(optarg)) image->GaussianRGB(6, 0.8);
                else             image->GaussianBlur(6, 0.8);
                break;
            default:
                break;
        }
    }

    // image->To_Gray();
    image->DumpImage(output_file);

    return 0;

}