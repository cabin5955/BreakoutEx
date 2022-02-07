//
//  sprite_renderer.hpp
//  LearnOpenGL_BreakOut
//
//  Created by chen caibin on 2021/9/25.
//

#ifndef sprite_renderer_hpp
#define sprite_renderer_hpp

#include "glad.h"
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>

#include "texture.hpp"
#include "shader.h"


class SpriteRenderer
{
public:
    // Constructor (inits shaders/shapes)
    SpriteRenderer(Shader &shader);
    // Destructor
    ~SpriteRenderer();
    // Renders a defined quad textured with given sprite
    void DrawSprite(Texture2D &texture, glm::vec2 position, glm::vec2 size = glm::vec2(10, 10), GLfloat rotate = 0.0f, glm::vec3 color = glm::vec3(1.0f));
    // Initializes and configures the quad's buffer and vertex attributes
    void initRenderData();
private:
    // Render state
    Shader shader;
    GLuint quadVAO;
};


#endif /* sprite_renderer_hpp */
