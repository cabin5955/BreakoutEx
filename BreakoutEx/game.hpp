//
//  game.hpp
//  BreakOutES
//
//  Created by chen caibin on 2021/10/28.
//

#ifndef game_hpp
#define game_hpp

#include "gles.h"

// Represents the current state of the game
enum GameState {
    GAME_ACTIVE,
    GAME_MENU,
    GAME_WIN
};

class Game
{
public:
    // Game state
    GameState              State;
    GLboolean              Keys[1024];
    GLuint                 Width, Height;
    GLchar                 preferPath[1024];
    // Constructor/Destructor
    Game(GLuint width, GLuint height);
    ~Game();
    // Initialize game state (load all shaders/textures/levels)
    void Init();
    // GameLoop
    void ProcessInput(GLfloat dt);
    void Update(GLfloat dt);
    void Render();
    
private:
    const GLchar *FullPath(GLchar* des,const GLchar *src);
};

#endif /* game_hpp */
