//
//  game_start.cpp
//  BreakoutEx
//
//  Created by chen caibin on 2022/1/6.
//

#include "game_start.hpp"

#include "resource_manager.hpp"
#include "sprite_renderer.hpp"
#include "text_renderer.hpp"
#include "color_renderer.hpp"
#include "director.hpp"
#include "game.hpp"
#include "button.hpp"

GameStart* GameStart::s_instance = nullptr;

extern SpriteRenderer      *Renderer;
extern TextRenderer        *Text;
ColorRenderer       *colorRenderer;

Button              *SettingButton;
Button              *CommentButton;
Button              *PaihangButton;
Button              *PlayButton;

void CommentBtnOnClick() {
    printf("click btn comment \n");
}

void SettingBtnOnClick() {
    
    printf("click btn setting \n");
}

void PaihangBtnOnClick() {
    
    printf("click btn paihang \n");
}

void PlayBtnOnClick() {
    printf("click btn play \n");
    Game::GetInstance()->ResetLevel();
    Game::GetInstance()->ResetPlayer();
    Director::GetInstance()->SetRootScene(Game::GetInstance());
}

const GLchar *GameStart::FullPath(const GLchar *fileName)
{
    memset(this->fullPath, 0, sizeof(this->fullPath));
    strcpy(this->fullPath, this->preferPath);
    strcat(this->fullPath, fileName);
    return this->fullPath;
}

void GameStart::Init(unsigned int width, unsigned int height)
{
    this->Width = width;
    this->Height = height;
    // 加载着色器
    char vs[1024] = {0}, fs[1024] = {0};
    memset(vs, 0, sizeof(vs));memset(fs, 0, sizeof(fs));
    strcpy(vs, this->FullPath("color.vs"));
    strcpy(fs, this->FullPath("color.fs"));
    ResourceManager::LoadShader(vs, fs, nullptr, "color");
    
    ResourceManager::LoadTexture(this->FullPath("background.jpg"), GL_FALSE, "background");
    ResourceManager::LoadTexture(this->FullPath("shezhi.png"), GL_FALSE, "ui_btn_setting");
    ResourceManager::LoadTexture(this->FullPath("dianzan.png"), GL_FALSE, "ui_btn_comment");
    ResourceManager::LoadTexture(this->FullPath("paiming.png"), GL_FALSE, "ui_btn_paihang");
    ResourceManager::LoadTexture(this->FullPath("kaishi.png"), GL_FALSE, "ui_btn_play");
    
    glm::mat4 projection = glm::ortho(0.0f, static_cast<GLfloat>(this->Width),
        static_cast<GLfloat>(this->Height), 0.0f, -1.0f, 1.0f);
    
    Shader colorShader = ResourceManager::GetShader("color");
    colorShader.use();
    colorShader.setMat4("projection", projection);
    colorRenderer = new ColorRenderer(colorShader);
    
    float scal = 2.0f;
    
    SettingButton = new Button(this,glm::vec2(this->Width/2-128*scal,this->Height-100*scal),
                              glm::vec2(64*scal,64*scal),
                              ResourceManager::GetTexture("ui_btn_setting"),
                              SettingBtnOnClick);
    
    CommentButton = new Button(this,glm::vec2(this->Width/2-32*scal,this->Height-100*scal),
                              glm::vec2(64*scal,64*scal),
                              ResourceManager::GetTexture("ui_btn_comment"),
                              CommentBtnOnClick);
    
    PaihangButton = new Button(this,glm::vec2(this->Width/2+64*scal,this->Height-100*scal),
                              glm::vec2(64*scal,64*scal),
                              ResourceManager::GetTexture("ui_btn_paihang"),
                              PaihangBtnOnClick);
    
    PlayButton = new Button(this,glm::vec2(this->Width/2-64*scal,this->Height/2-64*scal),
                              glm::vec2(128*scal,128*scal),
                              ResourceManager::GetTexture("ui_btn_play"),
                              PlayBtnOnClick);
    
}

void GameStart::OnEnter(){
}

void GameStart::OnExit(){
    
}

void GameStart::KeyboardInput(int virtual_key, char pressed)
{
    
}

void GameStart::Update(GLfloat dt)
{
    
}

void GameStart::Render()
{
    float scal = 2.0f;
    // 绘制背景
    Renderer->DrawSprite(ResourceManager::GetTexture("background"),
        glm::vec2(0, 0), glm::vec2(this->Width, this->Height), 0.0f
    );
    Text->RenderText("Breakout", 100.0f, this->Height / 2.0f-150*scal, 4.0f);
    SettingButton->Draw(*Renderer);
    CommentButton->Draw(*Renderer);
    PaihangButton->Draw(*Renderer);
    PlayButton->Draw(*Renderer);
}

void GameStart::MouseMotionOffset(double x,double y)
{
    
}

void GameStart::Release()
{
    
}

