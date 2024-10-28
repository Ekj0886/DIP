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

    static struct option long_options[] = {
        {"luminosity",  no_argument,       nullptr, 'l'},
        {"flip",        no_argument,       nullptr, 'f'},
        {"resolution",  required_argument, nullptr, 'r'},
        {"crop",        no_argument,       nullptr, 'c'},
        {nullptr,       0,                 nullptr,  0 } 
    };

    int opt;
    while ((opt = getopt_long(argc, argv, "fr:cl", long_options, nullptr)) != -1) {
        switch (opt) {
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
                image->IncreaseLuma();
                break;
            default:
                break;
        }
    }

    image->DumpImage(output_file);

    return 0;

}