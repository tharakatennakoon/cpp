#include <iostream>
#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include <fstream>
#include "include.h"

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

GLuint createTriangleShaderProgram()
{
    std::string strVert = get_file_string("./shader/triangle.vert");
    const GLchar *vertCStr = strVert.c_str();
    std::cout << strVert.c_str() << std::endl;

    std::string strFrag = get_file_string("./shader/triangle.frag");
    const GLchar *fragCStr = strFrag.c_str();
    std::cout << strFrag.c_str() << std::endl;

    GLuint vertexShader = glCreateShader(GL_VERTEX_SHADER);
    glShaderSource(vertexShader, 1, &vertCStr, NULL);
    glCompileShader(vertexShader);

    GLuint fragmentShader = glCreateShader(GL_FRAGMENT_SHADER);
    glShaderSource(fragmentShader, 1, &fragCStr, NULL);
    glCompileShader(fragmentShader);

    GLuint shaderProgram = glCreateProgram();
    glAttachShader(shaderProgram, vertexShader);
    glAttachShader(shaderProgram, fragmentShader);
    glLinkProgram(shaderProgram);

    glDeleteShader(vertexShader);
    glDeleteShader(fragmentShader);

    return shaderProgram;
}

GLuint copyTriangleVertexDataToGPU()
{
    constexpr float first_trianlge_depth = 0.5;
    constexpr float second_trianlge_depth = -0.5;

    GLfloat verts[] = {
        +0.0f, +1.0f, -1,          // Location XYZ
        +1.0f, +0.0f, 0.0f, +1.0f, // Color RGBA
        -1.0f, -1.0f, first_trianlge_depth,
        +0.0f, +1.0f, 0.0f, +1.0f,
        +1.0f, -1.0f, first_trianlge_depth,
        +0.0f, +0.0f, 1.0f, +1.0f,

        -1.0f, +1.0f, second_trianlge_depth, // Location XYZ
        +1.0f, +1.0f, 0.0f, +1.0f,           // Color RGBA
        +0.0f, -1.0f, second_trianlge_depth,
        +1.0f, +0.0f, 1.0f, +1.0f,
        +1.0f, +1.0f, second_trianlge_depth,
        +0.0f, +1.0f, 1.0f, +1.0f};

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

GLuint copyTriangleElementDataToGPU()
{
    GLushort indices[] = {0, 1, 2, 3, 4, 5};
    GLuint indexBufferObject;
    glGenBuffers(1, &indexBufferObject);
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, indexBufferObject);
    glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(indices), indices, GL_STATIC_DRAW);

    return indexBufferObject;
}

int DrawBasicTriandle()
{
    std::cout << "Hello Triangle" << std::endl;

    GLFWwindow *window;

    /* Initialize the library */
    if (!glfwInit())
        return -1;

    /* Create a windowed mode window and its OpenGL context */
    window = glfwCreateWindow(640, 480, "OpenGL Triangle", NULL, NULL);
    if (!window)
    {
        glfwTerminate();
        return -1;
    }

    /* Make the window's context current */
    glfwMakeContextCurrent(window);
    glfwSetWindowSizeCallback(window, windowSizeCallback);

    gladLoadGL();
    glEnable(GL_DEPTH_TEST); // *

    GLuint vertexBufferObject = copyTriangleVertexDataToGPU();
    GLuint indexBufferObject = copyTriangleElementDataToGPU();
    GLuint shaderProgram = createTriangleShaderProgram();
    glUseProgram(shaderProgram);

    glClearColor(0.07f, 0.13f, 0.17f, 1.0f);

    /* Loop until the user closes the window */
    while (!glfwWindowShouldClose(window))
    {
        /* Render here */
        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

        // glDrawArrays(GL_TRIANGLES, 0, 6); // Use element array for
        glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_SHORT, 0);

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