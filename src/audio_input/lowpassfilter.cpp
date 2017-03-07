#include "lowpassfilter.h"
#include <cstring>
#include <stdexcept>


LowPassFilter::LowPassFilter(float const * _filterConsts, const int _filterLength, const int _dataLength) : filterLength(_filterLength), dataLength(_dataLength) {
    filterConsts = _filterConsts;
    oldData = new float[filterLength]();
}

LowPassFilter::~LowPassFilter() {
    delete[] oldData;
}

void LowPassFilter::filter(float const * input, float * output) {

    //Filter input that use old data
    for(int i=0;i < filterLength-1;i++) {
        //Old data first
        for(int j=i+1; j < filterLength; j++) {
            output[i] += oldData[filterLength-2-(i+1)-j]*filterConsts[j];
        }
        //Then new data
        for(int j=0; j <= i; j++) {
            output[i] += input[i-j]*filterConsts[j];
        }
    }

    //Filter input that only use current data
    for(int i=filterLength-1;i < dataLength;i++) {
        for(int j=0; j < filterLength; j++) {
            output[i] += input[i-j]*filterConsts[j];
        }
    }

    //Copy new data to old data
    memcpy(oldData, input+dataLength-(filterLength-1), (filterLength-1)*sizeof(float));

    return;

}

void LowPassFilter::downsample(const float *input, float *output, int dataLen, int downsampleFactor)
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
