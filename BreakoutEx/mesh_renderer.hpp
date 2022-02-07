//
//  MeshRenderer.hpp
//  LearnOpenGL_BreakOut
//
//  Created by chen caibin on 2021/10/7.
//

#ifndef MeshRenderer_hpp
#define MeshRenderer_hpp

#include "glad.h"
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>

#include "texture.hpp"
#include "shader.h"

class MeshRenderer
{
public:
    // Constructor (inits shaders/shapes)
    MeshRenderer(Shader &shader,float vertics[],size_t vsize,
                 float texcoords[],size_t tsize,float normals[],size_t nsize);
    // Destructor
    ~MeshRenderer();
    // Renders a defined quad textured with given sprite
    void DrawMesh(Texture2D &texture, glm::vec3 position, glm::vec3 size = glm::vec3(1, 1, 1),
                  GLfloat angle = 0.0f, glm::vec3 axis = glm::vec3(0, 0, 1.0f),
                  glm::vec3 color = glm::vec3(1.0f));
    
    void DrawMesh(Texture2D &texture, glm::vec3 position,
                  glm::vec3 size = glm::vec3(1, 1, 1),
                  glm::quat q = glm::quat(1.f,0.0f,0.0f,0.0f),
                  glm::vec3 color = glm::vec3(1.0f));
private:
    // Render state
    Shader shader;
    GLuint meshVAO;
    GLuint verticsSize;
};

#endif /* MeshRenderer_hpp */
