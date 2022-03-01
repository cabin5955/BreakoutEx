//
//  button.cpp
//  BreakoutEx
//
//  Created by chen caibin on 2021/12/23.
//

#include "button.hpp"
#include "touch_dispatcher.hpp"

Button::Button(IScene *scene, glm::vec2 pos, glm::vec2 size,Texture2D sprite, ClickCallback onClick)
    : Position(pos)
    , Size(size)
    , sprite(sprite)
    , onClick(onClick)
    , mouseState(MOUSE_NONE){
        
        TouchDispatcher *dispatcher = TouchDispatcher::get_instance();
        dispatcher->addTargetedDelegate(scene->GetSceneID(), this, 0);
}

Button::~Button() {
}

bool Button::TouchBegan(double x, double y) {
    if (x >= (Position.x) && x <= (Position.x+Size.x) &&
        y >= (Position.y) && y <= (Position.y+Size.y)) {
            mouseState = MOUSE_PRESSED;
        }
    return true;
}

void Button::TouchEnded(double x, double y) {
    if (x >= (Position.x) && x <= (Position.x+Size.x) &&
        y >= (Position.y) && y <= (Position.y+Size.y)
        ) {
            if(mouseState == MOUSE_PRESSED){
                onClick();
            }
        }
    mouseState = MOUSE_NONE;
}

void Button::TouchMoved(double x, double y) {
    if (x >= (Position.x) && x <= (Position.x+Size.x) &&
        y >= (Position.y) && y <= (Position.y+Size.y)) {
            
        }
}

void Button::TouchCancelled(double x, double y)
{
    
}

void Button::Draw(SpriteRenderer &renderer){
    if(mouseState == MOUSE_PRESSED)
        renderer.DrawSprite(sprite, Position, Size*0.9f, 0, glm::vec3(1.0f,1.0f,1.0f));
    else
        renderer.DrawSprite(sprite, Position, Size, 0, glm::vec3(1.0f,1.0f,1.0f));
}
