#include "lowpassfilter.h"
#include <cstring>
#include <stdexcept>


LowPassFilter::LowPassFilter(double const * _filterConsts, const int _filterLength, const int _dataLength) : filterLength(_filterLength), dataLength(_dataLength) {
    filterConsts = _filterConsts;
    oldData = new double[filterLength-1+dataLength]();
}

LowPassFilter::~LowPassFilter() {
    delete[] oldData;
}

void LowPassFilter::filter(double const * input, double * output) {

    //Put everything into one array
    memcpy(oldData+filterLength-1,input,dataLength*sizeof(double));

    //Filter
    for(int i=0;i < dataLength;i++) {
        for(int j=0; j < filterLength; j++) {
            output[i] += input[i+filterLength-1-j]*filterConsts[j];
        }
    }

    //Copy last N-1 data points to the beginning of the array, for a filter of length N
    memcpy(oldData, input+dataLength-(filterLength-1), (filterLength-1)*sizeof(double));

    return;

}

void LowPassFilter::downsample(const double *input, double *output, int dataLen, int downsampleFactor)
{
    if (downsampleFactor < 2) {
        throw std::invalid_argument("Downsampling factor is not greater than 1!");
    }
    else if (dataLen%downsampleFactor != 0) {
        throw std::invalid_argument("Data length is not a multiple of downsampling factor!");
    }

    for(int k = 0; downsampleFactor*k < dataLen; k++) {
        output[k] = input[downsampleFactor*k];
    }
}
