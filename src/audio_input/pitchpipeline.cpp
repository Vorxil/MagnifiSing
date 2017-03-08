#include "pitchpipeline.h"

pitchPipeline::pitchPipeline(PitchFreqDetector * detector, LowPassFilter * filter, int frameLength, int downSamplingFactor)
{
    this->len = frameLength;
    this->factor = downSamplingFactor;
    this->detector = detector;
    this->filter = filter;
    this->filterBuffer = new double[frameLength];
    this->downSampleBuffer = new double[frameLength/downSamplingFactor];
}

double pitchPipeline::detect(const double *frame, const double fs)
{
    filter->filter(frame,filterBuffer);
    filter->downsample(filterBuffer, downSampleBuffer, len, factor);
    return detector->detectPitchFrequency(downSampleBuffer, fs/factor);
}

pitchPipeline::~pitchPipeline()
{
    delete filterBuffer;
    delete downSampleBuffer;
}
