//
//  game.cpp
//  BreakOutES
//
//  Created by chen caibin on 2021/10/28.
//

#include "game.hpp"
#include "resource_manager.hpp"
#include "sprite_renderer.hpp"
#include "text_renderer.hpp"

#include "game_level.hpp"
#include "ball_object.hpp"
#include "particle_generator.hpp"
#include "post_processor.hpp"

#include "SimpleAudioEngine.h"

#include <ft2build.h>
#include FT_FREETYPE_H

using namespace CocosDenshion;

SpriteRenderer  *Renderer;
TextRenderer        *Text;
BallObject          *Ball;
SpriteObject        *Player;
ParticleGenerator   *Particles;
PostProcessor       *Effects;

GLfloat             ShakeTime = 0.0f;

void AudioPlay(int sound){
    switch (sound) {
        case BLEEP:
            SimpleAudioEngine::sharedEngine()->playEffect("bleep.wav", false);
            break;
            
        case BLEEP2:
            SimpleAudioEngine::sharedEngine()->playEffect("bleep2.wav", false);
            break;
            
        case SOLID:
            SimpleAudioEngine::sharedEngine()->playEffect("solid.wav", false);
            break;
            
        case POWERUP:
            SimpleAudioEngine::sharedEngine()->playEffect("powerup.wav", false);
            break;
            
        default:
            break;
    }
}

const GLchar *Game::FullPath(GLchar* des,const GLchar *src)
{
    strcpy(des, this->preferPath);
    strcat(des, src);
    return des;
}

Game::Game(GLuint width, GLuint height)
    : State(GAME_ACTIVE), Keys(), Width(width), Height(height)
{

}

Game::~Game()
{

}

