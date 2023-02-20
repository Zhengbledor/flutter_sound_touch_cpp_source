//
//  SoundTouchExtension.h
//  soundtouchios
//
//  Created by 郑志豪 on 2023/2/17.    
//

#ifndef SoundTouchExtension_h
#define SoundTouchExtension_h
#include <stdexcept>
#include <string>
using namespace::std;
#import "SoundTouch.h"
#include "../source/SoundStretch/WavFile.h"
#define DLL_PUBLIC __attribute__ ((visibility ("default")))
#define BUFF_SIZE 4096
namespace soundtouch
{

    static string _errMsg;

    static void _setErrmsg(const char *msg)
    {
        _errMsg = msg;
    }

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

    static const char* getVersionString(){
        const char *verStr;
        verStr = SoundTouch::getVersionString();
        return verStr;
    }

    static const char * getErrorString(){
        return _errMsg.c_str();
    }

    static long newSoundTouchInstance(){
        return (long)(new SoundTouch());
    }

    static void deleteSoundTouchInstance(long handle){
        SoundTouch *ptr = (SoundTouch*)handle;
        delete ptr;
    }

    static void setSoundTouchTempo(long handle, float tempo){
        SoundTouch *ptr = (SoundTouch*)handle;
        ptr->setTempo(tempo);
    }

    static void setSoundTouchPitchSemiTones(long handle, float pitch){
        SoundTouch *ptr = (SoundTouch*)handle;
        ptr->setPitchSemiTones(pitch);
    }

    static void setSoundTouchSpeed(long handle, float speed){
        SoundTouch *ptr = (SoundTouch*)handle;
        ptr->setRate(speed);
    }

    static int processSoundTouchFile(long handle, const char *inputFile, const char *outputFile){
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
}
#endif /* SoundTouchExtension_h */
