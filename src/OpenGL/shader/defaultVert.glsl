#version 460 core

in layout (location = 0) vec3 pos;
in layout (location = 1) vec2 TextCoord;

out vec2 textCoord;

void main()
{
    gl_Position = vec4(pos, 1.0);
    textCoord = TextCoord;
}
