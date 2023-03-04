#include <glad/glad.h>
#include <GLFW/glfw3.h>

#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>

#include "utils/Shader.h"
#include "utils/Camera.h"
#include "includes/stb_image/stb_image.h"

#include <iostream>

//窗口改变回调函数
void framebuffer_size_callback(GLFWwindow* window, int width, int height);
//鼠标位置改变回调函数
void mouse_callback(GLFWwindow* window, double xposIn, double yposIn);
//鼠标滚轮滑动改变回调函数
void scroll_callback(GLFWwindow* window, double xoffset,double yoffset);
//处理输入函数
void processInput(GLFWwindow *window);

// settings
const unsigned int SCR_WIDTH = 800;
const unsigned int SCR_HEIGHT = 600;

//摄像机位置、方向
Camera camera(glm::vec3(0.0f,0.0f,3.0f));

//帧时间
float deltaTime = 0.0f;
float lastFrame = 0.0f;
//上一帧鼠标位置
float lastX = SCR_WIDTH / 2.0f;
float lastY = SCR_HEIGHT / 2.0f;
//是否是第一次移入窗口
bool firstMovingIn = true;

//灯位置
glm::vec3 lightPos(1.2f, 1.0f, 2.0f);

int main() {
    // GLFW初始化
    // ------------------------------
    glfwInit();
    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

#ifdef __APPLE__
    glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE);
#endif
    // 创建窗口
    // --------------------
    GLFWwindow* window = glfwCreateWindow(SCR_WIDTH, SCR_HEIGHT, "LearnOpenGL", NULL, NULL);
    if (window == NULL)
    {
        std::cout << "Failed to create GLFW window" << std::endl;
        glfwTerminate();
        return -1;
    }
    glfwMakeContextCurrent(window);
    //注册窗口改变回掉函数
    glfwSetFramebufferSizeCallback(window, framebuffer_size_callback);
    //设置鼠标光标隐藏
    //glfwSetInputMode(window,GLFW_CURSOR,GLFW_CURSOR_DISABLED);
    //注册鼠标移动回调函数
    glfwSetCursorPosCallback(window,mouse_callback);
    //注册鼠标滚轮回调函数
    glfwSetScrollCallback(window, scroll_callback);

    // glad: load all OpenGL function pointers
    // ---------------------------------------
    if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress))
    {
        std::cout << "Failed to initialize GLAD" << std::endl;
        return -1;
    }

    //开启深度缓冲测试
    glEnable(GL_DEPTH_TEST);

    //初始化Shader
    Shader lightShader("/Users/acezhang/Documents/GitHub/LearnOpenGL/07_CreateLightScene/shader/lightShader.vs","/Users/acezhang/Documents/GitHub/LearnOpenGL/07_CreateLightScene/shader/lightShader.fs");
    Shader boxShader("/Users/acezhang/Documents/GitHub/LearnOpenGL/07_CreateLightScene/shader/boxShader.vs","/Users/acezhang/Documents/GitHub/LearnOpenGL/07_CreateLightScene/shader/boxShader.fs");

    //设置顶点属性数据,共12个三角形，36个点。
    float vertices[] = {
            -0.5f, -0.5f, -0.5f,
            0.5f, -0.5f, -0.5f,
            0.5f,  0.5f, -0.5f,
            0.5f,  0.5f, -0.5f,
            -0.5f,  0.5f, -0.5f,
            -0.5f, -0.5f, -0.5f,

            -0.5f, -0.5f,  0.5f,
            0.5f, -0.5f,  0.5f,
            0.5f,  0.5f,  0.5f,
            0.5f,  0.5f,  0.5f,
            -0.5f,  0.5f,  0.5f,
            -0.5f, -0.5f,  0.5f,

            -0.5f,  0.5f,  0.5f,
            -0.5f,  0.5f, -0.5f,
            -0.5f, -0.5f, -0.5f,
            -0.5f, -0.5f, -0.5f,
            -0.5f, -0.5f,  0.5f,
            -0.5f,  0.5f,  0.5f,

            0.5f,  0.5f,  0.5f,
            0.5f,  0.5f, -0.5f,
            0.5f, -0.5f, -0.5f,
            0.5f, -0.5f, -0.5f,
            0.5f, -0.5f,  0.5f,
            0.5f,  0.5f,  0.5f,

            -0.5f, -0.5f, -0.5f,
            0.5f, -0.5f, -0.5f,
            0.5f, -0.5f,  0.5f,
            0.5f, -0.5f,  0.5f,
            -0.5f, -0.5f,  0.5f,
            -0.5f, -0.5f, -0.5f,

            -0.5f,  0.5f, -0.5f,
            0.5f,  0.5f, -0.5f,
            0.5f,  0.5f,  0.5f,
            0.5f,  0.5f,  0.5f,
            -0.5f,  0.5f,  0.5f,
            -0.5f,  0.5f, -0.5f,
    };

    //设置VAO、VBO
    unsigned int VBO, lightVAO, boxVAO;

    //加载顶点数据
    glGenBuffers(1,&VBO);
    glBindBuffer(GL_ARRAY_BUFFER, VBO);
    glBufferData(GL_ARRAY_BUFFER, sizeof (vertices), vertices, GL_STATIC_DRAW);

    //解释光源顶点数据
    glGenVertexArrays(1, &lightVAO);
    glBindVertexArray(lightVAO);
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3*sizeof(float), (void*)0);
    glEnableVertexAttribArray(0);

    //解释盒子顶点数据
    glGenVertexArrays(1, &boxVAO);
    glBindVertexArray(boxVAO);
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3*sizeof(float), (void*)0);
    glEnableVertexAttribArray(0);

    //渲染循环
    while (!glfwWindowShouldClose(window)){
        float currentFrame = static_cast<float>(glfwGetTime());
        deltaTime = currentFrame - lastFrame;
        lastFrame = currentFrame;
        //处理输入
        processInput(window);

        //清空颜色和深度缓存
        glClearColor(0.2f,0.3f,0.3f,1.0f);
        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

        //更新model,view和projection矩阵
        glm::mat4 model = glm::mat4(1.0f);
        glm::mat4 view = camera.GetViewMatrix();
        glm::mat4 projection = glm::perspective(glm::radians(camera.Zoom), (float)SCR_WIDTH / (float)SCR_HEIGHT, 0.1f, 100.0f);

        //渲染光源
        lightShader.use();
        lightShader.setMat4("projection",projection);
        lightShader.setMat4("view",view);
        model = glm::translate(model, lightPos);//移动光源
        model = glm::scale(model, glm::vec3(0.2f));//缩放光源
        lightShader.setMat4("model",model);
        glBindVertexArray(lightVAO);
        glDrawArrays(GL_TRIANGLES, 0, 36);

        //渲染物体
        boxShader.use();
        //设置光源颜色和物体颜色
        boxShader.setVec3("objectColor",glm::vec3(1.0f, 0.5f, 0.31f));
        boxShader.setVec3("lightColor",glm::vec3(1.0f, 1.0f, 1.0f));
        boxShader.setMat4("projection",projection);
        boxShader.setMat4("view",view);
        model = glm::mat4(1.0f);
        boxShader.setMat4("model",model);
        glBindVertexArray(boxVAO);
        glDrawArrays(GL_TRIANGLES, 0, 36);

        //交换缓存
        glfwSwapBuffers(window);
        glfwPollEvents();
    }

    //释放资源
    glDeleteVertexArrays(1, &lightVAO);
    glDeleteVertexArrays(1, &boxVAO);
    glDeleteBuffers(1, &VBO);

    glfwTerminate();
    return 0;
}


