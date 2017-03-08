#include "mainwindow.h"
#include <QApplication>
#include <QStyle>
#include <QDesktopWidget>
#include "singingviewcontroller.h"
#include "singingview.h"


#include "audio_input/hamminglpfilter.h"
#include "audio_input/pitchpipeline.h"
#include <fstream>
#include <iostream>
#include <vector>
#include <ctime>
#include "audio_input/cepsdwt.h"


int main(int argc, char *argv[])
{

    const double passband = 2000;
    const double transband = 500;
    const double fs = 48000;
    const int downFactor = 8;
    const int dwtLevels = 3;
    const double silence = 0.005;
    const double peak = 0.05;

    std::fstream io;
    std::string filename("C:/Users/Robert/Desktop/test/olli.dat");
    std::string output("C:/Users/Robert/Desktop/test/filtered.dat");
    std::string downs("C:/Users/Robert/Desktop/test/downs.dat");
    std::string pitches("C:/Users/Robert/Desktop/test/pitch.dat");
    std::vector<double> raw;
    std::vector<double> filtered;
    std::vector<double> downSampled;
    std::vector<double> freq;

    clock_t t1,t2;

    std::cout << "Opening file " << filename << std::endl;

    io.open(filename.c_str(), std::fstream::in);

    if (!io.is_open()){
        std::cerr << "Error opening file " << filename << std::endl;
        return 1;
    }

    std::cout << "Fetching data" << std::endl;

    double data = 0.0;

    while (io >> data) {
        raw.push_back(data);
    }

    io.close();

    std::cout << "Closing file " << filename << std::endl;

    std::cout << "Number of data points: " << raw.size() << std::endl;

    std::cout << "Setting up frames" << std::endl;

    long size = raw.size();

    long frameLength=1;
    while (fs > frameLength*6) {
        frameLength *= 2;
    }
    long frames = size/frameLength;

    std::cout << "Number of frames: " << frames << std::endl;
    std::cout << "Framelength: " << frameLength << std::endl;

    while (frameLength*frames != raw.size()) {
        raw.push_back(0.0);
        size++;
    }

    std::cout << "Generating filter" << std::endl;



    std::cout << "Filter length " << HammingLPFilter::filterLen(fs,transband) << std::endl;



    std::cout << "Filtering..." << std::endl;

    /*long long sum = 0;

    for(int frame = 0; frame < frames ; frame++) {
        t1 = clock();
        filter.filter(raw.data()+frame*frameLength, filtered.data() + frame*frameLength);
        t2 = clock();
        sum = (t2-t1);
    }

    std::cout << "Filtering done" << std::endl;
    std::cout << "Average time per frame taken: " << (1000.0*sum)/(frames*CLOCKS_PER_SEC) << " ms" << std::endl;

    std::cout << "Opening file " << output << std::endl;

    io.open(output.c_str(), std::fstream::out | std::fstream::trunc);

    if (!io.is_open()){
        std::cerr << "Error opening file " << output << std::endl;
        return 1;
    }

    std::cout << "Writing to file " << output << std::endl;

    for(int i=0;i < size;i++) {
        io << filtered[i] << std::endl;
    }

    io.close();

    std::cout << "Closing file " << output << std::endl;

    cepsDWT pitch(frameLength/downFactor,dwtLevels,silence,peak);

    freq.reserve(frames);
    downSampled.reserve(size/downFactor);

    std::cout << "Downsampling..." << std::endl;
    for(int frame = 0; frame < frames ; frame++) {
        filter.downsample(filtered.data()+frame*frameLength,downSampled.data() + frame*frameLength/downFactor,frameLength,downFactor);
        std::cout << "Downsampling frame " << frame << " complete" << std::endl;
    }

    std::cout << "Opening file " << downs << std::endl;

    io.open(downs.c_str(), std::fstream::out | std::fstream::trunc);

    if (!io.is_open()){
        std::cerr << "Error opening file " << downs << std::endl;
        return 1;
    }

    std::cout << "Writing to file " << downs << " " << size/downFactor << " elements" << std::endl;

    for(int i=0;i < size/downFactor ;i++) {
        io << downSampled[i] << std::endl;
    }

    io.close();

    std::cout << "Closing file " << downs << std::endl; */

    //HammingLPFilter filter(fs,passband,transband,frameLength);
    //cepsDWT pitch(frameLength/downFactor,dwtLevels,silence,peak);

    HammingLPFilter filter(48000,2000,500,8192);
    cepsDWT pitch(1024,3,0.005,0.05);

    filtered.reserve(frameLength);
    //filtered.reserve(size);
    downSampled.reserve(frameLength/downFactor);
    //downSampled.reserve(size/downFactor);

    pitchPipeline pipe(&pitch,&filter,frameLength,downFactor);
    double frequency;
    std::cout << "Calculating pitch frequencies..." << std::endl;
    for(int frame = 0; frame < frames ; frame++) {
        frequency = pipe.detect(raw.data()+frame*frameLength,fs);
        freq.push_back(frequency);
        std::cout << "Frame pitch " << freq[frame] << " Hz" << std::endl;
        std::cout << "Frame " << frame << " complete" << std::endl;
    }

    std::cout << "Calculating done" << std::endl;



    std::cout << "Opening file " << pitches << std::endl;

    io.open(pitches.c_str(), std::fstream::out | std::fstream::trunc);

    if (!io.is_open()){
        std::cerr << "Error opening file " << pitches << std::endl;
        return 1;
    }

    std::cout << "Writing to file " << pitches << std::endl;

    for(int i=0;i < frames;i++) {
        io << freq[i] << std::endl;
    }

    io.close();

    std::cout << "Closing file " << pitches << std::endl;

    return 0;


    /*QApplication a(argc, argv);
    MainWindow w;
    SingingViewController* singingViewController = new SingingViewController(w.getSingingView(), w.getStartSingingView());

    w.setWindowTitle("MagnifiSing");

    w.show();

    a.exit(0);
    return a.exec();*/

}