void Game::Init()
{
    // 加载着色器
    char vs[1024] = {0};
    char fs[1024] = {0};
    char des[1024] = {0};
    ResourceManager::LoadShader(this->FullPath(vs,"sprite.vs"),this->FullPath(fs,"sprite.fs"),
                                nullptr, "sprite");
    
    memset(vs, 0, sizeof(vs));memset(fs, 0, sizeof(fs));
    ResourceManager::LoadShader(this->FullPath(vs,"particle.vs"), this->FullPath(fs,"particle.fs"),
                                nullptr, "particle");
    
    memset(vs, 0, sizeof(vs));memset(fs, 0, sizeof(fs));
    ResourceManager::LoadShader(this->FullPath(vs,"post_processing.vs"), this->FullPath(fs,"post_processing.fs"),
                                nullptr, "postprocessing");
    
    memset(vs, 0, sizeof(vs));memset(fs, 0, sizeof(fs));
    ResourceManager::LoadShader(this->FullPath(vs,"text_2d.vs"),this->FullPath(fs,"text_2d.fs"),
                                nullptr, "text");
    
    // 配置着色器
    glm::mat4 projection = glm::ortho(0.0f, static_cast<GLfloat>(this->Width),
        static_cast<GLfloat>(this->Height), 0.0f, -1.0f, 1.0f);
    
    Shader spriteShader = ResourceManager::GetShader("sprite");
    spriteShader.use();
    spriteShader.setInt("image", 0);
    spriteShader.setMat4("projection", projection);
    
    Shader particleShader = ResourceManager::GetShader("particle");
    particleShader.use();
    particleShader.setMat4("projection", projection);
    
    Shader textShader = ResourceManager::GetShader("text");
    Text = new TextRenderer(textShader, this->Width, this->Height);
    Text->Load(this->FullPath(des,"default.ttf"),24);
    
    // 设置专用于渲染的控制
    Renderer = new SpriteRenderer(spriteShader);
    
    // 加载纹理
    ResourceManager::LoadTexture(this->FullPath(des,"background.jpg"), GL_FALSE, "background");
    ResourceManager::LoadTexture(this->FullPath(des,"awesomeface.png"), GL_TRUE, "face");
    ResourceManager::LoadTexture(this->FullPath(des,"block.png"), GL_FALSE, "block");
    ResourceManager::LoadTexture(this->FullPath(des,"block_solid.png"), GL_FALSE, "block_solid");
    
    ResourceManager::LoadTexture(this->FullPath(des,"paddle.png"), true, "paddle");
    ResourceManager::LoadTexture(this->FullPath(des,"particle.png"), GL_TRUE, "particle");
    ResourceManager::LoadTexture(this->FullPath(des,"powerup_speed.png"), GL_TRUE, "powerup_speed");
    ResourceManager::LoadTexture(this->FullPath(des,"powerup_sticky.png"), GL_TRUE, "powerup_sticky");
    ResourceManager::LoadTexture(this->FullPath(des,"powerup_increase.png"), GL_TRUE, "powerup_increase");
    ResourceManager::LoadTexture(this->FullPath(des,"powerup_confuse.png"), GL_TRUE, "powerup_confuse");
    ResourceManager::LoadTexture(this->FullPath(des,"powerup_chaos.png"), GL_TRUE, "powerup_chaos");
    ResourceManager::LoadTexture(this->FullPath(des,"powerup_passthrough.png"), GL_TRUE, "powerup_passthrough");
    ResourceManager::LoadTexture(this->FullPath(des,"zanting.png"), GL_FALSE, "ui_btn_pause");
    
    // 加载关卡
    GameLevel one; one.Load(this->FullPath(des,"one.lvl"), this->Width, this->Height * 0.5);
    GameLevel two; two.Load(this->FullPath(des,"two.lvl"), this->Width, this->Height * 0.5);
    GameLevel three; three.Load(this->FullPath(des,"three.lvl"), this->Width, this->Height * 0.5);
    GameLevel four; four.Load(this->FullPath(des,"four.lvl"), this->Width, this->Height * 0.5);
    this->Levels.push_back(one);
    this->Levels.push_back(two);
    this->Levels.push_back(three);
    this->Levels.push_back(four);
    this->Level = 1;
    
    glm::vec2 playerPos = glm::vec2(
            this->Width / 2 - PLAYER_SIZE.x / 2,
            this->Height - PLAYER_SIZE.y
        );
    Player = new SpriteObject(playerPos, PLAYER_SIZE, ResourceManager::GetTexture("paddle"));
    
    glm::vec2 ballPos = playerPos + glm::vec2(PLAYER_SIZE.x / 2 - BALL_RADIUS, -BALL_RADIUS * 2);
    Ball = new BallObject(ballPos, BALL_RADIUS, INITIAL_BALL_VELOCITY,ResourceManager::GetTexture("face"));
    Particles = new ParticleGenerator(
        ResourceManager::GetShader("particle"),
        ResourceManager::GetTexture("particle"),
        200
    );
    Effects = new PostProcessor(ResourceManager::GetShader("postprocessing"), this->Width*2, this->Height*2);
    this->Lives = 3;
    
    SimpleAudioEngine::sharedEngine()->preloadEffect("solid.wav");
    SimpleAudioEngine::sharedEngine()->preloadEffect("bleep.wav");
    SimpleAudioEngine::sharedEngine()->preloadEffect("bleep2.wav");
    SimpleAudioEngine::sharedEngine()->preloadEffect("powerup.wav");
    SimpleAudioEngine::sharedEngine()->preloadBackgroundMusic("breakout.wav");
    SimpleAudioEngine::sharedEngine()->playBackgroundMusic("breakout.wav", true);
}

