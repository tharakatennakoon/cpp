#version 460 core

in vec2 textCoord;

out layout(location = 0) vec4 FragColor;

uniform sampler2D gSampler;

void main()
{
   FragColor = texture2D(gSampler, textCoord);
}