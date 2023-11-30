#version 460 core

layout(local_size_x = 32, local_size_y = 32, local_size_z = 1) in;

layout (binding = 0, rgba8) readonly uniform image2D inImage;

layout (binding = 1, rgba8) writeonly uniform image2D outImage;

layout(std140, binding = 2) uniform imageData
{
    int w;
    int h;
    int c;
};

mat3 sx = mat3( +1.0, +2.0, +1.0,
                +0.0, +0.0, +0.0,
                -1.0, -2.0, -1.0);

mat3 sy = mat3( -1.0, +0.0, +1.0,
                -2.0, +0.0, +2.0,
                -1.0, +0.0, +1.0);

/*
    p00 p10 p20
    p01 p11 p21
    p02 p12 p22
*/

const highp vec3 waights = vec3(0.2125, 0.7154, 0.0721);

void main()
{
    uint posX = gl_GlobalInvocationID.x;
    uint posY = gl_GlobalInvocationID.y;

    if (w < posX || h < posY)
    {
        return;
    }

    ivec2 texelCoords = ivec2(gl_GlobalInvocationID.xy);

    mat3 grayColor = mat3(1.0);

    for (int y = -1; y < 2; y++)
    {
        for (int x = -1; x < 2; x++)
        {
            vec4 color = imageLoad(inImage, texelCoords + ivec2(x,y));
            grayColor[y+1][x+1] = dot(color.rgb, waights);
        }
    }

    float h = dot(grayColor[0], sx[0]) + dot(grayColor[1], sx[1]) + dot(grayColor[2], sx[2]);
    float v = dot(grayColor[0], sy[0]) + dot(grayColor[1], sy[1]) + dot(grayColor[2], sy[2]);

    float s = sqrt((v * v)+(h * h));

    vec4 grayOutColor = vec4(vec3(s), 1.0);

    imageStore(outImage, texelCoords, grayOutColor);
}