#include <bits/stdc++.h>
#include "IMAGE.h"
#include "SSIM.h"

#define F first 
#define S second

using namespace std;

// functions defined in header file

void IMAGE::LoadImage(string file) {
    if(!bmp_image.LoadBMP(file) && file != "-h") {
        cerr << "Failed to load image" << endl;
        exit(0);
    }

    W = bmp_image.GetW();
    H = bmp_image.GetH();
    bit = bmp_image.GetBit();

    // load 
    pixel.resize(H, vector<PIXEL>(W));

    // Get raw pixel data from the BMP image (assuming RGB 8-bit per channel)
    vector<uint8_t> raw_data = bmp_image.GetPixel(); 

    // Assuming each pixel is stored as 3 consecutive bytes (R, G, B)
    int index = 0;  // Index in the raw data array
    for (int i = 0; i < H; ++i) {
        for (int j = 0; j < W; ++j) {
            if(bit == 24) {
                // Read RGB values from the raw pixel data
                uint8_t B = raw_data[index++];
                uint8_t G = raw_data[index++];
                uint8_t R = raw_data[index++];
                // Assign the RGB values to the PIXEL struct
                pixel[i][j] = PIXEL(R, G, B, 0);
            }
            else {
                // Read RGB values from the raw pixel data
                uint8_t B = raw_data[index++];
                uint8_t G = raw_data[index++];
                uint8_t R = raw_data[index++];
                uint8_t A = raw_data[index++];
                // Assign the RGB values to the PIXEL struct
                pixel[i][j] = PIXEL(R, G, B, A);
            }
        }
    }

    std::cout << "-- Load Image " << file << endl;

}

double IMAGE::Clamp(double d, double low, double high) {
    if(d < low) return low;
    if(d > high) return high;
    return d;
}

void IMAGE::To_YCbCr() {
    for (int i = 0; i < H; i++) {
        for (int j = 0; j < W; j++) {
            double R = static_cast<double>(pixel[i][j].R);
            double G = static_cast<double>(pixel[i][j].G);
            double B = static_cast<double>(pixel[i][j].B);

            // Rec. 601 conversion
            double Y  =  0.299 * R + 0.587 * G + 0.114 * B;
            double Cb = -0.168736 * R - 0.331264 * G + 0.5 * B + 128;
            double Cr =  0.5 * R - 0.418688 * G - 0.081312 * B + 128;
            
            pixel[i][j].Y  = Clamp(Y, 0, 255);
            pixel[i][j].Cb = Clamp(Cb, 0, 255);
            pixel[i][j].Cr = Clamp(Cr, 0, 255);
        }
    }
}

void IMAGE::To_RGB() {
    for (int i = 0; i < H; i++) {
        for (int j = 0; j < W; j++) {

            pixel[i][j].Y  = Clamp(pixel[i][j].Y, 0, 255);
            double Y  = static_cast<double>(pixel[i][j].Y);
            double Cb = static_cast<double>(pixel[i][j].Cb) - 128;
            double Cr = static_cast<double>(pixel[i][j].Cr) - 128;

            // Convert YCbCr back to RGB with precise coefficients
            int R = static_cast<int>(Y + 1.402 * Cr);
            int G = static_cast<int>(Y - 0.344136 * Cb - 0.714136 * Cr);
            int B = static_cast<int>(Y + 1.772 * Cb);

            // Clamp and assign back to the pixel
            pixel[i][j].R = static_cast<uint8_t>(std::min(255, std::max(0, R)));
            pixel[i][j].G = static_cast<uint8_t>(std::min(255, std::max(0, G)));
            pixel[i][j].B = static_cast<uint8_t>(std::min(255, std::max(0, B)));
        }
    }
}

void IMAGE::To_Gray() {
    for (int i = 0; i < H; i++) {
        for (int j = 0; j < W; j++) {

            pixel[i][j].Y  = Clamp(pixel[i][j].Y, 0, 255);
            double Y  = static_cast<double>(pixel[i][j].Y);
            double Cb = 0;
            double Cr = 0;

            // Convert YCbCr back to RGB with precise coefficients
            int R = static_cast<int>(Y + 1.402 * Cr);
            int G = static_cast<int>(Y - 0.344136 * Cb - 0.714136 * Cr);
            int B = static_cast<int>(Y + 1.772 * Cb);

            // Clamp and assign back to the pixel
            pixel[i][j].R = static_cast<uint8_t>(std::min(255, std::max(0, R)));
            pixel[i][j].G = static_cast<uint8_t>(std::min(255, std::max(0, G)));
            pixel[i][j].B = static_cast<uint8_t>(std::min(255, std::max(0, B)));
        }
    }
}



