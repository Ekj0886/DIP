#include <bits/stdc++.h>
#include "IMAGE.h"

#define F first 
#define S second

using namespace std;

int main(int argc, char *argv[]) {

    ifstream infile (argv[1]);
    // ofstream outfile(argv[2]);

    string file_name;
    infile >> file_name;

    IMAGE image(file_name);
    
    return 0;

}