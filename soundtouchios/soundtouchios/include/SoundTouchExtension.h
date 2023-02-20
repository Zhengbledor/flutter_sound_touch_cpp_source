//
//  SoundTouchExtension.h
//  soundtouchios
//
//  Created by 郑志豪 on 2023/2/17.
//

#ifndef SoundTouchExtension_h
#define SoundTouchExtension_h
namespace soundtouch
{
    static const char* getVersionString();
    long newInstance();
    void deleteInstance(long handle);
    void setTempo(long handle, float tempo);
    void setPitchSemiTones(long handle, float pitch);
    void setSpeed(long handle, float speed);
    static const char * getErrorString();
    int processFile(long handle, const char *inputFile, const char *outputFile);
}
#endif /* SoundTouchExtension_h */
