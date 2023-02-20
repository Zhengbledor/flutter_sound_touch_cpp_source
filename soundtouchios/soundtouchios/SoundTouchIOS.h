//
//  soundtouchios.h
//  soundtouchios
//
//  Created by 郑志豪 on 2023/2/17.
//

#import <Foundation/Foundation.h>

@interface SoundTouchIOS : NSObject
+(NSString *)getVersionString;
+(NSString *)getErrorMsg;
-(void)setPitch:(float)pitch;
-(void)setSpeed:(float)speed;
-(void)setTempo:(float)tempo;
-(int)processFile:(NSString *)inputFile outputFile:(NSString *)outputFile;
@end
