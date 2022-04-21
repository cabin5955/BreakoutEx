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

#include "scene.h"
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

enum SoundEffect{
    BLEEP,
    BLEEP2,
    SOLID,
    POWERUP,
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

class Game:public IScene
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
    double                 fps;
    
    // Initialize game state (load all shaders/textures/levels)
    void Init(unsigned int width,unsigned int height);
    void OnEnter();
    void OnExit();
    // GameLoop
    void KeyboardInput(int virtual_key, char pressed);
    void Update(GLfloat dt);
    void Render();
    
    void DoCollisions();
    
    // Reset
    void ResetLevel();
    void ResetPlayer();
    void SpawnPowerUps(GameObject &block);
    void UpdatePowerUps(GLfloat dt);
    
    void Release();
    
    static Game* GetInstance()
    {
        if(s_instance == nullptr)
        {
            s_instance = new Game();
        }
        return s_instance;
    }
    
private:
    GLfloat deltaTime;

    Game()
    {
        this->State = GAME_MENU;
    }
    
    ~Game()
    {
    
    }

    Game(const Game&);
    Game& operator =(const Game&);
    
    static Game *s_instance;
};

// Collision detection
GLboolean CheckCollision(GameObject &one, GameObject &two);
Collision CheckCollision(BallObject &one, GameObject &two);
Direction VectorDirection(glm::vec2 closest);

#endif /* game_hpp */
