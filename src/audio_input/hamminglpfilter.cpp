#include "hamminglpfilter.h"
#define pi 3.1415926535897

HammingLPFilter::HammingLPFilter(const double samplingFreq, const double passband, const double transBand, const int _dataLength)
    : LowPassFilter(HammingLPFilter::generateFilter(samplingFreq, passband, transBand), HammingLPFilter::filterLen(samplingFreq,transBand), _dataLength){}

HammingLPFilter::~HammingLPFilter() {
    delete[] oldData;
    delete[] filterConsts;
}

double * HammingLPFilter::generateFilter(const double samplingFreq, const double passband, const double transBand) {
    int len = filterLen(samplingFreq, transBand);
    double * f = new double[len];
    double fc = (passband + transBand/2)/samplingFreq;
    double x;
    for(int i = 0; i < len; i++) {
        x = 2*pi*fc*(i - (len-1)/2);
        f[i] = 2*fc*((i == (len-1)/2)? 1 : sin(x)/x)*(0.54 + 0.46*cos(2*pi*(i - (len-1)/2)/len));
    }

    return f;
}