void Game::Update(GLfloat dt)
{
    this->fps = 1.0f/dt;
    this->deltaTime = dt;
    Ball->Move(dt, this->Width);
    // Check for collisions
    this->DoCollisions();
    GLfloat r = Ball->Radius / 2;
    Particles->Update(dt, *Ball, 2, glm::vec3(r,r,0.0f));
    // Update PowerUps
    this->UpdatePowerUps(dt);
    // Reduce shake time
    if (ShakeTime > 0.0f && Effects != nullptr)
    {
        ShakeTime -= dt;
        if (ShakeTime <= 0.0f)
            Effects->Shake = GL_FALSE;
    }
    // Check loss condition
    if (Ball->Position.y >= this->Height) // Did ball reach bottom edge?
    {
        --this->Lives;
        // 玩家是否已失去所有生命值? : 游戏结束
        if (this->Lives == 0)
        {
            this->ResetLevel();
            this->State = GAME_MENU;
            SimpleAudioEngine::sharedEngine()->stopBackgroundMusic();
            //Director::GetInstance()->PushScene(GameOver::GetInstance());
        }
        this->ResetPlayer();
    }
    // check win condition
    if (this->State == GAME_ACTIVE
        && this->Levels[this->Level].IsCompleted()
        && Effects != nullptr)
    {
        this->ResetLevel();
        this->ResetPlayer();
        Effects->Chaos = true;
        this->State = GAME_WIN;
        SimpleAudioEngine::sharedEngine()->stopBackgroundMusic();
    }
}

void Game::DoubleClickShoot()
{
    if (this->State == GAME_ACTIVE)
    {
        Ball->Stuck = false;
    }
    else if (this->State == GAME_MENU || this->State == GAME_WIN)
    {
        this->State = GAME_ACTIVE;
        SimpleAudioEngine::sharedEngine()->playBackgroundMusic("breakout.wav", true);
    }
}


void Game::ProcessInput(GLfloat dt)
{

}

void Game::MouseMotionOffset(double x,double y)
{
    if (Player->Position.x >= 0 || Player->Position.x <= this->Width - Player->Size.x)
    {
        Player->Position.x += x;
        if (Ball->Stuck)
            Ball->Position.x += x;
    }
}

void Game::Render()
{
    if(this->State == GAME_ACTIVE)
    {
        Effects->BeginRender();
        // 绘制背景
        Renderer->DrawSprite(ResourceManager::GetTexture("background"),
            glm::vec2(0, 0), glm::vec2(this->Width, this->Height), 0.0f
        );
        
        // 绘制关卡
        this->Levels[this->Level].Draw(*Renderer);
        
        Player->Draw(*Renderer);
        
        // Draw PowerUps
        for (PowerUp &powerUp : this->PowerUps){
            if (!powerUp.Destroyed)
                powerUp.Draw(*Renderer);
        }
        
        // Draw particles
        Particles->Draw();
        Ball->Draw(*Renderer);
        
        // End rendering to postprocessing quad
        Effects->EndRender();
        // Render postprocessing quad
        Effects->Render(this->deltaTime);
        
        Text->RenderText(L"生命值", 0, 10, 1.5f, glm::vec3(1.0f,1.0f,1.0f));
        std::stringstream ss; ss << this->Lives;
        Text->RenderText("Live:"+ss.str(), 200.0f, 10.0f, 1.5f, glm::vec3(1.0f,1.0f,1.0f));
    }
    
    if (this->State == GAME_MENU)
    {
        Text->RenderText("Double click to start", 100.0f, this->Height / 2.0f - 40.0f, 2.0f);
        Text->RenderText(L"双击屏幕开始", 100.0f, this->Height / 2.0f + 40.0f, 2.0f);
    }
    if (this->State == GAME_WIN)
    {
        Text->RenderText("You WON!!!", 100.0f, this->Height / 2.0f - 40.0f, 2.0f, glm::vec3(0.0f, 1.0f, 0.0f));
        Text->RenderText("Double click to start", 100.0f, this->Height / 2.0f + 40, 2.0f, glm::vec3(1.0f, 1.0f, 0.0f));
    }
}

void Game::ResetLevel()
{
    char des[1024] = {0};
    if (this->Level == 0)this->Levels[0].Load(this->FullPath(des,"one.lvl"), this->Width, this->Height * 0.5f);
    else if (this->Level == 1)
        this->Levels[1].Load(this->FullPath(des,"two.lvl"), this->Width, this->Height * 0.5f);
    else if (this->Level == 2)
        this->Levels[2].Load(this->FullPath(des,"three.lvl"), this->Width, this->Height * 0.5f);
    else if (this->Level == 3)
        this->Levels[3].Load(this->FullPath(des,"four.lvl"), this->Width, this->Height * 0.5f);
    
    this->Lives = 3;
}

