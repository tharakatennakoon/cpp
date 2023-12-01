#version 460 core

layout(local_size_x = 32, local_size_y = 32, local_size_z = 1) in;
layout (binding = 0, rgba8) readonly uniform image2D inImage;
layout (binding = 1, rgba8) writeonly uniform image2D outImage;

void main()
{
    ivec2 texelCoords = ivec2(gl_GlobalInvocationID.xy);
    vec4 color = imageLoad(inImage, texelCoords);

    float gray = (color.r+color.g+color.b)/3.0;

    vec4 grayColor;

    float res = step(0.5, gray);
    grayColor = vec4(res);

    imageStore(outImage, texelCoords, grayColor);
}