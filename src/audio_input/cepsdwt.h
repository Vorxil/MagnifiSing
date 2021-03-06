#ifndef CEPSDWT_H
#define CEPSDWT_H

#include "pitchfreqdetector.h"
#include "aquila/transform/Fft.h"
#include <memory>

#define EPSILON 0.00000001
//#define SILENT_THRESHOLD 30

class cepsDWT : public PitchFreqDetector {
private:
    Aquila::SpectrumType fftBuffer;
    std::vector<double> dwtBuffer;
    const int m_length;
    const int m_dwtLevels;
    double m_silenceThreshold;
    const double m_peakThreshold;
    std::shared_ptr<Aquila::Fft> fftObj;
public:
    cepsDWT(int length, int dwtLevels, double silenceThreshold, double peakThreshold);
    ~cepsDWT();
    double detectPitchFrequency(const double *src, double fs);
    void setSilentThreshold(double threshold);
    double getSilentThreshold();
    cepsDWT(int length, int dwtLevels, double peakThreshold);
};

#endif // CEPSDWT_H
