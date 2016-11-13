#ifndef PITCHFREQDETECTOR_H
#define PITCHFREQDETECTOR_H

class PitchFreqDetector
{  
public:
    virtual double detectPitchFrequency(const double* src, double fs) = 0;
};

#endif // PITCHFREQDETECTOR_H
