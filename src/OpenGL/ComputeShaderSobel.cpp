#include <iostream>
#include <glad/glad.h>
#include <gtc/type_ptr.hpp>
#include <GLFW/glfw3.h>
#include <fstream>
#include <gtc/matrix_transform.hpp>

#include <stb/stb_image.h>

#include <vector>
#include <tuple>

#include "include.h"

static float xPos = 0;
static float yPos = 0;
static float zPos = 100;

struct imageData
{
    GLint w;
    GLint h;
    GLint c;
};

static void DebugFunction(GLenum source, GLenum type, GLuint id, GLenum severity, GLsizei length, const GLchar *message, const void *userParam)
{

    std::cout << "Debug : ";
}

static std::string get_file_string(std::string filePath)
{
    std::ifstream ifs(filePath);
    return std::string((std::istreambuf_iterator<char>(ifs)),
                       (std::istreambuf_iterator<char>()));
}

static GLubyte* loadImageData(std::string filePath, int *width, int *height, int *bpp)
{
    std::cout << "\n====================== loadImageData ==================== " << std::endl;
    std::cout << "File Path : " << filePath << std::endl;

    stbi_set_flip_vertically_on_load(1);
    GLubyte* imageData = stbi_load(filePath.c_str(), width, height, bpp, 0);

    assert(imageData != nullptr);
    assert(*width > 0);
    assert(*height > 0);

    std::cout << "Width :" << *width << ", Height :" << *height << ", BPP : " << *bpp << std::endl;
    std::cout << "--------------------------------------------------------- " << std::endl;
    return imageData;
}

static void windowSizeCallback(GLFWwindow *window, int width, int height)
{
    glViewport(0, 0, width, height);
}

static void keyBoardCallback(GLFWwindow *windows, int key, int scancode, int action, int mode)
{
    if (key == 265 && action == 0 && yPos < 400)
    {
        yPos += 10;
    }
    else if (key == 264 && action == 0 && yPos > -400)
    {
        yPos -= 10;
    }
    else if (key == 263 && action == 0 && xPos > -400)
    {
        xPos -= 10;
    }
    else if (key == 262 && action == 0 && xPos < 400)
    {
        xPos += 10;
    }
    else if (key == 45 && action == 0 && zPos > -400)
    {
        zPos -= 10;
    }
    else if (key == 61 && action == 0 && zPos < 400)
    {
        zPos += 10;
    }

    std::cout << "xPos : " << xPos << ", yPos : " << yPos << ", zPos : " << zPos << std::endl;
}

static void checkShaderErrors(std::string type, GLuint shader)
{
    int isCompiled = 0;
    glGetShaderiv(shader, GL_COMPILE_STATUS, &isCompiled);
    if (isCompiled == GL_FALSE)
    {
        int maxLength = 0;
        glGetShaderiv(shader, GL_INFO_LOG_LENGTH, &maxLength);
        std::vector<GLchar> vInfoLog(maxLength);
        glGetShaderInfoLog(shader, maxLength, &maxLength, &vInfoLog[0]);
        glDeleteShader(shader);

        std::cout << "Unable to compile : " << type << " : Error : " << vInfoLog.data();
        assert(1);
    }
}

static GLuint createShaderProgram(GLuint shaderProgram, std::string vertexShaderPath, GLenum type)
{
    std::cout << "\n============== createSquareShaderProgram ============== " << std::endl;

    if (shaderProgram == 0)
    {
        shaderProgram = glCreateProgram();
    }

    std::string strVert = get_file_string(vertexShaderPath.c_str());
    const GLchar *vertCStr = strVert.c_str();
    std::cout << strVert.c_str() << std::endl;

    GLuint vertexShader = glCreateShader(type);
    glShaderSource(vertexShader, 1, &vertCStr, NULL);
    glCompileShader(vertexShader);
    checkShaderErrors("vertex", vertexShader);

    glAttachShader(shaderProgram, vertexShader);

    glLinkProgram(shaderProgram);

    GLint ret;
    glGetProgramiv(shaderProgram, GL_LINK_STATUS, &ret);
    if (ret == GL_FALSE)
    {
        GLchar info[512];
        GLsizei len;
        glGetProgramInfoLog(shaderProgram, 512, &len, info);
        std::cout << "shader program link error : " << info << std::endl;
        assert(ret);
    }

    glDeleteShader(vertexShader);

    std::cout << "--------------------------------------------------------- " << std::endl;
    return shaderProgram;
}

