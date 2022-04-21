#version 300 es

// Input vertex attributes
layout (location = 0) in vec3 aPos;
layout (location = 1) in vec3 aNormal;
layout (location = 2) in vec2 aTexCoords;

uniform mat4 model;
uniform mat4 view;
uniform mat4 projection;

// Output vertex attributes (to fragment shader)
out vec3 fragPosition;
out vec2 fragTexCoord;
out vec3 fragNormal;

// NOTE: Add here your custom variables

void main()
{
    // Send vertex attributes to fragment shader
    fragPosition = vec3(model * vec4(aPos, 1.0));;
    fragTexCoord = aTexCoords;
    fragNormal = aNormal;

    // Calculate final vertex position
    gl_Position = projection * view * model * vec4(aPos, 1.0);
}
