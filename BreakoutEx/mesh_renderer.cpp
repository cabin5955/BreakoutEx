//
//  MeshRenderer.cpp
//  LearnOpenGL_BreakOut
//
//  Created by chen caibin on 2021/10/7.
//

#include "mesh_renderer.hpp"

MeshRenderer::MeshRenderer(Shader &shader,float *vertics,size_t vSize,
                           float *texcoords,size_t tSize,float *normals,size_t nSize)
{
    this->shader = shader;
    unsigned int shipVBO;
    glGenVertexArrays(1, &this->meshVAO);
    glGenBuffers(1, &shipVBO);
    glBindVertexArray(this->meshVAO);
    
    glBindBuffer(GL_ARRAY_BUFFER, shipVBO);
    glBufferData(GL_ARRAY_BUFFER,vSize+nSize+tSize,nullptr,GL_STATIC_DRAW);
    glBufferSubData(GL_ARRAY_BUFFER, 0, vSize, vertics);
    glBufferSubData(GL_ARRAY_BUFFER, vSize, nSize, normals);
    glBufferSubData(GL_ARRAY_BUFFER, vSize+nSize, tSize, texcoords);

    glEnableVertexAttribArray(0);
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3*sizeof(float), 0);
    glEnableVertexAttribArray(1);
    glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 3*sizeof(float), (GLvoid*)vSize);
    glEnableVertexAttribArray(2);
    glVertexAttribPointer(2, 2, GL_FLOAT, GL_FALSE, 2*sizeof(float),
                          (GLvoid*)(vSize+nSize));

    glBindVertexArray(0);
    glBindBuffer(GL_ARRAY_BUFFER, 0);
    
    this->verticsSize = (GLuint)vSize;
}

MeshRenderer::~MeshRenderer()
{
    glDeleteVertexArrays(1, &this->meshVAO);
}

void MeshRenderer::DrawMesh(Texture2D &texture, glm::vec3 position,
              glm::vec3 size, glm::quat q, glm::vec3 color)
{
    // Prepare transformations
    this->shader.use();
    glm::mat4 model = glm::mat4(1.0f);
    model = glm::translate(model, position);  // First translate (transformations are: scale happens first, then rotation and then finall translation happens; reversed order)
    model *= glm::mat4_cast(q);
    model = glm::scale(model, size); // Last scale

    this->shader.setMat4("model", model);
    glActiveTexture(GL_TEXTURE0);
    texture.Bind();

    glBindVertexArray(this->meshVAO);
    glDrawArrays(GL_TRIANGLES, 0, this->verticsSize/(sizeof(float)*3));
    glBindVertexArray(0);
}

void MeshRenderer::DrawMesh(Texture2D &texture, glm::vec3 position, glm::vec3 size,
                            GLfloat rotation, glm::vec3 axis, glm::vec3 color)
{
//    glm::quat quat = glm::angleAxis(rotation, axis);
//    this->DrawMesh(texture, position, size, quat, color);
    
    // Prepare transformations
    this->shader.use();
    glm::mat4 model = glm::mat4(1.0f);;
    model = glm::translate(model, position);  // First translate (transformations are: scale happens first, then rotation and then finall translation happens; reversed order)

    //model = glm::translate(model, glm::vec3(0.5f * size.x, 0.5f * size.y, 0.0f)); // Move origin of rotation to center of quad
    model = glm::rotate(model, rotation, axis); // Then rotate
    //model = glm::translate(model, glm::vec3(-0.5f * size.x, -0.5f * size.y, 0.0f)); // Move origin back

    model = glm::scale(model, size); // Last scale

    this->shader.setMat4("model", model);
    glActiveTexture(GL_TEXTURE0);
    texture.Bind();

    glBindVertexArray(this->meshVAO);
    glDrawArrays(GL_TRIANGLES, 0, this->verticsSize/(sizeof(float)*3));
    glBindVertexArray(0);
}
