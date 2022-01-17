//
//  game.cpp
//  BreakOutES
//
//  Created by chen caibin on 2021/10/28.
//

#include "game.hpp"
#include "resource_manager.hpp"
#include "sprite_renderer.hpp"

SpriteRenderer  *Renderer;
Game::Game(GLuint width, GLuint height)
    : State(GAME_ACTIVE), Keys(), Width(width), Height(height)
{

}

Game::~Game()
{

}

const GLchar *Game::FullPath(GLchar* des,const GLchar *src)
{
    strcpy(des, this->preferPath);
    strcat(des, src);
    return des;
}

void Game::Init()
{
    // 加载着色器
    char vs[1024] = {0};
    char fs[1024] = {0};
    char des[1024] = {0};
    ResourceManager::LoadShader(this->FullPath(vs,"sprite.vs"),this->FullPath(fs,"sprite.fs"), nullptr, "sprite");
    // 配置着色器
    glm::mat4 projection = glm::ortho(0.0f, static_cast<GLfloat>(this->Width),
        static_cast<GLfloat>(this->Height), 0.0f, -1.0f, 1.0f);
    Shader spriteShader = ResourceManager::GetShader("sprite");
    spriteShader.use();
    spriteShader.setInt("image", 0);
    spriteShader.setMat4("projection", projection);
    // 设置专用于渲染的控制
    Renderer = new SpriteRenderer(spriteShader);
    
    // 加载纹理
    ResourceManager::LoadTexture(this->FullPath(des,"awesomeface.png"), GL_TRUE, "face");
    ResourceManager::LoadTexture(this->FullPath(des,"block.png"), GL_FALSE, "block");
    ResourceManager::LoadTexture(this->FullPath(des,"block_solid.png"), GL_FALSE, "block_solid");
}

void Game::Update(GLfloat dt)
{

}


void Game::ProcessInput(GLfloat dt)
{

}

void Game::Render()
{
    Renderer->DrawSprite(ResourceManager::GetTexture("face"), glm::vec2(200, 200), glm::vec2(300, 300), 0.0f, glm::vec3(0.0f, 1.0f, 0.0f));
}