void Game::ResetPlayer()
{
    // Reset player/ball stats
    Player->Size = glm::vec3(PLAYER_SIZE.x,PLAYER_SIZE.y,1.0f);
    glm::vec2 pos = glm::vec2(this->Width / 2 - PLAYER_SIZE.x / 2, this->Height - PLAYER_SIZE.y);
    Player->Position = glm::vec3(pos.x,pos.y,0.0f);
    Ball->Reset(pos + glm::vec2(PLAYER_SIZE.x / 2 - BALL_RADIUS, -(BALL_RADIUS * 2)), INITIAL_BALL_VELOCITY);
    // Also disable all active powerups
    if(Effects != nullptr)
    {
        Effects->Chaos = Effects->Confuse = GL_FALSE;
    }
    Ball->PassThrough = Ball->Sticky = GL_FALSE;
    Player->Color = glm::vec3(1.0f);
    Ball->Color = glm::vec3(1.0f);
}

void ActivatePowerUp(PowerUp &powerUp)
{
    // 根据道具类型发动道具
    if (powerUp.Type == "speed")
    {
        Ball->Velocity *= 1.2;
    }
    else if (powerUp.Type == "sticky")
    {
        Ball->Sticky = GL_TRUE;
        Player->Color = glm::vec3(1.0f, 0.5f, 1.0f);
    }
    else if (powerUp.Type == "pass-through")
    {
        Ball->PassThrough = GL_TRUE;
        Ball->Color = glm::vec3(1.0f, 0.5f, 0.5f);
    }
    else if (powerUp.Type == "pad-size-increase")
    {
        Player->Size.x += 50;
    }
    else if (powerUp.Type == "confuse")
    {
        if (Effects != nullptr && !Effects->Chaos)
            Effects->Confuse = GL_TRUE; // 只在chaos未激活时生效，chaos同理
    }
    else if (powerUp.Type == "chaos")
    {
        if (Effects != nullptr && !Effects->Confuse)
            Effects->Chaos = GL_TRUE;
    }
}

