#ifndef LOWPASSFILTER_H
#define LOWPASSFILTER_H

/**
 * @brief The LowPassFilter class is a generic FIR lowpass filter of odd length using a direct implementation, with an additional static downsampling function.
 */
class LowPassFilter
{
protected:
    double const * filterConsts;
    double * oldData;
    const int filterLength, dataLength;
public:

    /**
     * @brief LowPassFilter - Constructor
     * @param _filterConsts - The filter constants for a FIR filter
     * @param _filterLength - Length of the filter, should be odd
     * @param _dataLength - Length of the data that is being filtered, should be greater than filter length.
     */
    LowPassFilter(double const * _filterConsts, const int _filterLength, const int _dataLength);

    ~LowPassFilter();

    /**
     * @brief filter - filters the input and puts the result into output
     * @param input
     * @param output
     */
    void filter(double const * input, double * output);

    /**
     * @brief downsample - downsample the current data window by the downsampleFactor
     * @param input
     * @param output
     * @param dataLen - length of the data window
     * @param downsampleFactor - factor to downsample, needs to be a multiple of dataLen
     */
    static void downsample(double const * input, double * output, int dataLen, int downsampleFactor);
};

#endif // LOWPASSFILTER_H
