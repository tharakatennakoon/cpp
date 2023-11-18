#include <iostream>
#include <glad/glad.h>
#include <gtc/type_ptr.hpp>
#include <GLFW/glfw3.h>
#include <fstream>
#include <gtc/matrix_transform.hpp>

#include <vector>

#include "include.h"

struct mvp
{
    glm::mat4 T;
    glm::mat4 R;
    glm::mat4 S;
};

using MVP = mvp;

static std::string get_file_string(std::string filePath)
{
    std::ifstream ifs(filePath);
    return std::string((std::istreambuf_iterator<char>(ifs)),
                       (std::istreambuf_iterator<char>()));
}

static void windowSizeCallback(GLFWwindow *window, int width, int height)
{
    glViewport(0, 0, width, height);
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

static GLuint createSquareShaderProgram()
{
    std::string strVert = get_file_string("./shader/uniform.vert");
    const GLchar *vertCStr = strVert.c_str();
    std::cout << strVert.c_str() << std::endl;

    std::string strFrag = get_file_string("./shader/uniform.frag");
    const GLchar *fragCStr = strFrag.c_str();
    std::cout << strFrag.c_str() << std::endl;

    GLuint vertexShader = glCreateShader(GL_VERTEX_SHADER);
    glShaderSource(vertexShader, 1, &vertCStr, NULL);
    glCompileShader(vertexShader);
    checkShaderErrors("vertex", vertexShader);

    GLuint fragmentShader = glCreateShader(GL_FRAGMENT_SHADER);
    glShaderSource(fragmentShader, 1, &fragCStr, NULL);
    glCompileShader(fragmentShader);
    checkShaderErrors("fragment", fragmentShader);

    GLuint shaderProgram = glCreateProgram();
    glAttachShader(shaderProgram, vertexShader);
    glAttachShader(shaderProgram, fragmentShader);
    glLinkProgram(shaderProgram);

    glDeleteShader(vertexShader);
    glDeleteShader(fragmentShader);

    return shaderProgram;
}

static GLuint SquareModelVertex()
{
    GLfloat verts[] = {
        // Location XYZ      Color RGBA
        -1.0f, +1.0f, +0.0f, +1.0f, +0.0f, +0.0f, +1.0f,
        +1.0f, +1.0f, -1.0f, +0.0f, +1.0f, +0.0f, +1.0f,
        +1.0f, -1.0f, +0.0f, +0.0f, +0.0f, +1.0f, +1.0f,
        -1.0f, -1.0f, +0.0f, +1.0f, +1.0f, +0.0f, +1.0f};

    GLuint vertexBufferObject;
    glGenBuffers(1, &vertexBufferObject);
    glBindBuffer(GL_ARRAY_BUFFER, vertexBufferObject);
    glBufferData(GL_ARRAY_BUFFER, sizeof(verts), verts, GL_STATIC_DRAW);

    glEnableVertexAttribArray(0);
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 7 * sizeof(GLfloat), (void *)0);

    glEnableVertexAttribArray(1);
    glVertexAttribPointer(1, 4, GL_FLOAT, GL_FALSE, 7 * sizeof(GLfloat), (void *)(sizeof(GLfloat) * 3));

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

static void DebugFunction(GLenum source, GLenum type, GLuint id, GLenum severity, GLsizei length, const GLchar *message, const void *userParam)
{

    std::cout << "Debug : ";
}

static std::vector<MVP> generateMvps()
{
    std::vector<MVP> mvps;

    glm::mat4 modelTrans[4] = {glm::translate(glm::mat4(1.0f), glm::vec3(+0.5f, +0.5f, 0.0f)),
                               glm::translate(glm::mat4(1.0f), glm::vec3(+0.5f, -0.5f, 0.0f)),
                               glm::translate(glm::mat4(1.0f), glm::vec3(-0.5f, -0.5f, 0.0f)),
                               glm::translate(glm::mat4(1.0f), glm::vec3(-0.5f, +0.5f, 0.0f))};

    glm::mat4 modelScale[4] = {glm::scale(glm::mat4(1.0f), glm::vec3(0.1f)),
                               glm::scale(glm::mat4(1.0f), glm::vec3(0.15f)),
                               glm::scale(glm::mat4(1.0f), glm::vec3(0.2f)),
                               glm::scale(glm::mat4(1.0f), glm::vec3(0.25f))};

    glm::mat4 modelRoate[4] = {glm::rotate(glm::mat4(1.0f), glm::radians(00.0f), glm::vec3(0, 0, 1)),
                               glm::rotate(glm::mat4(1.0f), glm::radians(15.0f), glm::vec3(0, 0, 1)),
                               glm::rotate(glm::mat4(1.0f), glm::radians(30.0f), glm::vec3(0, 0, 1)),
                               glm::rotate(glm::mat4(1.0f), glm::radians(45.0f), glm::vec3(0, 0, 1))};

    for (int i = 0; i < 4; i++)
    {
        MVP mvp{modelTrans[i], modelScale[i], modelRoate[i]};
        mvps.push_back(mvp);
    }

    return mvps;
}

static std::vector<GLuint> configureUniforBuffer(GLuint shaderProgram, std::vector<MVP> mvps)
{
    std::vector<GLuint> ubos;

    GLint blockSize = 0;
    GLint ubi = glGetUniformBlockIndex(shaderProgram, "vertexData");
    glGetActiveUniformBlockiv(shaderProgram, ubi, GL_UNIFORM_BLOCK_DATA_SIZE, &blockSize);

    std::cout << "ubi : " << ubi << ", size : " << blockSize << std::endl;

    const GLchar *names[] = {"T", "R", "S"};
    GLuint indices[3];
    glGetUniformIndices(shaderProgram, 3, names, indices);

    GLint offset[3];
    glGetActiveUniformsiv(shaderProgram, 3, indices, GL_UNIFORM_OFFSET, offset);

    for (int i = 0; i < 3; i++)
    {
        std::cout << "asttribute : " << names[i] << ", index : " << indices[i] << ", offset : " << offset[i] << std::endl;
    }

    for (int i = 0; i < 4; i++)
    {
        GLubyte *blockBuffer = new GLubyte[blockSize];
        GLuint ubo;

        memcpy(&blockBuffer[offset[0]], &mvps[i].T, sizeof(mvps[i].T));
        memcpy(&blockBuffer[offset[1]], &mvps[i].R, sizeof(mvps[i].R));
        memcpy(&blockBuffer[offset[2]], &mvps[i].S, sizeof(mvps[i].S));

        glCreateBuffers(1, &ubo);
        glBindBuffer(GL_UNIFORM_BUFFER, ubo);
        glBufferData(GL_UNIFORM_BUFFER, blockSize, blockBuffer, GL_STATIC_DRAW);
        glBindBuffer(GL_UNIFORM_BUFFER, 0);

        ubos.push_back(ubo);

        delete[] blockBuffer;
    }

    return ubos;
}

int DrawUniformBuffers()
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

    gladLoadGL();
    glEnable(GL_DEPTH_TEST);

    GLuint vertexBufferObject = SquareModelVertex();
    GLuint indexBufferObject = suqareElementData();
    GLuint shaderProgram = createSquareShaderProgram();

    std::vector<MVP> mvps = generateMvps();
    std::vector<GLuint> ubos = configureUniforBuffer(shaderProgram, mvps);

    glUseProgram(shaderProgram);

    glClearColor(0.07f, 0.13f, 0.17f, 1.0f);

    GLuint fbo;
    glGenFramebuffers(1, &fbo);
    glBindFramebuffer(GL_FRAMEBUFFER, fbo);

    /* Loop until the user closes the window */
    while (!glfwWindowShouldClose(window))
    {
        /* Render here */
        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

        for (GLint ubo : ubos)
        {
            glBindBufferBase(GL_UNIFORM_BUFFER, 0, ubo);
            glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_SHORT, 0);
        }

        /* Swap front and back buffers */
        glfwSwapBuffers(window);

        /* Poll for and process events */
        glfwPollEvents();
    }

    glDeleteBuffers(1, &vertexBufferObject);
    glDeleteBuffers(1, &indexBufferObject);
    glDeleteProgram(shaderProgram);
    glDeleteFramebuffers(1, &fbo);
    glfwDestroyWindow(window);
    glfwTerminate();
    return 0;
}