void IMAGE::DumpImage(string file) {

    bmp_image.UpdateWH(W, H);

    vector<uint8_t> new_pixel;
    if(bit == 24) {
        for(int i = 0; i < H; i++) {
            for(int q = 0; q < W; q++) {
                new_pixel.push_back(uint8_t(pixel[i][q].B));
                new_pixel.push_back(uint8_t(pixel[i][q].G));
                new_pixel.push_back(uint8_t(pixel[i][q].R));
            }
        }
    }
    else {
        for(int i = 0; i < H; i++) {
            for(int q = 0; q < W; q++) {
                new_pixel.push_back(uint8_t(pixel[i][q].B));
                new_pixel.push_back(uint8_t(pixel[i][q].G));
                new_pixel.push_back(uint8_t(pixel[i][q].R));
                new_pixel.push_back(uint8_t(pixel[i][q].A));
            }
        }
    }
    bmp_image.UpdatePixel(new_pixel);
    bmp_image.DumpImageToBMP(file);
    std::cout << "-- Dump Image " << name << " to " << file << endl;
}

void IMAGE::Flip() {

    for(int i = 0; i < H; i++) {
        for(int q = 0; q < ceil(W/2); q++) {
            PIXEL temp;
            temp = pixel[i][q];
            pixel[i][q] = pixel[i][W-q-1];
            pixel[i][W-q-1] = temp;
        }
    }
    std::cout << "-- Flip Image " << name << endl;

}

void IMAGE::Resolution(int ResBit) {

    if(ResBit != 2 && ResBit != 4 && ResBit != 6) {
        std::cout << "-- Wrong Resolution Bit num, cancel cropping" << endl;
        return;
    }

    uint8_t mask;
    switch(ResBit) {
        case(2): mask = 0b11000000; break;
        case(4): mask = 0b11110000; break;
        case(6): mask = 0b11111100; break;
    };

    for(int i = 0; i < H; i++) {
        for(int q = 0; q < W; q++) {
            pixel[i][q].R = pixel[i][q].R & mask;
            pixel[i][q].G = pixel[i][q].G & mask;
            pixel[i][q].B = pixel[i][q].B & mask;
        }
    }
    std::cout << "-- Resolution " << ResBit << " " << name << endl; 

}

void IMAGE::Crop(int x, int y, int w, int h) {

    if(x < 0 || x > W || y < 0 || y > H) {
        std::cout << "-- Crop failed: Coordinates out of bound" << endl;
        return;
    } 

    if(w < 0 || h < 0 || x+w > W || y+h > H) {
        std::cout << "-- Crop failed: Region out of bound" << endl;
        return;
    }


    W = w;
    H = h;

    vector<vector<PIXEL>> new_pixel(H, vector<PIXEL>(W));
    for(int i = 0; i < h; i++) {
        for(int q = 0; q < w; q++) {

            new_pixel[i][q] = pixel[y+i][x+q];

        }
    }

    pixel = new_pixel;

}

double sigmoid(double x, double alpha, double beta) {
    return 1 / (1 + exp(-alpha * (x - beta)));
}


void IMAGE::GaussianBlur(int k, double sigma) {

    // Generate 1D Gaussian kernel
    vector<double> kernel(k); 
    k /= 2;
    double total = 0;
    for(int i = -k; i <= k; i++) {
        kernel[i+k] = exp(-1 * (i * i) / (2 * sigma * sigma) );
        total += kernel[i+k];
    }

    for(auto& kernel_value : kernel) {
        kernel_value /= total;
    }

    // Perform horizontal convolution 
    for(int i = 0; i < H; i++) {
        for(int j = 0; j < W; j++) {
            
            double Xconv = 0;
            double Xsum = 0; 
            for(int r = -k; r <= k; r++) {
                int x = r + j;
                int y = i;

                if(x < 0 || y < 0 || x >= W || y >= H) continue; // zero padding
                
                Xconv += pixel[y][x].Y * kernel[r + k];
                Xsum += kernel[r + k];
            }

            pixel[i][j].Y = Xconv / Xsum;
            pixel[i][j].Y  = Clamp(pixel[i][j].Y, 0, 255);
        }
    }

    // Perform vertical convolution 
    for(int i = 0; i < H; i++) {
        for(int j = 0; j < W; j++) {
            
            double Yconv = 0;
            double Ysum = 0;
            for(int r = -k; r <= k; r++) {
                int x = j;
                int y = r + i;

                if(x < 0 || y < 0 || x >= W || y >= H) continue; // zero padding
                
                Yconv += pixel[y][x].Y * kernel[r + k];
                Ysum += kernel[r + k];
            }

            pixel[i][j].Y = Yconv / Ysum;
            pixel[i][j].Y  = Clamp(pixel[i][j].Y, 0, 255);
        }
    }

    To_RGB();
}

