//
//  button.hpp
//  BreakoutEx
//
//  Created by chen caibin on 2021/12/23.
//

#ifndef button_hpp
#define button_hpp
#include "glad.h"
#include <glm/glm.hpp>

#include "texture.hpp"
#include "sprite_renderer.hpp"
#include "touch_delegate_protocol.h"
#include "scene.h"

enum MouseState {
    MOUSE_NONE,
    MOUSE_PRESSED
};

class Button:public TouchDelegate
{
public:
    typedef void (*ClickCallback)();
    Button(IScene *scene, glm::vec2 pos, glm::vec2 size, Texture2D sprite, ClickCallback onClick);
    ~Button();
    
    bool TouchBegan(double x, double y);
    // optional

    void TouchMoved(double x, double y);
    void TouchEnded(double x, double y);
    void TouchCancelled(double x, double y);
    
    void Draw(SpriteRenderer &renderer);

    glm::vec2   Position, Size;
    ClickCallback onClick;
    Texture2D sprite;
    MouseState mouseState;
};

#endif /* button_hpp */
