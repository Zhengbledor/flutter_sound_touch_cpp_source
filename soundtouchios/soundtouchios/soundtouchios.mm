//
//  soundtouchios.m
//  soundtouchios
//
//  Created by 郑志豪 on 2023/2/17.
//

#import "soundtouchios.h"

@implementation soundtouchios
long handle = 0;
 
- (instancetype)init{
    handle = soundtouch::newInstance();
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
    soundtouch::setPitchSemiTones(handle,pitch);
}
-(void)setSpeed:(float)speed{
    soundtouch::setSpeed(handle, speed);
}
-(void)setTempo:(float)tempo{
    soundtouch::setTempo(handle, tempo);
}
-(int)processFile:(NSString *)inputFile outputFile:(NSString *)outputFile{
    return soundtouch::processFile(handle, [inputFile UTF8String],[outputFile UTF8String]);
}
@end
