#ifndef PITCHPIPELINE_H
#define PITCHPIPELINE_H
#include "lowpassfilter.h"
#include "pitchfreqdetector.h"

class pitchPipeline
{
private:
    int len;
    int factor;
    PitchFreqDetector * detector;
    LowPassFilter * filter;
    double * filterBuffer;
    double * downSampleBuffer;
public:
    pitchPipeline(PitchFreqDetector * detector, LowPassFilter * filter, int frameLength, int downSamplingFactor);
    double detect(const double *frame, const double fs);
    ~pitchPipeline();
};

#endif // PITCHPIPELINE_H
