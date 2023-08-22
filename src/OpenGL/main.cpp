#include <iostream>
#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include <fstream>

std::string get_file_string(std::string filePath)
{
    std::ifstream ifs(filePath);
    return std::string((std::istreambuf_iterator<char>(ifs)),
                       (std::istreambuf_iterator<char>()));
}

void windowSizeCallback(GLFWwindow *window, int width, int height)
{
    glad_glViewport(0, 0, width, height);
}

GLuint createShaderProgram()
{
    std::string strVert = get_file_string("./shader/triangle.vert");
    const GLchar *vertCStr = strVert.c_str();
    std::cout << strVert.c_str() << std::endl;

    std::string strFrag = get_file_string("./shader/triangle.frag");
    const GLchar *fragCStr = strFrag.c_str();
    std::cout << strFrag.c_str() << std::endl;

    GLuint vertexShader = glad_glCreateShader(GL_VERTEX_SHADER);
    glad_glShaderSource(vertexShader, 1, &vertCStr, NULL);
    glad_glCompileShader(vertexShader);

    GLuint fragmentShader = glad_glCreateShader(GL_FRAGMENT_SHADER);
    glad_glShaderSource(fragmentShader, 1, &fragCStr, NULL);
    glad_glCompileShader(fragmentShader);

    GLuint shaderProgram = glad_glCreateProgram();
    glad_glAttachShader(shaderProgram, vertexShader);
    glad_glAttachShader(shaderProgram, fragmentShader);
    glad_glLinkProgram(shaderProgram);

    glad_glDeleteShader(vertexShader);
    glad_glDeleteShader(fragmentShader);

    return shaderProgram;
}

GLuint copyVertexDataToGPU()
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
    glad_glGenBuffers(1, &vertexBufferObject);
    glad_glBindBuffer(GL_ARRAY_BUFFER, vertexBufferObject);
    glad_glBufferData(GL_ARRAY_BUFFER, sizeof(verts), verts, GL_STATIC_DRAW);

    glad_glEnableVertexAttribArray(0);
    glad_glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 7 * sizeof(GLfloat), (void *)0);

    glad_glEnableVertexAttribArray(1);
    glad_glVertexAttribPointer(1, 4, GL_FLOAT, GL_FALSE, 7 * sizeof(GLfloat), (void *)(sizeof(GLfloat) * 3));

    return vertexBufferObject;
}

GLuint copyElementDataToGPU()
{
    GLushort indices[] = {0, 1, 2, 3, 4, 5};
    GLuint indexBufferObject;
    glad_glGenBuffers(1, &indexBufferObject);
    glad_glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, indexBufferObject);
    glad_glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(indices), indices, GL_STATIC_DRAW);

    return indexBufferObject;
}

int main()
{
    std::cout << "Hello world" << std::endl;

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
    glad_glEnable(GL_DEPTH_TEST);

    GLuint vertexBufferObject = copyVertexDataToGPU();
    GLuint indexBufferObject = copyElementDataToGPU();
    GLuint shaderProgram = createShaderProgram();
    glUseProgram(shaderProgram);

    /* Loop until the user closes the window */
    while (!glfwWindowShouldClose(window))
    {
        /* Render here */
        glad_glClearColor(0.07f, 0.13f, 0.17f, 1.0f);

        glad_glClear(GL_COLOR_BUFFER_BIT);
        glad_glClear(GL_DEPTH_BUFFER_BIT);

        // glDrawArrays(GL_TRIANGLES, 0, 6); // Use element array for
        glad_glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_SHORT, 0);

        /* Swap front and back buffers */
        glfwSwapBuffers(window);

        /* Poll for and process events */
        glfwPollEvents();
    }

    glad_glDeleteBuffers(1, &vertexBufferObject);
    glad_glDeleteBuffers(1, &indexBufferObject);
    glad_glDeleteProgram(shaderProgram);
    glfwDestroyWindow(window);
    glfwTerminate();
    return 0;
}