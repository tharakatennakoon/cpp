#include <iostream>
#include <glad/glad.h>
#include <gtc/type_ptr.hpp>
#include <GLFW/glfw3.h>
#include <fstream>
#include <gtc/matrix_transform.hpp>

#include <vector>
#include <tuple>

#include "include.h"

struct ViewProjection
{
    glm::mat4 view;
    glm::mat4 projection;
};

struct Model
{
    glm::mat4 model;
};

static float xPos = 0;
static float yPos = 0;
static float zPos = 100;

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
        +1.0f, +1.0f, +0.0f, +0.0f, +1.0f, +0.0f, +1.0f,
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

static std::vector<Model> generateModelMat()
{
    std::vector<Model> ms;

    glm::mat4 modelTrans[5] = {glm::translate(glm::mat4(1.0f), glm::vec3(+100.0f, +100.0f, -100.0f)),
                               glm::translate(glm::mat4(1.0f), glm::vec3(+100.0f, -100.0f, -050.0f)),
                               glm::translate(glm::mat4(1.0f), glm::vec3(-100.0f, -100.0f, +050.0f)),
                               glm::translate(glm::mat4(1.0f), glm::vec3(-100.0f, +100.0f, +100.0f)),
                               glm::translate(glm::mat4(1.0f), glm::vec3(+000.0f, +000.0f, +000.0f))};

    glm::mat4 modelScale[] = {glm::scale(glm::mat4(1.0f), glm::vec3(20.0f)),
                              glm::scale(glm::mat4(1.0f), glm::vec3(20.0f)),
                              glm::scale(glm::mat4(1.0f), glm::vec3(20.0f)),
                              glm::scale(glm::mat4(1.0f), glm::vec3(20.0f)),
                              glm::scale(glm::mat4(1.0f), glm::vec3(20.0f))};

    glm::mat4 modelRoate[] = {glm::rotate(glm::mat4(1.0f), glm::radians(15.0f), glm::vec3(0, 0, 1)),
                              glm::rotate(glm::mat4(1.0f), glm::radians(30.0f), glm::vec3(0, 0, 1)),
                              glm::rotate(glm::mat4(1.0f), glm::radians(15.0f), glm::vec3(0, 1, 0)),
                              glm::rotate(glm::mat4(1.0f), glm::radians(30.0f), glm::vec3(0, 1, 0)),
                              glm::rotate(glm::mat4(1.0f), glm::radians(00.0f), glm::vec3(0, 0, 1))};

    for (int i = 0; i < modelTrans->length() + 1; i++)
    {
        Model m{modelTrans[i] * modelRoate[i] * modelScale[i]};
        ms.push_back(m);
    }

    std::cout << "Model Count : " << ms.size() << std::endl;

    return ms;
}

