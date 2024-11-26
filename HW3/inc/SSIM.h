#ifndef SSIM_H
#define SSIM_H
#include <bits/stdc++.h>
#include "IMAGE.h"

#define F first 
#define S second

using namespace std;

// Helper function to compute mean for a 2D patch using Y
double computeMean(const std::vector<std::vector<PIXEL>>& pixels, int x, int y, int patchSize) {
    double sum = 0.0;
    int count = 0;
    for (int j = 0; j < patchSize; ++j) {
        for (int i = 0; i < patchSize; ++i) {
            sum += pixels[y + j][x + i].Y; // Use Y component
            count++;
        }
    }
    return sum / count;
}

// Helper function to compute variance for a 2D patch using Y
double computeVariance(const std::vector<std::vector<PIXEL>>& pixels, int x, int y, int patchSize, double mean) {
    double sum = 0.0;
    int count = 0;
    for (int j = 0; j < patchSize; ++j) {
        for (int i = 0; i < patchSize; ++i) {
            double value = pixels[y + j][x + i].Y; // Use Y component
            sum += (value - mean) * (value - mean);
            count++;
        }
    }
    return sum / count;
}

// Helper function to compute covariance between two 2D patches using Y
double computeCovariance(const std::vector<std::vector<PIXEL>>& img1, const std::vector<std::vector<PIXEL>>& img2, 
                         int x, int y, int patchSize, double mean1, double mean2) {
    double sum = 0.0;
    int count = 0;
    for (int j = 0; j < patchSize; ++j) {
        for (int i = 0; i < patchSize; ++i) {
            double value1 = img1[y + j][x + i].Y; // Use Y component
            double value2 = img2[y + j][x + i].Y; // Use Y component
            sum += (value1 - mean1) * (value2 - mean2);
            count++;
        }
    }
    return sum / count;
}

// SSIM calculation using Y channel for a single patch
double calculateSSIMForY(const std::vector<std::vector<PIXEL>>& img1, const std::vector<std::vector<PIXEL>>& img2, 
                         int x, int y, int patchSize) {
    double C1 = 6.5025, C2 = 58.5225;

    double mean1 = computeMean(img1, x, y, patchSize);
    double mean2 = computeMean(img2, x, y, patchSize);

    double variance1 = computeVariance(img1, x, y, patchSize, mean1);
    double variance2 = computeVariance(img2, x, y, patchSize, mean2);

    double covariance = computeCovariance(img1, img2, x, y, patchSize, mean1, mean2);

    return ((2 * mean1 * mean2 + C1) * (2 * covariance + C2)) /
           ((mean1 * mean1 + mean2 * mean2 + C1) * (variance1 + variance2 + C2));
}

#endif