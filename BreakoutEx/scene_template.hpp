//
//  scene_template.hpp
//  BreakoutEx
//
//  Created by chen caibin on 2022/1/6.
//

#ifndef scene_template_hpp
#define scene_template_hpp

#include "glad.h"
#include <vector>

#include "scene.h"
#include <string>

class SceneTemplate:public IScene
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
    
    static SceneTemplate* GetInstance()
    {
        if(s_instance == nullptr)
        {
            s_instance = new SceneTemplate();
        }
        return s_instance;
    }
    
private:

    SceneTemplate()
    {
        //std::cout << "Construct Game" << std::endl;
    }
    
    ~SceneTemplate()
    {
        //std::cout << "Destruct Game" << std::endl;
    }

    SceneTemplate(const SceneTemplate&);
    SceneTemplate& operator =(const SceneTemplate&);
    
    static SceneTemplate *s_instance;
};

#endif /* scene_template_hpp */
