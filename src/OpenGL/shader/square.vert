#version 460 core

in layout(location = 0) vec3 pos;
in layout(location = 1) vec4 incolor;
uniform mat4 mvp;

out vec4 fragcolor;

void main()
{
    gl_Position = mvp * vec4(pos, 1.0);
    fragcolor = incolor;
}