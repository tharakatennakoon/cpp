#include <iostream>
#include <glad/glad.h>
#include <gtc/type_ptr.hpp>
#include <GLFW/glfw3.h>
#include <fstream>
#include <gtc/matrix_transform.hpp>

#include <vector>
#include <tuple>

#include "include.h"

struct rs
{
    glm::mat4 R;
    glm::mat4 S;
};

struct t
{
    glm::mat4 t;
};

using RS = rs;
using T = t;

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
    std::string strVert = get_file_string("./shader/uniformMultiBind.vert");
    const GLchar *vertCStr = strVert.c_str();
    std::cout << strVert.c_str() << std::endl;

    std::string strFrag = get_file_string("./shader/uniformMultiBind.frag");
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

static std::tuple<std::vector<T>, std::vector<RS>> generateMvps()
{
    std::vector<RS> rss;
    std::vector<T> ts;

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
        RS rs{modelScale[i], modelRoate[i]};
        T t{modelTrans[i]};

        rss.push_back(rs);
        ts.push_back(t);
    }

    return std::make_tuple(ts, rss);
}

static std::tuple<std::vector<GLuint>, std::vector<GLuint>> configureUniformBuffer(GLuint shaderProgram, std::vector<RS> rss, std::vector<T> ts)
{
    std::vector<GLuint> ubos_rs;
    std::vector<GLuint> ubos_t;

    GLint blockSizeTranslateMat = 0;
    GLint ubiTranslateMat = glGetUniformBlockIndex(shaderProgram, "TranslateMat");
    glGetActiveUniformBlockiv(shaderProgram, ubiTranslateMat, GL_UNIFORM_BLOCK_DATA_SIZE, &blockSizeTranslateMat);

    std::cout << "ubiTranslateMat : " << ubiTranslateMat << ", size : " << blockSizeTranslateMat << std::endl;

    const GLchar *nameTranslateMat[] = {"T"};
    GLuint indicesTranslateMat[1];
    glGetUniformIndices(shaderProgram, 1, nameTranslateMat, indicesTranslateMat);

    GLint offsetTranslateMat[1];
    glGetActiveUniformsiv(shaderProgram, 1, indicesTranslateMat, GL_UNIFORM_OFFSET, offsetTranslateMat);

    for (int i = 0; i < 1; i++)
    {
        std::cout << "asttribute : " << nameTranslateMat[i] << ", index : " << indicesTranslateMat[i] << ", offset : " << offsetTranslateMat[i] << std::endl;
    }

    GLint blockSizeRotateScaleMat = 0;
    GLint ubiRotateScaleMat = glGetUniformBlockIndex(shaderProgram, "RotateScaleMat");
    glGetActiveUniformBlockiv(shaderProgram, ubiRotateScaleMat, GL_UNIFORM_BLOCK_DATA_SIZE, &blockSizeRotateScaleMat);

    std::cout << "ubiRotateScaleMat : " << ubiRotateScaleMat << ", size : " << blockSizeRotateScaleMat << std::endl;

    const GLchar *nameRotateScaleMat[] = {"R", "S"};
    GLuint indicesRotateScaleMat[2];
    glGetUniformIndices(shaderProgram, 2, nameRotateScaleMat, indicesRotateScaleMat);

    GLint offsetRotateScaleMat[2];
    glGetActiveUniformsiv(shaderProgram, 2, indicesRotateScaleMat, GL_UNIFORM_OFFSET, offsetRotateScaleMat);

    for (int i = 0; i < 1; i++)
    {
        std::cout << "asttribute : " << nameRotateScaleMat[i] << ", index : " << indicesRotateScaleMat[i] << ", offset : " << offsetRotateScaleMat[i] << std::endl;
    }

    for (int i = 0; i < 4; i++)
    {
        GLubyte *blockBufferTranslateMat = new GLubyte[blockSizeTranslateMat];
        GLubyte *blockBufferRotateScaleMat = new GLubyte[blockSizeRotateScaleMat];

        GLuint ubo_t;
        GLuint ubo_rs;

        memcpy(&blockBufferTranslateMat[offsetTranslateMat[0]], &ts[i].t, sizeof(ts[i].t));
        memcpy(&blockBufferRotateScaleMat[offsetRotateScaleMat[0]], &rss[i].R, sizeof(rss[i].R));
        memcpy(&blockBufferRotateScaleMat[offsetRotateScaleMat[1]], &rss[i].S, sizeof(rss[i].S));

        glCreateBuffers(1, &ubo_t);
        glBindBuffer(GL_UNIFORM_BUFFER, ubo_t);
        glBufferData(GL_UNIFORM_BUFFER, blockSizeTranslateMat, blockBufferTranslateMat, GL_STATIC_DRAW);
        glBindBuffer(GL_UNIFORM_BUFFER, 0);
        ubos_t.push_back(ubo_t);

        glCreateBuffers(1, &ubo_rs);
        glBindBuffer(GL_UNIFORM_BUFFER, ubo_rs);
        glBufferData(GL_UNIFORM_BUFFER, blockSizeRotateScaleMat, blockBufferRotateScaleMat, GL_STATIC_DRAW);
        glBindBuffer(GL_UNIFORM_BUFFER, 0);
        ubos_rs.push_back(ubo_rs);

        delete[] blockBufferTranslateMat;
        delete[] blockBufferRotateScaleMat;
    }

    return std::make_tuple(ubos_t, ubos_rs);
}

int DrawUniformBuffersMultiBind()
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

    // to turn off vsync - 0, turn on - 1
    glfwSwapInterval(1);

    gladLoadGL();
    glEnable(GL_DEPTH_TEST);

    GLuint vertexBufferObject = SquareModelVertex();
    GLuint indexBufferObject = suqareElementData();
    GLuint shaderProgram = createSquareShaderProgram();

    std::vector<RS> rss;
    std::vector<T> ts;

    auto mvp = generateMvps();
    ts = std::get<0>(mvp);
    rss = std::get<1>(mvp);

    std::vector<GLuint> ubos_t;
    std::vector<GLuint> ubos_rs;

    auto ubos = configureUniformBuffer(shaderProgram, rss, ts);
    ubos_t = std::get<0>(ubos);
    ubos_rs = std::get<1>(ubos);

    glUseProgram(shaderProgram);

    glClearColor(0.07f, 0.13f, 0.17f, 1.0f);

    GLfloat rot = 0;

    /* Loop until the user closes the window */
    while (!glfwWindowShouldClose(window))
    {
        /* Render here */
        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

        rot = (((GLint)rot + 1) % 360);
        glm::mat4 rotate = glm::rotate(glm::mat4(1.0f), glm::radians(rot), glm::vec3(0, 0, 1));

        for (int i = 0; i < 4; i++)
        {
            glm::mat4 rt = rotate * ts[i].t;

            glBindBuffer(GL_UNIFORM_BUFFER, ubos_t[i]);
            glBufferSubData(GL_UNIFORM_BUFFER, 0, sizeof(rt), &rt);
            glBindBuffer(GL_UNIFORM_BUFFER, 0);
            glBindBufferBase(GL_UNIFORM_BUFFER, 0, ubos_t[i]);

            glBindBufferBase(GL_UNIFORM_BUFFER, 1, ubos_rs[i]);

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
    glfwDestroyWindow(window);
    glfwTerminate();
    return 0;
}