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
#include "glfm.h"

@interface GameWrapper (){
    Game *game;
    NSString *preferPath;
}
@end

bool IsDoubleClick ()
{
    static double LastClickTicks = 0;
    double CurrentClickTicks;

    /* First time this function is called, LastClickTicks
    has not been initialised yet. */
    if (LastClickTicks == 0)
    {
        LastClickTicks = glfmGetTime ();
        return false;
    }
    else
    {
        CurrentClickTicks = glfmGetTime ();

        /* If the period between the two clicks is smaller
        or equal to a pre-defined number, we report a
        DoubleClick event. */
        double sub = CurrentClickTicks - LastClickTicks;
        if ( sub <= 0.4f)
        {
            /* Update LastClickTicks and signal a DoubleClick. */

            LastClickTicks = CurrentClickTicks;
            return true;
        }

        /* Update LastClickTicks and signal a SingleClick. */

        LastClickTicks = CurrentClickTicks;
        return false;
    }
}

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

- (void)KeyboardInputWhithKey:(int) key Pressed:(char)pressed{
    
}

- (void)TouchBegan{
    
    if(IsDoubleClick())
    {
        game->DoubleClickShoot();
    }
}

- (void)TouchEnded{
    
}

- (void)TouchMoveOffsetX:(double)x OffsetY:(double)y
{
    game->MouseMotionOffset(x, y);
}

- (void)Update:(GLfloat)dt{
    game->Update(dt);
}

- (void)Render{
    game->Render();
}
- (void)Realease
{
    
}

@end
