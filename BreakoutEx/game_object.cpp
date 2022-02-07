//
//  game_object.cpp
//  LearnOpenGL
//
//  Created by chen caibin on 2021/9/25.
//

#include "game_object.hpp"
GameObject::GameObject(): Position(0, 0, 0), Size(1, 1, 1), Velocity(0.0f), Color(1.0f),
                        Rotation(0.0f), Sprite(), IsSolid(false), Destroyed(false),RotationVelocity(0.0f)
{ }

GameObject::GameObject(glm::vec3 pos, glm::vec3 size, Texture2D sprite, glm::vec3 color,
                       glm::vec3 velocity,glm::vec3 rotationSpeed)
    : Position(pos), Size(size), Velocity(velocity), Color(color), Rotation(0.0f),
      Sprite(sprite),RotationVelocity(rotationSpeed), IsSolid(false), Destroyed(false) { }
