//
//  game.hpp
//  BreakOutES
//
//  Created by chen caibin on 2021/10/28.
//

#ifndef game_hpp
#define game_hpp

#include "glad.h"

#include <vector>
#include "game_level.hpp"
#include "ball_object.hpp"
#include "power_up.h"
#include <string>

// Represents the current state of the game
enum GameState {
    GAME_ACTIVE,
    GAME_MENU,
    GAME_WIN
};

// Represents the four possible (collision) directions
enum Direction {
    DIR_UP,
    DIR_RIGHT,
    DIR_DOWN,
    DIR_LEFT
};

// Defines a Collision typedef that represents collision data
typedef std::tuple<GLboolean, Direction, glm::vec2> Collision; // <collision?, what direction?, difference vector center - closest point>

// Initial size of the player paddle
const glm::vec2 PLAYER_SIZE(200, 40);
// Initial velocity of the player paddle
const GLfloat PLAYER_VELOCITY(500.0f);
// Initial velocity of the Ball
const glm::vec2 INITIAL_BALL_VELOCITY(200.0f, -700.0f);
// Radius of the ball object
const GLfloat BALL_RADIUS = 25.0f;

class Game
{
public:
    GLuint Lives;
    // Game state
    GameState              State;
    std::vector<GameLevel> Levels;
    GLuint                 Level;
    std::vector<PowerUp>   PowerUps;
    GLboolean              Keys[1024];
    GLuint                 Width, Height;
    GLchar                 preferPath[1024];
    double                 fps;
    
    // Constructor/Destructor
    Game(GLuint width, GLuint height);
    ~Game();
    // Initialize game state (load all shaders/textures/levels)
    void Init();
    // GameLoop
    void ProcessInput(GLfloat dt);
    void Update(GLfloat dt);
    void Render();
    
    void DoCollisions();
    void DoubleClickShoot();
    void MouseMotionOffset(double x,double y);
    // Reset
    void ResetLevel();
    void ResetPlayer();
    void SpawnPowerUps(GameObject &block);
    void UpdatePowerUps(GLfloat dt);
    
    void Release();
    
private:
    const GLchar *FullPath(GLchar* des,const GLchar *src);
    GLfloat deltaTime;
};

// Collision detection
GLboolean CheckCollision(GameObject &one, GameObject &two);
Collision CheckCollision(BallObject &one, GameObject &two);
Direction VectorDirection(glm::vec2 closest);

#endif /* game_hpp */
