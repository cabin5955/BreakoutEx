//
//  game_wrapper.m
//  BreakOutES
//
//  Created by chen caibin on 2021/10/29.
//

#import <Foundation/Foundation.h>
#include "game_wrapper.h"
#include "game.hpp"
#include <string.h>

@interface GameWrapper (){
    Game *game;
    NSString *preferPath;
}
@end

@implementation GameWrapper

- (void)InitWidth:(GLfloat) width Height:(GLfloat) height{
    
    preferPath = [NSString stringWithFormat:@"%@/",[[NSBundle mainBundle] bundlePath]];
    const char* fileName = [preferPath cStringUsingEncoding:1];
    game = new Game(width,height);
    strcpy(game->preferPath, fileName);
    game->Init();
}

- (void)ProcessInput:(GLfloat) dt{
    game->ProcessInput(dt);
}

- (void)Update:(GLfloat)dt{
    game->Update(dt);
}

- (void)Render{
    game->Render();
}

@end