/**
 * 处理输入函数
 * @param window
 */
void processInput(GLFWwindow *window)
{
    if (glfwGetKey(window, GLFW_KEY_ESCAPE) == GLFW_PRESS)
        glfwSetWindowShouldClose(window, true);
    if (glfwGetKey(window, GLFW_KEY_W) == GLFW_PRESS)
        camera.ProcessKeyboard(FORWARD, deltaTime);
    if (glfwGetKey(window, GLFW_KEY_S) == GLFW_PRESS)
        camera.ProcessKeyboard(BACKWARD, deltaTime);
    if (glfwGetKey(window, GLFW_KEY_A) == GLFW_PRESS)
        camera.ProcessKeyboard(LEFT, deltaTime);
    if (glfwGetKey(window, GLFW_KEY_D) == GLFW_PRESS)
        camera.ProcessKeyboard(RIGHT, deltaTime);
}

/**
 * 窗口改变回调函数
 * @param window
 * @param width
 * @param height
 */
void framebuffer_size_callback(GLFWwindow* window, int width, int height)
{
    // make sure the viewport matches the new window dimensions; note that width and
    // height will be significantly larger than specified on retina displays.
    glViewport(0, 0, width, height);
}

/**
 * 鼠标位置改变回调函数
 * @param window
 * @param xpos
 * @param ypos
 */
void mouse_callback(GLFWwindow* window, double xposIn, double yposIn){
    float xpos = static_cast<float>(xposIn);
    float ypos = static_cast<float>(yposIn);

    if (firstMovingIn)
    {
        lastX = xpos;
        lastY = ypos;
        firstMovingIn = false;
    }

    float xoffset = xpos - lastX;
    float yoffset = lastY - ypos; // reversed since y-coordinates go from bottom to top

    lastX = xpos;
    lastY = ypos;

    camera.ProcessMouseMovement(xoffset, yoffset);
}

/**
 * 鼠标滚轮滑动回调函数
 * @param window
 * @param xoffset
 * @param yoffset
 */
void scroll_callback(GLFWwindow* window,double xoffset,double yoffset){
    camera.ProcessMouseScroll(static_cast<float>(yoffset));
}