static std::tuple<std::vector<GLuint>, GLuint> configureUniformBuffer(GLuint shaderProgram, std::vector<Model> ms)
{
    std::vector<GLuint> ubos_vp;
    std::vector<GLuint> ubos_m;

    GLint blockSizeModel = 0;
    GLint ubiModelMat = glGetUniformBlockIndex(shaderProgram, "Model");
    glGetActiveUniformBlockiv(shaderProgram, ubiModelMat, GL_UNIFORM_BLOCK_DATA_SIZE, &blockSizeModel);

    std::cout << "ubiModelMat : " << ubiModelMat << ", size : " << blockSizeModel << std::endl;

    const GLchar *nameModelMat[] = {"model"};
    GLuint indicesModelMat[1];
    glGetUniformIndices(shaderProgram, 1, nameModelMat, indicesModelMat);

    GLint offsetModelMat[1];
    glGetActiveUniformsiv(shaderProgram, 1, indicesModelMat, GL_UNIFORM_OFFSET, offsetModelMat);

    for (int i = 0; i < 1; i++)
    {
        std::cout << "asttribute : " << nameModelMat[i] << ", index : " << indicesModelMat[i] << ", offset : " << offsetModelMat[i] << std::endl;
    }

    GLint blockSizeViewProjectionMat = 0;
    GLint ubiViewProjectionMat = glGetUniformBlockIndex(shaderProgram, "ViewProjection");
    glGetActiveUniformBlockiv(shaderProgram, ubiViewProjectionMat, GL_UNIFORM_BLOCK_DATA_SIZE, &blockSizeViewProjectionMat);

    std::cout << "ubiViewProjectionMat : " << ubiViewProjectionMat << ", size : " << blockSizeViewProjectionMat << std::endl;

    const GLchar *nameViewProjectionMat[] = {"view", "projection"};
    GLuint indicesViewProjectionMat[2];
    glGetUniformIndices(shaderProgram, 2, nameViewProjectionMat, indicesViewProjectionMat);

    GLint offsetViewProjection[2];
    glGetActiveUniformsiv(shaderProgram, 2, indicesViewProjectionMat, GL_UNIFORM_OFFSET, offsetViewProjection);

    for (int i = 0; i < 1; i++)
    {
        std::cout << "asttribute : " << nameViewProjectionMat[i] << ", index : " << indicesViewProjectionMat[i] << ", offset : " << offsetViewProjection[i] << std::endl;
    }

    for (int i = 0; i < ms.size(); i++)
    {
        GLuint ubo_m;
        GLubyte *blockBufferModelMat = new GLubyte[blockSizeModel];

        memcpy(&blockBufferModelMat[offsetModelMat[0]], &ms[i].model, sizeof(ms[i].model));

        glCreateBuffers(1, &ubo_m);
        glBindBuffer(GL_UNIFORM_BUFFER, ubo_m);
        glBufferData(GL_UNIFORM_BUFFER, blockSizeModel, blockBufferModelMat, GL_STATIC_DRAW);
        glBindBuffer(GL_UNIFORM_BUFFER, 0);
        ubos_m.push_back(ubo_m);

        delete[] blockBufferModelMat;
    }

    GLuint ubo_vp;
    ViewProjection vp{glm::mat4(1.0f), glm::mat4(1.0f)};
    GLubyte *blockBufferViewProjectionMat = new GLubyte[blockSizeViewProjectionMat];
    memcpy(&blockBufferViewProjectionMat[offsetViewProjection[0]], &vp, sizeof(vp));

    glCreateBuffers(1, &ubo_vp);
    glBindBuffer(GL_UNIFORM_BUFFER, ubo_vp);
    glBufferData(GL_UNIFORM_BUFFER, blockSizeViewProjectionMat, blockBufferViewProjectionMat, GL_STATIC_DRAW);
    glBindBuffer(GL_UNIFORM_BUFFER, 0);

    delete[] blockBufferViewProjectionMat;

    return std::make_tuple(ubos_m, ubo_vp);
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
    glfwSetKeyCallback(window, keyBoardCallback);

    // to turn off vsync - 0, turn on - 1
    glfwSwapInterval(1);

    gladLoadGL();
    glEnable(GL_DEPTH_TEST);

    GLuint vertexBufferObject = SquareModelVertex();
    GLuint indexBufferObject = suqareElementData();
    GLuint shaderProgram = createSquareShaderProgram();

    std::vector<Model> ms;

    ms = generateModelMat();

    auto ubos = configureUniformBuffer(shaderProgram, ms);
    std::vector<GLuint> ubos_m = std::get<0>(ubos);
    GLuint ubo_vp = std::get<1>(ubos);

    glUseProgram(shaderProgram);

    glClearColor(0.07f, 0.13f, 0.17f, 1.0f);

    GLfloat rot = 0;

    glBindBufferBase(GL_UNIFORM_BUFFER, 1, ubo_vp);

    /* Loop until the user closes the window */
    while (!glfwWindowShouldClose(window))
    {
        /* Render here */
        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

        rot = (((GLint)rot + 1) % 360);
        glm::mat4 rotateTrans = glm::rotate(glm::mat4(1.0f), glm::radians(rot), glm::vec3(0, 0, 1));
        glm::mat4 rotateObject = glm::rotate(glm::mat4(1.0f), glm::radians(rot), glm::vec3(0, 1, 0));

        ViewProjection vp;
        vp.view = glm::inverse(glm::translate(glm::mat4(1.0f), glm::vec3(xPos, yPos, zPos)));
        vp.projection = glm::ortho(-200.0f, 200.0f, -200.0f, 200.0f, 0.0f, 300.0f);

        glBindBuffer(GL_UNIFORM_BUFFER, ubo_vp);
        glBufferSubData(GL_UNIFORM_BUFFER, 0, sizeof(vp), &vp);
        glBindBuffer(GL_UNIFORM_BUFFER, 0);

        for (int i = 0; i < ubos_m.size(); i++)
        {
            glm::mat4 rt = rotateTrans * ms[i].model * rotateObject;

            glBindBuffer(GL_UNIFORM_BUFFER, ubos_m[i]);
            glBufferSubData(GL_UNIFORM_BUFFER, 0, sizeof(rt), &rt);
            glBindBuffer(GL_UNIFORM_BUFFER, 0);
            glBindBufferBase(GL_UNIFORM_BUFFER, 0, ubos_m[i]);

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