//
//  game_level.hpp
//  LearnOpenGL
//
//  Created by chen caibin on 2021/9/25.
//

#ifndef game_level_hpp
#define game_level_hpp
#include "glad.h"
#include <glm/glm.hpp>

#include "sprite_object.hpp"
#include "sprite_renderer.hpp"
#include "resource_manager.hpp"

#include <vector>

/// GameLevel holds all Tiles as part of a Breakout level and
/// hosts functionality to Load/render levels from the harddisk.
class GameLevel
{
public:
    // Level state
    std::vector<SpriteObject> Bricks;
    // Constructor
    GameLevel() { }
    // Loads level from file
    void      Load(const GLchar *file, GLuint levelWidth, GLuint levelHeight);
    // Render level
    void      Draw(SpriteRenderer &renderer);
    // Check if the level is completed (all non-solid tiles are destroyed)
    GLboolean IsCompleted();
private:
    // Initialize level from tile data
    void      init(std::vector<std::vector<GLuint>> tileData, GLuint levelWidth, GLuint levelHeight);
};

#endif /* game_level_hpp */
