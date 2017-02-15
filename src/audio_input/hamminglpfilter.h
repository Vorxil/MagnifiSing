#ifndef HAMMINGLPFILTER_H
#define HAMMINGLPFILTER_H
#include "lowpassfilter.h"

/**
 * @brief The HammingLPFilter class is a symmetric Hamming lowpass filter of odd length. Inherits LowPassFilter functionality.
 */
class HammingLPFilter : public LowPassFilter
{
public:
    /**
     * @brief generateFilter - generates filter constants
     * @param samplingFreq - The sampling frequency of the data in Hz
     * @param passband - The passband of the data in Hz i.e. frequencies above this value will be attenuated
     * @param transBand - The length of transitional band in Hz i.e. the transition from passband to stopband
     * @return the filter constants
     */
    static double * generateFilter(const double samplingFreq, const double passband, const double transBand);

    /**
     * @brief filterLen - Calculates the optimal filter length for the filter
     * @param samplingFreq - Sampling frequency of the data in Hz
     * @param transBand - Length of the transitional band i.e. the transition from passband to stopband
     * @return - the optimal filter length
     */
    inline static int filterLen(const double samplingFreq, const double transBand);

    /**
     * @brief HammingLPFilter - constructor of the filter
     * @param samplingFreq - Sampling frequency of the data in Hz
     * @param passband - The passband of the data in Hz i.e. frequencies above this value will be attenuated
     * @param transBand - The length of transitional band in Hz i.e. the transition from passband to stopband
     * @param _dataLength - The length of the data window
     */
    HammingLPFilter(const double samplingFreq, const double passband, const double transBand, const int _dataLength);
    ~HammingLPFilter();
};

#endif // HAMMINGFILTER_H
