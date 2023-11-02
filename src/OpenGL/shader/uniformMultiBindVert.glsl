#version 460 core

in layout (location = 0) vec3 pos;
in layout (location = 1) vec2 TextCoord;

layout (std140, binding = 0) uniform Model
{
    mat4 model;
};

layout (std140, binding = 1) uniform ViewProjection
{
    mat4 view;
    mat4 projection;
};

out vec2 textCoord;

void main()
{
    gl_Position = projection * view * model * vec4(pos, 1.0);
    textCoord = TextCoord;
}
