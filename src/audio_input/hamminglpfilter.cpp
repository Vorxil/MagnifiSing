#include "hamminglpfilter.h"
#include <cmath>
#define pi 3.1415926535897

HammingLPFilter::HammingLPFilter(const float samplingFreq, const float passband, const float transBand, const int _dataLength)
    : LowPassFilter(HammingLPFilter::generateFilter(samplingFreq, passband, transBand), HammingLPFilter::filterLen(samplingFreq,transBand), _dataLength){}

HammingLPFilter::~HammingLPFilter() {
    delete[] oldData;
    delete[] filterConsts;
}

inline int HammingLPFilter::filterLen(const float samplingFreq, const float transBand) {
    return static_cast<int>(ceil(3.3*samplingFreq/transBand) + 1 - fmod(ceil(3.3*samplingFreq/transBand), 2));
}

float * HammingLPFilter::generateFilter(const float samplingFreq, const float passband, const float transBand) {
    int len = filterLen(samplingFreq, transBand);
    float * f = new float[len];
    float fc = (passband + transBand/2)/samplingFreq;
    float x;
    for(int i = 0; i < len; i++) {
        x = 2*pi*fc*(i - (len-1)/2);
        f[i] = 2*fc*((i == (len-1)/2)? 1 : sin(x)/x)*(0.54 + 0.46*cos(2*pi*(i - (len-1)/2)/len));
    }

    return f;
}