void Game::DoCollisions()
{
    for (GameObject &box : this->Levels[this->Level].Bricks)
    {
        if (!box.Destroyed)
        {
            Collision collision = CheckCollision(*Ball, box);
            if (std::get<0>(collision)) // If collision is true
            {
                // Destroy block if not solid
                if (!box.IsSolid)
                {
                    box.Destroyed = GL_TRUE;
                    this->SpawnPowerUps(box);
                    AudioPlay(BLEEP2);
                }
                else if(Effects != nullptr)
                {   // if block is solid, enable shake effect
                    ShakeTime = 0.05f;
                    Effects->Shake = GL_TRUE;
                    AudioPlay(SOLID);
                }
                // Collision resolution
                Direction dir = std::get<1>(collision);
                glm::vec2 diff_vector = std::get<2>(collision);
                if (!(Ball->PassThrough && !box.IsSolid))
                {
                    if (dir == DIR_LEFT || dir == DIR_RIGHT) // Horizontal collision
                    {
                        Ball->Velocity.x = -Ball->Velocity.x; // Reverse horizontal velocity
                        // Relocate
                        GLfloat penetration = Ball->Radius - std::abs(diff_vector.x);
                        if (dir == DIR_LEFT)
                            Ball->Position.x += penetration; // Move ball to right
                        else
                            Ball->Position.x -= penetration; // Move ball to left;
                    }
                    else // Vertical collision
                    {
                        Ball->Velocity.y = -Ball->Velocity.y; // Reverse vertical velocity
                        // Relocate
                        GLfloat penetration = Ball->Radius - std::abs(diff_vector.y);
                        if (dir == DIR_UP)
                            Ball->Position.y -= penetration; // Move ball bback up
                        else
                            Ball->Position.y += penetration; // Move ball back down
                    }
                }
            }
        }
    }
    // Also check collisions for player pad (unless stuck)
    Collision result = CheckCollision(*Ball, *Player);
    if (!Ball->Stuck && std::get<0>(result))
    {
        // Check where it hit the board, and change velocity based on where it hit the board
        GLfloat centerBoard = Player->Position.x + Player->Size.x / 2;
        GLfloat distance = (Ball->Position.x + Ball->Radius) - centerBoard;
        GLfloat percentage = distance / (Player->Size.x / 2);
        // Then move accordingly
        GLfloat strength = 2.0f;
        glm::vec2 oldVelocity = Ball->Velocity;
        Ball->Velocity.x = INITIAL_BALL_VELOCITY.x * percentage * strength;
        //Ball->Velocity.y = -Ball->Velocity.y;
        Ball->Velocity = glm::normalize(Ball->Velocity) * glm::length(oldVelocity); // Keep speed consistent over both axes (multiply by length of old velocity, so total strength is not changed)
        // Fix sticky paddle
        Ball->Velocity.y = -1 * abs(Ball->Velocity.y);
        Ball->Stuck = Ball->Sticky;
        AudioPlay(BLEEP);
    }
    for (PowerUp &powerUp : this->PowerUps)
    {
        if (!powerUp.Destroyed)
        {
            if (powerUp.Position.y >= this->Height)
                powerUp.Destroyed = GL_TRUE;
            if (CheckCollision(*Player, powerUp))
            {   // 道具与挡板接触，激活它！
                ActivatePowerUp(powerUp);
                powerUp.Destroyed = GL_TRUE;
                powerUp.Activated = GL_TRUE;
                AudioPlay(POWERUP);
            }
        }
    }
}

GLboolean CheckCollision(GameObject &one, GameObject &two) // AABB - AABB collision
{
    // Collision x-axis?
    bool collisionX = one.Position.x + one.Size.x >= two.Position.x &&
        two.Position.x + two.Size.x >= one.Position.x;
    // Collision y-axis?
    bool collisionY = one.Position.y + one.Size.y >= two.Position.y &&
        two.Position.y + two.Size.y >= one.Position.y;
    // Collision only if on both axes
    return collisionX && collisionY;
}

Collision CheckCollision(BallObject &one, GameObject &two) // AABB - Circle collision
{
    // Get center point circle first
    glm::vec2 center(one.Position + one.Radius);
    // Calculate AABB info (center, half-extents)
    glm::vec2 aabb_half_extents(two.Size.x / 2, two.Size.y / 2);
    glm::vec2 aabb_center(two.Position.x + aabb_half_extents.x, two.Position.y + aabb_half_extents.y);
    // Get difference vector between both centers
    glm::vec2 difference = center - aabb_center;
    glm::vec2 clamped = glm::clamp(difference, -aabb_half_extents, aabb_half_extents);
    // Now that we know the the clamped values, add this to AABB_center and we get the value of box closest to circle
    glm::vec2 closest = aabb_center + clamped;
    // Now retrieve vector between center circle and closest point AABB and check if length < radius
    difference = closest - center;
    
    if (glm::length(difference) < one.Radius) // not <= since in that case a collision also occurs when object one exactly touches object two, which they are at the end of each collision resolution stage.
        return std::make_tuple(GL_TRUE, VectorDirection(difference), difference);
    else
        return std::make_tuple(GL_FALSE, DIR_UP, glm::vec2(0, 0));
}

// Calculates which direction a vector is facing (N,E,S or W)
Direction VectorDirection(glm::vec2 target)
{
    glm::vec2 compass[] = {
        glm::vec2(0.0f, 1.0f),    // up
        glm::vec2(1.0f, 0.0f),    // right
        glm::vec2(0.0f, -1.0f),    // down
        glm::vec2(-1.0f, 0.0f)    // left
    };
    GLfloat max = 0.0f;
    GLuint best_match = -1;
    for (GLuint i = 0; i < 4; i++)
    {
        GLfloat dot_product = glm::dot(glm::normalize(target), compass[i]);
        if (dot_product > max)
        {
            max = dot_product;
            best_match = i;
        }
    }
    return (Direction)best_match;
}

