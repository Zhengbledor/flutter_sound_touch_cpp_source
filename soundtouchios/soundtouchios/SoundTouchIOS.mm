//
//  soundtouchios.m
//  soundtouchios
//
//  Created by 郑志豪 on 2023/2/17.
//

#import "SoundTouchIOS.h"
#import "SoundTouchExtension.h"

@implementation SoundTouchIOS
long handle = 0;
 
- (instancetype)init{
    handle = soundtouch::newSoundTouchInstance();
    return self;
}
+(NSString *)getVersionString{
    NSString * versiontString = [[NSString alloc] initWithUTF8String:soundtouch::getVersionString()];
    return versiontString;
}
+(NSString *)getErrorMsg{
    NSString * errorMsg = [[NSString alloc] initWithUTF8String:soundtouch::getErrorString()];
    return errorMsg;
}
-(void)setPitch:(float)pitch{
    soundtouch::setSoundTouchSpeed(handle,pitch);
}
-(void)setSpeed:(float)speed{
    soundtouch::setSoundTouchSpeed(handle, speed);
}
-(void)setTempo:(float)tempo{
    soundtouch::setSoundTouchTempo(handle, tempo);
}
-(int)processFile:(NSString *)inputFile outputFile:(NSString *)outputFile{
    return soundtouch::processSoundTouchFile(handle, [inputFile UTF8String],[outputFile UTF8String]);
}
@end
