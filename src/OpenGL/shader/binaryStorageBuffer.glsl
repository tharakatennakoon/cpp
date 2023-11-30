#version 460 core

layout(local_size_x = 32, local_size_y = 32, local_size_z = 1) in;

layout(std430, binding = 0) readonly buffer inImage {
    uint data[];
};

layout (binding = 1, rgba8) writeonly uniform image2D outImage;

layout(std140, binding = 2) uniform imageData
{
    int w;
    int h;
    int c;
};

void main()
{
    ivec2 texelCoords = ivec2(gl_GlobalInvocationID.xy);
    uint posX = gl_GlobalInvocationID.x;
    uint posY = gl_GlobalInvocationID.y;

    uint pos = posY * w + posX;
    vec4 rgba = unpackUnorm4x8(data[pos]);

    imageStore(outImage, texelCoords, rgba);
}