//
//  SoundTouchExtension.cpp
//  soundtouchios
//
//  Created by 郑志豪 on 2023/2/17.
//
#include <stdexcept>
#include <string>

using namespace std;

#include "../include/SoundTouch.h"
#include "SoundStretch/WavFile.h"
#include "../include/SoundTouchExtension.h"
#include "../include/SoundTouchExtension.h"

// String for keeping possible c++ exception error messages. Notice that this isn't
// thread-safe but it's expected that exceptions are special situations that won't
// occur in several threads in parallel.

#define DLL_PUBLIC __attribute__ ((visibility ("default")))
#define BUFF_SIZE 4096


using namespace soundtouch;

static string _errMsg = "";

// Set error message to return
static void _setErrmsg(const char *msg)
{
    _errMsg = msg;
}


// Processes the sound file
static void _processFile(SoundTouch *pSoundTouch, const char *inFileName, const char *outFileName)
{
    int nSamples;
    int nChannels;
    int buffSizeSamples;
    SAMPLETYPE sampleBuffer[BUFF_SIZE];

    // open input file
    WavInFile inFile(inFileName);
    int sampleRate = inFile.getSampleRate();
    int bits = inFile.getNumBits();
    nChannels = inFile.getNumChannels();

    // create output file
    WavOutFile outFile(outFileName, sampleRate, bits, nChannels);

    pSoundTouch->setSampleRate(sampleRate);
    pSoundTouch->setChannels(nChannels);

    assert(nChannels > 0);
    buffSizeSamples = BUFF_SIZE / nChannels;

    // Process samples read from the input file
    while (inFile.eof() == 0)
    {
        int num;

        // Read a chunk of samples from the input file
        num = inFile.read(sampleBuffer, BUFF_SIZE);
        nSamples = num / nChannels;

        // Feed the samples into SoundTouch processor
        pSoundTouch->putSamples(sampleBuffer, nSamples);

        // Read ready samples from SoundTouch processor & write them output file.
        // NOTES:
        // - 'receiveSamples' doesn't necessarily return any samples at all
        //   during some rounds!
        // - On the other hand, during some round 'receiveSamples' may have more
        //   ready samples than would fit into 'sampleBuffer', and for this reason
        //   the 'receiveSamples' call is iterated for as many times as it
        //   outputs samples.
        do
        {
            nSamples = pSoundTouch->receiveSamples(sampleBuffer, buffSizeSamples);
            outFile.write(sampleBuffer, nSamples * nChannels);
        } while (nSamples != 0);
    }

    // Now the input file is processed, yet 'flush' few last samples that are
    // hiding in the SoundTouch's internal processing pipeline.
    pSoundTouch->flush();
    do
    {
        nSamples = pSoundTouch->receiveSamples(sampleBuffer, buffSizeSamples);
        outFile.write(sampleBuffer, nSamples * nChannels);
    } while (nSamples != 0);
}



static const char* getVersionString()
{
    const char *verStr;
    verStr = SoundTouch::getVersionString();
    return verStr;
}



long newInstance()
{
    return (long)(new SoundTouch());
}


void deleteInstance(long handle)
{
    SoundTouch *ptr = (SoundTouch*)handle;
    delete ptr;
}


void setTempo(long handle, float tempo)
{
    SoundTouch *ptr = (SoundTouch*)handle;
    ptr->setTempo(tempo);
}


void setPitchSemiTones(long handle, float pitch)
{
    SoundTouch *ptr = (SoundTouch*)handle;
    ptr->setPitchSemiTones(pitch);
}


void setSpeed(long handle, float speed)
{
    SoundTouch *ptr = (SoundTouch*)handle;
    ptr->setRate(speed);
}


static const char * getErrorString()
{
    return _errMsg.c_str();
}


int processFile(long handle, const char *inputFile, const char *outputFile)
{
    SoundTouch *ptr = (SoundTouch*)handle;
    try
    {
        _processFile(ptr, inputFile, outputFile);
    }
    catch (const runtime_error &e)
    {
        const char *err = e.what();
        _setErrmsg(err);
        return -1;
    }
    return 0;
}
