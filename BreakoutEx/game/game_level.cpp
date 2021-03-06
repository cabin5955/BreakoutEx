//
//  game_level.cpp
//  LearnOpenGL
//
//  Created by chen caibin on 2021/9/25.
//

#include "game_level.hpp"
#include <fstream>
#include <sstream>


void GameLevel::Load(const GLchar *file, GLuint levelWidth, GLuint levelHeight)
{
    // Clear old data
    this->Bricks.clear();
    // Load from file
    GLuint tileCode;
    GameLevel level;
    std::string line;
    std::ifstream fstream(file);
    std::vector<std::vector<GLuint>> tileData;
    if (fstream)
    {
        while (std::getline(fstream, line)) // Read each line from level file
        {
            std::istringstream sstream(line);
            std::vector<GLuint> row;
            while (sstream >> tileCode) // Read each word seperated by spaces
                row.push_back(tileCode);
            tileData.push_back(row);
        }
        
        if (tileData.size() > 0)
            this->init(tileData, levelWidth, levelHeight);
    }
}

void GameLevel::Draw(SpriteRenderer &renderer)
{
    for (GameObject &tile : this->Bricks)
        if (!tile.Destroyed)
            tile.Draw(renderer);
}

GLboolean GameLevel::IsCompleted()
{
    for (GameObject &tile : this->Bricks)
        if (!tile.IsSolid && !tile.Destroyed)
            return GL_FALSE;
    return GL_TRUE;
}

void GameLevel::init(std::vector<std::vector<GLuint>> tileData, GLuint levelWidth, GLuint levelHeight)
{
    // Calculate dimensions
    GLuint height = tileData.size();
    GLuint width = tileData[0].size(); // Note we can index vector at [0] since this function is only called if height > 0
    GLfloat unit_width = levelWidth / static_cast<GLfloat>(width), unit_height = levelHeight / height;
    // Initialize level tiles based on tileData
    for (GLuint y = 0; y < height; ++y)
    {
        for (GLuint x = 0; x < width; ++x)
        {
            // Check block type from level data (2D level array)
            if (tileData[y][x] == 1) // Solid
            {
                glm::vec2 pos(unit_width * x, unit_height * y + 42);
                glm::vec2 size(unit_width, unit_height);
                SpriteObject obj(pos, size, ResourceManager::GetTexture("block_solid"), {204,204,178,255});
                obj.IsSolid = GL_TRUE;
                this->Bricks.push_back(obj);
            }
            else if (tileData[y][x] > 1)    // Non-solid; now determine its color based on level data
            {
                Color color = WHITE; // original: white
                if (tileData[y][x] == 2)
                    color = {51,153,255,255};//glm::vec3(0.2f, 0.6f, 1.0f);
                else if (tileData[y][x] == 3)
                    color = {0,178,0,255};//glm::vec3(0.0f, 0.7f, 0.0f);
                else if (tileData[y][x] == 4)
                    color = {204,204,102,255};//glm::vec3(0.8f, 0.8f, 0.4f);
                else if (tileData[y][x] == 5)
                    color = {255,128,0,255};//glm::vec3(1.0f, 0.5f, 0.0f);

                glm::vec2 pos(unit_width * x, unit_height * y + 42);
                glm::vec2 size(unit_width, unit_height);
                this->Bricks.push_back(SpriteObject(pos, size, ResourceManager::GetTexture("block"), color));
            }
        }
    }
}
