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
#include "director.hpp"
#include "game_start.hpp"
#include "touch_dispatcher.hpp"
#include "game_over.hpp"
#include "game_pause.hpp"
#include "color_renderer.hpp"

@interface GameWrapper (){
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

extern ColorRenderer       *colorRenderer;

@implementation GameWrapper

- (void)InitWidth:(GLfloat) width Height:(GLfloat) height{
    
    preferPath = [NSString stringWithFormat:@"%@/",[[NSBundle mainBundle] bundlePath]];
    const char* fileName = [preferPath cStringUsingEncoding:1];
    
    strcpy(GameStart::GetInstance()->preferPath, fileName);
    GameStart::GetInstance()->Init(width,height);
    
    strcpy(GameOver::GetInstance()->preferPath, fileName);
    GameOver::GetInstance()->Init(width,height);
    
    strcpy(Game::GetInstance()->preferPath, fileName);
    Game::GetInstance()->Init(width,height);
    
    strcpy(GamePause::GetInstance()->preferPath, fileName);
    GamePause::GetInstance()->Init(width,height);
    
    Director::GetInstance()->SetRootScene(GameStart::GetInstance());
}

- (void)ProcessInput:(GLfloat) dt{
    
}

- (void)KeyboardInputWhithKey:(int) key Pressed:(char)pressed{
    Director::GetInstance()->GetTopScene()->KeyboardInput(key,pressed);
}

- (void)TouchBeganPosX:(double)x PosY:(double)y{
    if (Game::GetInstance()->State == GAME_ACTIVE && IsDoubleClick())
    {
        Game::GetInstance()->DoubleClickShoot();
    }
    TouchDispatcher *dispatcher = TouchDispatcher::get_instance();
    dispatcher->touchesBegan(x, y);
}

- (void)TouchEndedPos:(double)x PosY:(double)y{
    TouchDispatcher *dispatcher = TouchDispatcher::get_instance();
    dispatcher->touchesEnded(x, y);
}

- (void)TouchMoveOffsetX:(double)x OffsetY:(double)y
{
    Director::GetInstance()->GetTopScene()->MouseMotionOffset(x, y);
}

- (void)Update:(GLfloat)dt{
    std::vector<IScene*> scenes = Director::GetInstance()->GetAllScenes();
    for(int i = 0; i < scenes.size();i++)
    {
        scenes[i]->Update(dt);
    }
}

- (void)Render{
    std::vector<IScene*> scenes = Director::GetInstance()->GetAllScenes();
    for(int i = 0; i < scenes.size();i++)
    {
        if(i>0){
            colorRenderer->DrawColor(glm::vec4(0,0,0,0.75f), glm::vec2(0, 0), glm::vec2(1536, 2048));
        }
        scenes[i]->Render();
    }
}

- (void)Realease
{
    std::vector<IScene*> scenes = Director::GetInstance()->GetAllScenes();
    for(int i = 0; i < scenes.size();i++)
    {
        scenes[i]->Release();
    }
}

@end