void IMAGE::GaussianRGB(int k, double sigma) {
    // Generate 1D Gaussian kernel
    vector<double> kernel(k); 
    k /= 2;
    double total = 0;
    for (int i = -k; i <= k; i++) {
        kernel[i + k] = exp(-1 * (i * i) / (2 * sigma * sigma));
        total += kernel[i + k];
    }
    for (auto& kernel_value : kernel) {
        kernel_value /= total;
    }

    // Perform horizontal convolution on R, G, and B channels
    for (int i = 0; i < H; i++) {
        for (int j = 0; j < W; j++) {
            double Rconv = 0, Gconv = 0, Bconv = 0;
            double Xsum = 0;

            for (int r = -k; r <= k; r++) {
                int x = r + j;
                int y = i;

                if (x < 0 || x >= W || y < 0 || y >= H) continue; // zero padding

                Rconv += pixel[y][x].R * kernel[r + k];
                Gconv += pixel[y][x].G * kernel[r + k];
                Bconv += pixel[y][x].B * kernel[r + k];
                Xsum += kernel[r + k];
            }

            pixel[i][j].R = Clamp(Rconv / Xsum, 0, 255);
            pixel[i][j].G = Clamp(Gconv / Xsum, 0, 255);
            pixel[i][j].B = Clamp(Bconv / Xsum, 0, 255);
        }
    }

    // Perform vertical convolution on R, G, and B channels
    for (int i = 0; i < H; i++) {
        for (int j = 0; j < W; j++) {
            double Rconv = 0, Gconv = 0, Bconv = 0;
            double Ysum = 0;

            for (int r = -k; r <= k; r++) {
                int x = j;
                int y = r + i;

                if (x < 0 || x >= W || y < 0 || y >= H) continue; // zero padding

                Rconv += pixel[y][x].R * kernel[r + k];
                Gconv += pixel[y][x].G * kernel[r + k];
                Bconv += pixel[y][x].B * kernel[r + k];
                Ysum += kernel[r + k];
            }

            pixel[i][j].R = Clamp(Rconv / Ysum, 0, 255);
            pixel[i][j].G = Clamp(Gconv / Ysum, 0, 255);
            pixel[i][j].B = Clamp(Bconv / Ysum, 0, 255);
        }
    }
    To_YCbCr();
}


void IMAGE::EnhanceLuma(double gamma) {
    To_YCbCr();
    for(int i = 0; i < H; i++) {
        for(int j = 0; j < W; j++) {
            pixel[i][j].Y = Clamp( 255 * pow(pixel[i][j].Y / 255, gamma), 0, 255 );
        }
    }
    To_RGB();
}

void IMAGE::EnhanceSharpness(int level) {
    IMAGE LPF_Image = *this;
    LPF_Image.GaussianBlur(13, 1);
    for(int i = 0; i < H; i++) {
        for(int j = 0; j < W; j++) {
            pixel[i][j].Y += level * (pixel[i][j].Y - LPF_Image.pixel[i][j].Y);
            // pixel[i][j].Y = (3*level)*(pixel[i][j].Y - LPF_Image.pixel[i][j].Y);
        }
    }
    To_RGB();
}

bool comp (const PIXEL &a, const PIXEL &b) {
    return a.Y < b.Y;    // ascending order
    // return a.value > b.value; // descending order
}


void IMAGE::MedianFilter(int k_size) {

    int r = k_size / 2;
    for(int i = 0; i < H; i++) {
        for(int j = 0; j < W; j++) {

            vector<PIXEL> kernel;
            for(int y = -r; y <= r; y++) {
                for(int x = -r; x <= r; x++) {
                    int Y = i + y;
                    int X = j + x;
                    if(Y >= 0 && X >= 0 && Y < H && X < W) { 
                        kernel.push_back(pixel[Y][X]);
                    }
                }
            }
            sort(kernel.begin(), kernel.end(), comp);
            PIXEL med = kernel[kernel.size() / 2];

            pixel[i][j] = med;
        }
    }
    To_RGB();
}

// Main SSIM calculation over the whole image using Y channel
void IMAGE::SSIM(IMAGE* origin_image) {
    std::vector<std::vector<PIXEL>> origin = origin_image->GetPixel();

    int patchSize = 11;
    int numPatches = 0;
    double ssimSum = 0.0;

    // Slide the window over the image
    for (int y = 0; y <= H - patchSize; y += patchSize) {
        for (int x = 0; x <= W - patchSize; x += patchSize) {
            // Calculate SSIM for Y channel and sum up
            ssimSum += calculateSSIMForY(pixel, origin, x, y, patchSize);
            ++numPatches;
        }
    }

    // Average SSIM for Y channel
    double ssimY = ssimSum / numPatches;

    // Output SSIM score
    std::cout << "-- SSIM Score (Y channel): " << ssimY << std::endl;
}

