#ifndef CEPSDWT_H
#define CEPSDWT_H

#include "pitchfreqdetector.h"
#include "aquila/transform/Fft.h"
#include <memory>

#define EPSILON 0.00000001
#define SILENT_THRESHOLD 0.1

class cepsDWT : PitchFreqDetector {
private:
    Aquila::SpectrumType fftBuffer;
    std::vector<double> dwtBuffer;
    const int m_length;
    const int m_dwtLevels;
    std::shared_ptr<Aquila::Fft> fftObj;
public:
    cepsDWT(int length, int dwtLevels);
    ~cepsDWT();
    double detectPitchFrequency(const double *src, double fs);
};

#endif // CEPSDWT_H
