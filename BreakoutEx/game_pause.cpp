//
//  game_pause.cpp
//  BreakoutEx
//
//  Created by chen caibin on 2022/1/11.
//

#include "game_pause.hpp"
#include "resource_manager.hpp"
#include "sprite_renderer.hpp"
#include "text_renderer.hpp"
#include "director.hpp"
#include "game_start.hpp"
#include "game.hpp"
#include "button.hpp"

GamePause* GamePause::s_instance = nullptr;
extern SpriteRenderer      *Renderer;
extern TextRenderer        *Text;

Button              *HomeButton_Pause;
Button              *ContinueButton_Pause;
Button              *SoundButton_Pause;

void Pause_HomeBtnOnClick() {
    Game::GetInstance()->ResetLevel();
    Game::GetInstance()->ResetPlayer();
    Director::GetInstance()->SetRootScene(GameStart::GetInstance());
    printf("click btn home \n");
}

void Pause_ContinueBtnOnClick() {
    Director::GetInstance()->PopScene();
    printf("click btn continue \n");
}

void Pause_SoundBtnOnClick() {
    
    
    printf("click btn sound \n");
}

const GLchar *GamePause::FullPath(const GLchar *fileName)
{
    memset(this->fullPath, 0, sizeof(this->fullPath));
    strcpy(this->fullPath, this->preferPath);
    strcat(this->fullPath, fileName);
    return this->fullPath;
}

void GamePause::Init(unsigned int width, unsigned int height)
{
    this->Width = width;
    this->Height = height;
    ResourceManager::LoadTexture(this->FullPath("shengyin_k.png"), GL_FALSE, "ui_btn_sound_on");
    ResourceManager::LoadTexture(this->FullPath("shengyin_g.png"), GL_FALSE, "ui_btn_sound_off");
    ResourceManager::LoadTexture(this->FullPath("continue.png"), GL_FALSE, "ui_btn_continue");
    
    float scal = 2.0f;
    HomeButton_Pause = new Button(this,glm::vec2(this->Width/2-128*scal,this->Height/2),
                              glm::vec2(64*scal,64*scal),
                              ResourceManager::GetTexture("ui_btn_home"),
                              Pause_HomeBtnOnClick);
    
    ContinueButton_Pause = new Button(this,glm::vec2(this->Width/2-32*scal,this->Height/2),
                              glm::vec2(64*scal,64*scal),
                              ResourceManager::GetTexture("ui_btn_continue"),
                              Pause_ContinueBtnOnClick);
    
    SoundButton_Pause = new Button(this,glm::vec2(this->Width/2+64*scal,this->Height/2),
                               glm::vec2(64*scal,64*scal),
                               ResourceManager::GetTexture("ui_btn_sound_on"),
                               Pause_SoundBtnOnClick);
}

void GamePause::OnEnter(){
    
}

void GamePause::OnExit(){
    
}

void GamePause::KeyboardInput(int virtual_key, char pressed)
{
    
}

void GamePause::Update(GLfloat dt)
{
    
}

void GamePause::Render()
{
    HomeButton_Pause->Draw(*Renderer);
    ContinueButton_Pause->Draw(*Renderer);
    SoundButton_Pause->Draw(*Renderer);
}

void GamePause::MouseMotionOffset(double x,double y)
{
    
}

void GamePause::Release()
{
    
}
