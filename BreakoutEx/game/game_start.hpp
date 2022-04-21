//
//  game_start.hpp
//  BreakoutEx
//
//  Created by chen caibin on 2022/1/6.
//

#ifndef game_start_hpp
#define game_start_hpp

#include "glad.h"
#include <vector>

#include "scene.h"
#include <string>

class GameStart:public IScene
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
    
    void Release();
    
    static GameStart* GetInstance()
    {
        if(s_instance == nullptr)
        {
            s_instance = new GameStart();
        }
        return s_instance;
    }
    
    GLchar                 preferPath[1024];
    
private:
    const GLchar *FullPath(const GLchar *fileName);
    GLchar  fullPath[1024];
    GLfloat deltaTime;

    GameStart()
    {
        //std::cout << "Construct Game" << std::endl;
    }
    
    ~GameStart()
    {
        //std::cout << "Destruct Game" << std::endl;
    }

    GameStart(const GameStart&);
    GameStart& operator =(const GameStart&);
    
    static GameStart *s_instance;
};


#endif /* game_start_hpp */
