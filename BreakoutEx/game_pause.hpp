//
//  game_pause.hpp
//  BreakoutEx
//
//  Created by chen caibin on 2022/1/11.
//

#ifndef game_pause_hpp
#define game_pause_hpp

#include "glad.h"
#include <vector>

#include "scene.h"
#include <string>

class GamePause:public IScene
{
public:
    
    // Initialize game state (load all shaders/textures/levels)
    void Init(unsigned int width, unsigned int height);
    void OnEnter();
    void OnExit();
    // GameLoop
    void KeyboardInput(int virtual_key, char pressed);
    void Update(GLfloat dt);
    void Render();
    void MouseMotionOffset(double x,double y);
    
    void Release();
    
    static GamePause* GetInstance()
    {
        if(s_instance == nullptr)
        {
            s_instance = new GamePause();
        }
        return s_instance;
    }
    GLchar                 preferPath[1024];
    
private:
    const GLchar *FullPath(const GLchar *fileName);
    GLchar  fullPath[1024];
    GLfloat deltaTime;
    
    GamePause(){}
    
    ~GamePause(){}

    GamePause(const GamePause&);
    GamePause& operator =(const GamePause&);
    
    static GamePause *s_instance;
};

#endif /* game_pause_hpp */