static GLuint createTexture(std::string filePath, int width, int height, GLenum internalFormat, GLenum format)
{
    GLuint tobj;
    glGenTextures(1, &tobj);
    glBindTexture(GL_TEXTURE_2D, tobj);

    int w = width;
    int h = height;
    int bpp = 0;
    GLenum f = format;

    GLubyte* data = NULL;

    if (!filePath.empty())
    {
        data = loadImageData(filePath, &w, &h, &bpp);
        f = bpp == 3 ? GL_RGB : GL_RGBA;
        glTexImage2D(GL_TEXTURE_2D, 0, internalFormat, w, h, 0, f, GL_UNSIGNED_BYTE, data);
    }
    else
    {
        glTexStorage2D(GL_TEXTURE_2D, 1, internalFormat, w, h);
    }

    glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
    glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
    glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
    glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);

    glBindTexture(GL_TEXTURE_2D, 0);

    stbi_image_free(data);

    return tobj;
}

static GLuint configureUniformBuffer(GLuint shaderProgram, int w, int h, int c, GLuint ubBinding)
{
    std::cout << "\n================= configureUniformBuffer ================ " << std::endl;

    imageData im = {w, h, c};

    GLuint ubObj;
    glCreateBuffers(1, &ubObj);
    glBindBuffer(GL_UNIFORM_BUFFER, ubObj);
    glBindBufferBase(GL_UNIFORM_BUFFER, ubBinding, ubObj);
    glBufferData(GL_UNIFORM_BUFFER, sizeof(im), &im, GL_DYNAMIC_COPY);

    glBindBuffer(GL_UNIFORM_BUFFER, 0);

    return ubObj;
}

static GLuint createStorageBuffer(std::string filePath, int width, int height, int channels, GLuint bindingIndex)
{
    GLuint bobj;
    glGenBuffers(1, &bobj);
    glBindBuffer(GL_SHADER_STORAGE_BUFFER, bobj);
    glBindBufferBase(GL_SHADER_STORAGE_BUFFER, bindingIndex, bobj);

    int w = width;
    int h = height;
    int c = 0;

    GLubyte* data = NULL;

    if (!filePath.empty())
    {
        data = loadImageData(filePath, &w, &h, &c);

        glBufferData(GL_SHADER_STORAGE_BUFFER, w * h * c, data, GL_STATIC_DRAW);
        stbi_image_free(data);
    }
    else
    {
        glBufferData(GL_SHADER_STORAGE_BUFFER, w * h * c, NULL, GL_DYNAMIC_COPY);
    }

    glBindBuffer(GL_SHADER_STORAGE_BUFFER, 0);

    return bobj;
}

static GLuint GenerateModelVertex()
{
    GLfloat verts[] = {
        // Location XYZ      Texture coord x,y
        -1.0f, +1.0f, +0.0f, +0.0f, +1.0f,
        +1.0f, +1.0f, +0.0f, +1.0f, +1.0f,
        +1.0f, -1.0f, +0.0f, +1.0f, +0.0f,
        -1.0f, -1.0f, +0.0f, +0.0f, +0.0f};

    GLuint vertexBufferObject;
    glGenBuffers(1, &vertexBufferObject);
    glBindBuffer(GL_ARRAY_BUFFER, vertexBufferObject);
    glBufferData(GL_ARRAY_BUFFER, sizeof(verts), verts, GL_STATIC_DRAW);

    glEnableVertexAttribArray(0);
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 5 * sizeof(GLfloat), (void *)0);

    glEnableVertexAttribArray(1);
    glVertexAttribPointer(1, 2, GL_FLOAT, GL_FALSE, 5 * sizeof(GLfloat), (void *)(sizeof(GLfloat) * 3));

    return vertexBufferObject;
}

static GLuint suqareElementData()
{
    GLushort indices[] = {0, 1, 2, 2, 3, 0};
    GLuint indexBufferObject;
    glGenBuffers(1, &indexBufferObject);
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, indexBufferObject);
    glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(indices), indices, GL_STATIC_DRAW);

    return indexBufferObject;
}

