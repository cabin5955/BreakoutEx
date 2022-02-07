//
//  power_up.h
//  LearnOpenGL_BreakOut
//
//  Created by chen caibin on 2021/9/27.
//

#ifndef power_up_h
#define power_up_h
#include <string>

#include "glad.h"
#include <glm/glm.hpp>

#include "sprite_object.hpp"


// The size of a PowerUp block
const glm::vec2 SIZE(120, 40);
// Velocity a PowerUp block has when spawned
const glm::vec2 VELOCITY(0.0f, 300.0f);


// PowerUp inherits its state and rendering functions from
// GameObject but also holds extra information to state its
// active duration and whether it is activated or not.
// The type of PowerUp is stored as a string.
class PowerUp : public SpriteObject
{
public:
    // PowerUp State
    std::string Type;
    GLfloat     Duration;
    GLboolean   Activated;
    // Constructor
    PowerUp(std::string type, glm::vec3 color, GLfloat duration, glm::vec2 position, Texture2D texture)
        : SpriteObject(position, SIZE, texture, color, VELOCITY), Type(type), Duration(duration), Activated() { }
};

#endif /* power_up_h */