void IMAGE::ShadesGrey(int n) {


    int thres = 210;    
    double Y_norm = 0, R_norm = 0, G_norm = 0, B_norm = 0;
    for(int i = 0; i < H; i++) {
        for(int j = 0; j < W; j++) {
            int R = pixel[i][j].R;
            int G = pixel[i][j].G;
            int B = pixel[i][j].B;
            if(R < thres && G < thres && B < thres) {
                R_norm += pow(pixel[i][j].R, n);
                G_norm += pow(pixel[i][j].G, n);
                B_norm += pow(pixel[i][j].B, n);
            }
        }
    }
    
    R_norm = pow(R_norm, 1.0/n);
    G_norm = pow(G_norm, 1.0/n);
    B_norm = pow(B_norm, 1.0/n);
    Y_norm = (R_norm + B_norm + G_norm) / 3.0;

    for(int i = 0; i < H; i++) {
        for(int j = 0; j < W; j++) {
            pixel[i][j].R = Clamp((pixel[i][j].R * Y_norm ) / R_norm, 0, 255);
            pixel[i][j].G = Clamp((pixel[i][j].G * Y_norm ) / G_norm, 0, 255);
            pixel[i][j].B = Clamp((pixel[i][j].B * Y_norm ) / B_norm, 0, 255);
        }
    }
    
}

void IMAGE::Saturation(float factor) {
    To_YCbCr();
    for(int i = 0; i < H; i++) {
        for(int j = 0; j < W; j++) {
            pixel[i][j].Cb = Clamp( (pixel[i][j].Cb - 128)*factor + 128, 0, 255 ); 
            pixel[i][j].Cr = Clamp( (pixel[i][j].Cr - 128)*factor + 128, 0, 255 ); 
        }
    }
    To_RGB();
}

void IMAGE::MaxRGB() {

    int R_max = 0, G_max = 0, B_max = 0, max_ave;
    
    for(int i = 0; i < H; i++) {
        for(int j = 0; j < W; j++) {
            R_max = max((int)pixel[i][j].R, R_max);
            G_max = max((int)pixel[i][j].G, G_max);
            B_max = max((int)pixel[i][j].B, B_max);
        }
    }
    
    max_ave = (R_max + G_max + B_max) / 3;

    for(int i = 0; i < H; i++) {
        for(int j = 0; j < W; j++) {
            pixel[i][j].R = Clamp( pixel[i][j].R * max_ave / R_max, 0, 255 );
            pixel[i][j].G = Clamp( pixel[i][j].G * max_ave / G_max, 0, 255 );
            pixel[i][j].B = Clamp( pixel[i][j].B * max_ave / B_max, 0, 255 );
        }
    }

}

void IMAGE::EqualizeHistogram() {
    
    To_YCbCr();
    
    vector<int> Histogram(256, 0);
    vector<int> CDF(256, 0);
    vector<int> Equal(256, 0);

    // compute Histogram
    for(int i = 0; i < H; i++) {
        for(int j = 0; j < W; j++) {
            Histogram[pixel[i][j].Y]++;
        }
    }

    // compute & normalize CDF
    CDF[0] = Histogram[0];
    for(int i = 1; i < 256; i++) {
        CDF[i] += CDF[i-1] + Histogram[i];
    }

    int CDF_min = *min_element(CDF.begin(), CDF.end());
    for(int i = 0; i < 256; i++) {
        Equal[i] = round( (double)(CDF[i] - CDF_min) / (H*W - CDF_min) * 255 );
    }

    // Apply on Y channel
    for(int i = 0; i < H; i++) {
        for(int j = 0; j < W; j++) {
            pixel[i][j].Y = Equal[pixel[i][j].Y];
        }
    }

    To_RGB();
    
}

void IMAGE::Warm() {
    for(int i = 0; i < H; i++) {
        for(int j = 0; j < W; j++) {
            pixel[i][j].R = Clamp((pixel[i][j].R * 1.2 ), 0, 255);
            pixel[i][j].G = Clamp((pixel[i][j].G * 1.05 ), 0, 255);
            pixel[i][j].B = Clamp((pixel[i][j].B * 0.8 ), 0, 255);
        }
    }
}

void IMAGE::Cold() {
    for(int i = 0; i < H; i++) {
        for(int j = 0; j < W; j++) {
            pixel[i][j].R = Clamp((pixel[i][j].R * 0.8 ), 0, 255);
            pixel[i][j].G = Clamp((pixel[i][j].G * 1.05 ), 0, 255);
            pixel[i][j].B = Clamp((pixel[i][j].B * 1.2 ), 0, 255);
        }
    }
}