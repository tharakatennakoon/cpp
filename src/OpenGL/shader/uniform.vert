#version 460 core

in layout (location = 0) vec3 pos;
in layout (location = 1) vec4 incolor;

layout (std140) uniform vertexData
{
    mat4 T;
    mat4 R;
    mat4 S;
};

out vec4 fragcolor;

void main()
{
    gl_Position = T * R * S * vec4(pos, 1.0);
    fragcolor = incolor;
}
