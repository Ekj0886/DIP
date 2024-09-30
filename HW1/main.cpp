#include <bits/stdc++.h>
#include "IMAGE.h"

#define F first 
#define S second

using namespace std;

int main(int argc, char *argv[]) {

    // ifstream infile (argv[1]);
    // ofstream outfile(argv[2]);

    string file_name = argv[1];

    IMAGE* image = new IMAGE(file_name);
    image->Flip();
    image->Resolution(4);
    image->DumpImage("output.bmp");

    return 0;

}