int DrawSobel()
{
    std::cout << "Hello Uniform Buffers" << std::endl;

    GLFWwindow *window;

    /* Initialize the library */
    if (!glfwInit())
        return -1;

    /* Create a windowed mode window and its OpenGL context */
    window = glfwCreateWindow(640, 640, "OpenGL Square", NULL, NULL);
    if (!window)
    {
        glfwTerminate();
        return -1;
    }

    /* Make the window's context current */
    glfwMakeContextCurrent(window);
    glfwSetWindowSizeCallback(window, windowSizeCallback);
    glfwSetKeyCallback(window, keyBoardCallback);

    // to turn off vsync - 0, turn on - 1
    glfwSwapInterval(1);

    gladLoadGL();
    glEnable(GL_DEPTH_TEST);

    GLuint vertexBufferObject = GenerateModelVertex();
    GLuint indexBufferObject = suqareElementData();
    GLuint shaderProgramScreen = createShaderProgram(0, "./shader/defaultVert.glsl", GL_VERTEX_SHADER);
    shaderProgramScreen = createShaderProgram(shaderProgramScreen, "./shader/defaultFrag.glsl", GL_FRAGMENT_SHADER);

    int maxWorkGroupSizes[3];
    glGetIntegeri_v(GL_MAX_COMPUTE_WORK_GROUP_SIZE, 0, &maxWorkGroupSizes[0]);
    glGetIntegeri_v(GL_MAX_COMPUTE_WORK_GROUP_SIZE, 1, &maxWorkGroupSizes[1]);
    glGetIntegeri_v(GL_MAX_COMPUTE_WORK_GROUP_SIZE, 2, &maxWorkGroupSizes[2]);

    std::cout << "maxGroup x: " << maxWorkGroupSizes[0] << ", y: " << maxWorkGroupSizes[1] << ", z: " << maxWorkGroupSizes[2] << std::endl;

    GLuint computeShader = createShaderProgram(0, "./shader/Sobel.glsl", GL_COMPUTE_SHADER); 
    GLuint texture = createTexture("./res/lena.png", 0, 0, GL_RGBA8, GL_RGBA8);
    GLuint ub = configureUniformBuffer(computeShader, 512, 512, 3, 2);
    GLuint outputTexture = createTexture("", 512, 512, GL_RGBA8, GL_RGBA8);

   /* Loop until the user closes the window */
    while (!glfwWindowShouldClose(window))
    {
        glBindBufferBase(GL_UNIFORM_BUFFER, 2, ub);
        glBindBuffer(GL_UNIFORM_BUFFER, ub);

        glBindImageTexture(0, texture, 0, GL_FALSE, 0, GL_READ_ONLY, GL_RGBA8);

        glBindImageTexture(1, outputTexture, 0, GL_FALSE, 0, GL_WRITE_ONLY, GL_RGBA8);

        glUseProgram(computeShader);
        glDispatchCompute(512/32, 512/32, 1);
        glMemoryBarrier(GL_SHADER_IMAGE_ACCESS_BARRIER_BIT);

        glBindFramebuffer(GL_FRAMEBUFFER, 0);

        glClearColor(1.0f, 1.0f, 1.0f, 1.0f);
        glClear(GL_COLOR_BUFFER_BIT);

        glUseProgram(shaderProgramScreen);
        glDisable(GL_DEPTH_TEST);
        glActiveTexture(GL_TEXTURE0);
        glBindTexture(GL_TEXTURE_2D, outputTexture);
        glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_SHORT, 0);

        /* Swap front and back buffers */
        glfwSwapBuffers(window);

        /* Poll for and process events */
        glfwPollEvents();
    }

    glDeleteBuffers(1, &vertexBufferObject);
    glDeleteBuffers(1, &indexBufferObject);
    glDeleteTextures(1, &texture);
    glDeleteTextures(1, &outputTexture);
    glDeleteProgram(shaderProgramScreen);
    glDeleteProgram(computeShader);
    glfwDestroyWindow(window);
    glfwTerminate();
    return 0;
}
