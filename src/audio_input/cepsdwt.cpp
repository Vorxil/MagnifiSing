#include "cepsdwt.h"
#include "aquila/transform/FftFactory.h"
#include <algorithm>
#include <QDebug>

/**
 * @brief cepsDWT::cepsDWT Constructor of a cepsDWT object
 * @param length - length of frame, must be a power of 2
 * @param dwtLevels - number DWT operations to perform
 * @param silenceThreshold - upper RMS threshold for signal considered to be silence
 * @param peakThreshold - magnitude relative to the max peak that the base of the pitch peak must be below
 */

cepsDWT::cepsDWT(int length, int dwtLevels, double silenceThreshold, double peakThreshold) : m_length(length), m_dwtLevels(dwtLevels),
        m_peakThreshold(peakThreshold){

    fftBuffer.reserve(length);
    dwtBuffer.reserve(length);
    fftObj = Aquila::FftFactory::getFft(length);
    m_silenceThreshold = silenceThreshold;
}

cepsDWT::cepsDWT(int length, int dwtLevels, double peakThreshold) : m_length(length), m_dwtLevels(dwtLevels),
        m_peakThreshold(peakThreshold){

    fftBuffer.reserve(length);
    dwtBuffer.reserve(length);
    fftObj = Aquila::FftFactory::getFft(length);
    m_silenceThreshold = 0.005;
}

cepsDWT::~cepsDWT() {}


/**
 * @brief intPow - quick, recursive integer exponential with integer base and exponent
 * @param x - integer base
 * @param p - integer exponent
 * @return integer exponential
 */
int intPow(int x, int p)
{
  if (p == 0) return 1;
  if (p == 1) return x;

  int tmp = intPow(x, p/2);
  if (p%2 == 0) return tmp * tmp;
  else return x * tmp * tmp;
}

/**
 * @brief rms - Returns the root mean square value of a contiguous double array
 * @param src - pointer to first element in double array
 * @param len - length of double array
 * @return root mean square value
 */
double rms(const double* src, int len) {
    double mean = 0;
    double tmp;
    for(int i = 0; i < len; i++) {
        tmp = *(src+i);
        mean += tmp*tmp;
    }
    return std::sqrt(mean/len);
}

double cepsDWT::detectPitchFrequency(const double *src, double fs) {

    //Check silence threshold
    if (rms(src,m_length) <= m_silenceThreshold) return 0;

    //Calculate FFT
    fftBuffer = fftObj->fft(src);

    //Calculate cepstrum
    for(int i=0;i < m_length; i++) {
        dwtBuffer[i] = 20*std::log(std::norm(fftBuffer[i]) + EPSILON);
    }
    fftBuffer = fftObj->fft(dwtBuffer.data());
    for(int i=0;i < m_length; i++) {
        fftBuffer[i] = std::norm(fftBuffer[i])/intPow(m_length,2);
    }

    //Perform discrete Haar wavelet transform on cepstrum data and get the nth level approximation coefficients
    int len = m_length;
    for(int k=1;k <= m_dwtLevels; k++) {
        len = len/2;
        for(int i=0;i < len; i++) {
            if (k > 1) {
                dwtBuffer[i] = (dwtBuffer[2*i] + dwtBuffer[2*i+1])/2;
            } else {
                dwtBuffer[i] = (std::real(fftBuffer[2*i]) + std::real(fftBuffer[2*i+1]))/2;
            }
        }
    }


    int c_max = -1;
    int d_max = -1;
    int a = len/2-1;
    int b = len/2-1;
    int c = len/2-1;
    int k = 1;

    //Determine peak range

    for(int i=0; i < len/2; i++) {
        if (dwtBuffer[i] > c_max) {
            c_max = dwtBuffer[i];
        }
    }

    for(int i=0; i < len/2; i++) {
        if (dwtBuffer[i] <= m_peakThreshold*c_max) {
            a = i;
            break;
        }
    }

    for(int i=a+1; i < len/2; i++) {
        if (dwtBuffer[i] > d_max) {
            d_max = dwtBuffer[i];
            b = i;
        }
    }

    for(int i=b+1; i < len/2; i++) {
        if (dwtBuffer[i] <= m_peakThreshold*d_max) {
            c = i;
            break;
        }
    }

    //Find max peak in peak range
    d_max = -1;
    for(int i=a*intPow(2,m_dwtLevels); i <= c*intPow(2,m_dwtLevels); i++) {
        if (std::real(fftBuffer[i]) > d_max) {
            d_max = std::real(fftBuffer[i]);
            k = i;
        }
    }

    //Return pitch frequency
    return fs/k;

}

void cepsDWT::setSilentThreshold(double threshold){
    m_silenceThreshold = threshold;
}

int cepsDWT::getSilentThreshold(){
    return m_silenceThreshold;
}