GLboolean ShouldSpawn(GLuint chance)
{
    GLuint random = rand() % chance;
    return random == 0;
}

void Game::SpawnPowerUps(GameObject &block)
{
    if (ShouldSpawn(75)) // 1 in 75 chance
        this->PowerUps.push_back(PowerUp("speed", glm::vec3(0.5f, 0.5f, 1.0f), 0.0f, block.Position, ResourceManager::GetTexture("powerup_speed")));
    if (ShouldSpawn(75))
        this->PowerUps.push_back(PowerUp("sticky", glm::vec3(1.0f, 0.5f, 1.0f), 20.0f, block.Position, ResourceManager::GetTexture("powerup_sticky")));
    if (ShouldSpawn(75))
        this->PowerUps.push_back(PowerUp("pass-through", glm::vec3(0.5f, 1.0f, 0.5f), 10.0f, block.Position, ResourceManager::GetTexture("powerup_passthrough")));
    if (ShouldSpawn(75))
        this->PowerUps.push_back(PowerUp("pad-size-increase", glm::vec3(1.0f, 0.6f, 0.4), 0.0f, block.Position, ResourceManager::GetTexture("powerup_increase")));
    if (ShouldSpawn(15)) // Negative powerups should spawn more often
        this->PowerUps.push_back(PowerUp("confuse", glm::vec3(1.0f, 0.3f, 0.3f), 15.0f, block.Position, ResourceManager::GetTexture("powerup_confuse")));
    if (ShouldSpawn(15))
        this->PowerUps.push_back(PowerUp("chaos", glm::vec3(0.9f, 0.25f, 0.25f), 15.0f, block.Position, ResourceManager::GetTexture("powerup_chaos")));
    
}

GLboolean isOtherPowerUpActive(std::vector<PowerUp> &powerUps, std::string type)
{
    for (const PowerUp &powerUp : powerUps)
    {
        if (powerUp.Activated)
            if (powerUp.Type == type)
                return GL_TRUE;
    }
    return GL_FALSE;
}

void Game::UpdatePowerUps(GLfloat dt)
{
    for (PowerUp &powerUp : this->PowerUps)
    {
        powerUp.Position += powerUp.Velocity * dt;
        if (powerUp.Activated)
        {
            powerUp.Duration -= dt;

            if (powerUp.Duration <= 0.0f)
            {
                // 之后会将这个道具移除
                powerUp.Activated = GL_FALSE;
                // 停用效果
                if (powerUp.Type == "sticky")
                {
                    if (!isOtherPowerUpActive(this->PowerUps, "sticky"))
                    {   // 仅当没有其他sticky效果处于激活状态时重置，以下同理
                        Ball->Sticky = GL_FALSE;
                        Player->Color = glm::vec3(1.0f);
                    }
                }
                else if (powerUp.Type == "pass-through")
                {
                    if (!isOtherPowerUpActive(this->PowerUps, "pass-through"))
                    {
                        Ball->PassThrough = GL_FALSE;
                        Ball->Color = glm::vec3(1.0f);
                    }
                }
                else if (powerUp.Type == "confuse")
                {
                    if (!isOtherPowerUpActive(this->PowerUps, "confuse"))
                    {
                        Effects->Confuse = GL_FALSE;
                    }
                }
                else if (powerUp.Type == "chaos")
                {
                    if (!isOtherPowerUpActive(this->PowerUps, "chaos"))
                    {
                        Effects->Chaos = GL_FALSE;
                    }
                }
            }
        }
    }
    this->PowerUps.erase(std::remove_if(this->PowerUps.begin(), this->PowerUps.end(),
        [](const PowerUp &powerUp) { return powerUp.Destroyed && !powerUp.Activated; }
    ), this->PowerUps.end());
}
