//
//  game_over.cpp
//  BreakoutEx
//
//  Created by chen caibin on 2022/1/10.
//

#include "game_over.hpp"

#include "resource_manager.hpp"
#include "sprite_renderer.hpp"
#include "text_renderer.hpp"
#include "director.hpp"
#include "game_start.hpp"
#include "button.hpp"
#include "game.hpp"

GameOver* GameOver::s_instance = nullptr;
extern SpriteRenderer      *Renderer;
extern TextRenderer        *Text;

Button              *HomeButton;
Button              *ReplayButton;
Button              *RankButton_Over;

void HomeBtnOnClick() {
    Game::GetInstance()->ResetLevel();
    Game::GetInstance()->ResetPlayer();
    Director::GetInstance()->SetRootScene(GameStart::GetInstance());
    printf("click btn home \n");
}

void ReplayBtnOnClick() {
    Game::GetInstance()->ResetLevel();
    Game::GetInstance()->ResetPlayer();
    Director::GetInstance()->PopScene();
    printf("click btn replay \n");
}

void RankBtnOnClick() {
    
    printf("click btn rank \n");
}

const GLchar *GameOver::FullPath(const GLchar *fileName)
{
    memset(this->fullPath, 0, sizeof(this->fullPath));
    strcpy(this->fullPath, this->preferPath);
    strcat(this->fullPath, fileName);
    return this->fullPath;
}

void GameOver::Init(unsigned int width, unsigned int height)
{
    this->Width = width;
    this->Height = height;
    ResourceManager::LoadTexture(this->FullPath("zhuye.png"), GL_FALSE, "ui_btn_home");
    ResourceManager::LoadTexture(this->FullPath("zaitiaozhan.png"), GL_FALSE, "ui_btn_replay");
    float scal = 2.0f;
    HomeButton = new Button(this,glm::vec2(this->Width/2-128*scal,this->Height/2),
                              glm::vec2(64*scal,64*scal),
                              ResourceManager::GetTexture("ui_btn_home"),
                              HomeBtnOnClick);
    
    ReplayButton = new Button(this,glm::vec2(this->Width/2-32*scal,this->Height/2),
                              glm::vec2(64*scal,64*scal),
                              ResourceManager::GetTexture("ui_btn_replay"),
                              ReplayBtnOnClick);
    
    RankButton_Over = new Button(this,glm::vec2(this->Width/2+64*scal,this->Height/2),
                               glm::vec2(64*scal,64*scal),
                               ResourceManager::GetTexture("ui_btn_paihang"),
                               RankBtnOnClick);
}

void GameOver::OnEnter(){
    
}

void GameOver::OnExit(){
    
}

void GameOver::KeyboardInput(int virtual_key, char pressed)
{
    
}

void GameOver::Update(GLfloat dt)
{
    
}

void GameOver::Render()
{
    Text->RenderText("Game Over", 100.0f, this->Height / 2.0f-150, 4.0f);
    
    HomeButton->Draw(*Renderer);
    ReplayButton->Draw(*Renderer);
    RankButton_Over->Draw(*Renderer);
}

void GameOver::MouseMotionOffset(double x,double y)
{
    
}

void GameOver::Release()
{
    
}
