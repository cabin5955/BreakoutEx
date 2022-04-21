//
//  ball_object.hpp
//  LearnOpenGL_BreakOut
//
//  Created by chen caibin on 2021/9/26.
//

#ifndef ball_object_hpp
#define ball_object_hpp

#include "glad.h"
#include <glm/glm.hpp>

#include "texture.hpp"
#include "sprite_renderer.hpp"
#include "sprite_object.hpp"

// BallObject holds the state of the Ball object inheriting
// relevant state data from GameObject. Contains some extra
// functionality specific to Breakout's ball object that
// were too specific for within GameObject alone.
class BallObject : public SpriteObject
{
public:
    // Ball state
    GLfloat   Radius;
    GLboolean Stuck;
    GLboolean Sticky, PassThrough;
    
    // Constructor(s)
    BallObject();
    BallObject(glm::vec2 pos, GLfloat radius, glm::vec2 velocity, Texture2D sprite);
    // Moves the ball, keeping it constrained within the window bounds (except bottom edge); returns new position
    glm::vec2 Move(GLfloat dt, GLuint window_width);
    // Resets the ball to original state with given position and velocity
    void      Reset(glm::vec2 position, glm::vec2 velocity);
};

#endif /* ball_object_hpp */
