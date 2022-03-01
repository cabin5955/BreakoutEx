//
//  game_over.hpp
//  BreakoutEx
//
//  Created by chen caibin on 2022/1/10.
//

#ifndef game_over_hpp
#define game_over_hpp

#include "glad.h"
#include <vector>

#include "scene.h"
#include <string>

class GameOver:public IScene
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
    
    static GameOver* GetInstance()
    {
        if(s_instance == nullptr)
        {
            s_instance = new GameOver();
        }
        return s_instance;
    }
    GLchar                 preferPath[1024];
    
private:
    const GLchar *FullPath(const GLchar *fileName);
    GLchar  fullPath[1024];
    GLfloat deltaTime;
    
    GameOver()
    {
        //std::cout << "Construct Game" << std::endl;
    }
    
    ~GameOver()
    {
        //std::cout << "Destruct Game" << std::endl;
    }

    GameOver(const GameOver&);
    GameOver& operator =(const GameOver&);
    
    static GameOver *s_instance;
};

#endif /* game_over_hpp */
