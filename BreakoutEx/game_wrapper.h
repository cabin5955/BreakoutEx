//
//  game_wrapper.h
//  BreakOutES
//
//  Created by chen caibin on 2021/10/29.
//

#include "glad.h"
#include <UIKit/UIKit.h>

@interface GameWrapper : NSObject
- (void)InitWidth:(GLfloat) width Height:(GLfloat) height;
- (void)KeyboardInputWhithKey:(int) key Pressed:(char)pressed;
- (void)TouchMoveOffsetX:(double)x OffsetY:(double)y;
- (void)TouchBegan;
- (void)TouchEnded;
- (void)Update:(GLfloat)dt;
- (void)Render;
- (void)Realease;
@end

