//
//  game_wrapper.h
//  BreakOutES
//
//  Created by chen caibin on 2021/10/29.
//

#include "gles.h"

@interface GameWrapper : NSObject
- (void)InitWidth:(GLfloat) width Height:(GLfloat) height;
- (void)ProcessInput:(GLfloat) dt;
- (void)Update:(GLfloat)dt;
- (void)Render;
@end

