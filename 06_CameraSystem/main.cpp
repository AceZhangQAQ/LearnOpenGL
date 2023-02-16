#include <glad/glad.h>
#include <GLFW/glfw3.h>

#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>

#include <cmath>

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

float mixValue = 0.2f;

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

    // glad: load all OpenGL function pointers
    // ---------------------------------------
    if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress))
    {
        std::cout << "Failed to initialize GLAD" << std::endl;
        return -1;
    }

    //开启深度缓冲测试
    glEnable(GL_DEPTH_TEST);
    //设置鼠标光标隐藏
    //glfwSetInputMode(window,GLFW_CURSOR,GLFW_CURSOR_DISABLED);
    //注册鼠标移动回调函数
    glfwSetCursorPosCallback(window,mouse_callback);
    //注册鼠标滚轮回调函数
    glfwSetScrollCallback(window, scroll_callback);

    //初始化Shader
    Shader ourShader("/Users/acezhang/Documents/GitHub/LearnOpenGL/05_CoordSystem/shader/shader.vs","/Users/acezhang/Documents/GitHub/LearnOpenGL/05_CoordSystem/shader/shader.fs");
    //Shader ourShader("D:/Studys_Files/GithubFiles/LearnOpenGL/04_TransformByGLM/shader/shader.vs","D:/Studys_Files/GithubFiles/LearnOpenGL/04_TransformByGLM/shader/shader.fs");

    //设置顶点属性数据
    float vertices[] = {
            -0.5f, -0.5f, -0.5f,  0.0f, 0.0f,
            0.5f, -0.5f, -0.5f,  1.0f, 0.0f,
            0.5f,  0.5f, -0.5f,  1.0f, 1.0f,
            0.5f,  0.5f, -0.5f,  1.0f, 1.0f,
            -0.5f,  0.5f, -0.5f,  0.0f, 1.0f,
            -0.5f, -0.5f, -0.5f,  0.0f, 0.0f,

            -0.5f, -0.5f,  0.5f,  0.0f, 0.0f,
            0.5f, -0.5f,  0.5f,  1.0f, 0.0f,
            0.5f,  0.5f,  0.5f,  1.0f, 1.0f,
            0.5f,  0.5f,  0.5f,  1.0f, 1.0f,
            -0.5f,  0.5f,  0.5f,  0.0f, 1.0f,
            -0.5f, -0.5f,  0.5f,  0.0f, 0.0f,

            -0.5f,  0.5f,  0.5f,  1.0f, 0.0f,
            -0.5f,  0.5f, -0.5f,  1.0f, 1.0f,
            -0.5f, -0.5f, -0.5f,  0.0f, 1.0f,
            -0.5f, -0.5f, -0.5f,  0.0f, 1.0f,
            -0.5f, -0.5f,  0.5f,  0.0f, 0.0f,
            -0.5f,  0.5f,  0.5f,  1.0f, 0.0f,

            0.5f,  0.5f,  0.5f,  1.0f, 0.0f,
            0.5f,  0.5f, -0.5f,  1.0f, 1.0f,
            0.5f, -0.5f, -0.5f,  0.0f, 1.0f,
            0.5f, -0.5f, -0.5f,  0.0f, 1.0f,
            0.5f, -0.5f,  0.5f,  0.0f, 0.0f,
            0.5f,  0.5f,  0.5f,  1.0f, 0.0f,

            -0.5f, -0.5f, -0.5f,  0.0f, 1.0f,
            0.5f, -0.5f, -0.5f,  1.0f, 1.0f,
            0.5f, -0.5f,  0.5f,  1.0f, 0.0f,
            0.5f, -0.5f,  0.5f,  1.0f, 0.0f,
            -0.5f, -0.5f,  0.5f,  0.0f, 0.0f,
            -0.5f, -0.5f, -0.5f,  0.0f, 1.0f,

            -0.5f,  0.5f, -0.5f,  0.0f, 1.0f,
            0.5f,  0.5f, -0.5f,  1.0f, 1.0f,
            0.5f,  0.5f,  0.5f,  1.0f, 0.0f,
            0.5f,  0.5f,  0.5f,  1.0f, 0.0f,
            -0.5f,  0.5f,  0.5f,  0.0f, 0.0f,
            -0.5f,  0.5f, -0.5f,  0.0f, 1.0f
    };

    //10个cube在世界坐标中的位置
    glm::vec3 cubePositions[] = {
            glm::vec3( 0.0f,  0.0f,  0.0f),
            glm::vec3( 2.0f,  5.0f, -15.0f),
            glm::vec3(-1.5f, -2.2f, -2.5f),
            glm::vec3(-3.8f, -2.0f, -12.3f),
            glm::vec3( 2.4f, -0.4f, -3.5f),
            glm::vec3(-1.7f,  3.0f, -7.5f),
            glm::vec3( 1.3f, -2.0f, -2.5f),
            glm::vec3( 1.5f,  2.0f, -2.5f),
            glm::vec3( 1.5f,  0.2f, -1.5f),
            glm::vec3(-1.3f,  1.0f, -1.5f)
    };

    //设置VAO、VBO、EBO
    //unsigned int VAO,VBO,EBO;
    unsigned int VAO,VBO;

    glGenVertexArrays(1,&VAO);
    glGenBuffers(1,&VBO);
    //glGenBuffers(1,&EBO);

    glBindVertexArray(VAO);

    glBindBuffer(GL_ARRAY_BUFFER,VBO);
    glBufferData(GL_ARRAY_BUFFER,sizeof(vertices),vertices,GL_STATIC_DRAW);

    //glBindBuffer(GL_ELEMENT_ARRAY_BUFFER,EBO);
    //glBufferData(GL_ELEMENT_ARRAY_BUFFER,sizeof(indices),indices,GL_STATIC_DRAW);

    glVertexAttribPointer(0,3,GL_FLOAT,GL_FALSE,5 * sizeof(float), (void*)0);
    glEnableVertexAttribArray(0);
    glVertexAttribPointer(1,2,GL_FLOAT,GL_FALSE,5 * sizeof(float), (void*)(3 * sizeof(float)));
    glEnableVertexAttribArray(1);

    //创建纹理对象
    unsigned int texture1,texture2;
    glGenTextures(1,&texture1);
    glBindTexture(GL_TEXTURE_2D,texture1);

    //为纹理对象设置环绕方式、过滤方式
    glTexParameteri(GL_TEXTURE_2D,GL_TEXTURE_WRAP_S,GL_REPEAT);
    glTexParameteri(GL_TEXTURE_2D,GL_TEXTURE_WRAP_T,GL_REPEAT);
    glTexParameteri(GL_TEXTURE_2D,GL_TEXTURE_MIN_FILTER,GL_LINEAR);
    glTexParameteri(GL_TEXTURE_2D,GL_TEXTURE_MAG_FILTER,GL_LINEAR);

    //加载并生成纹理
    int width, height, nrChannels;
    stbi_set_flip_vertically_on_load(true);//翻转y轴加载纹理
    unsigned char *data = stbi_load("/Users/acezhang/Documents/GitHub/LearnOpenGL/05_CoordSystem/src/image/container.jpg", &width, &height, &nrChannels, 0);
    //unsigned char *data = stbi_load("D:/Studys_Files/GithubFiles/LearnOpenGL/04_TransformByGLM/src/image/container.jpg", &width, &height, &nrChannels, 0);
    if(data){
        glTexImage2D(GL_TEXTURE_2D,0,GL_RGB,width,height,0,GL_RGB,GL_UNSIGNED_BYTE,data);
        glGenerateMipmap(GL_TEXTURE_2D);
    }else{
        std::cout << "ERROR::TEXTURE::LOAD::FAILED TO LOAD TEXTURE IMAGE" << std::endl;
    }
    stbi_image_free(data);
    glGenTextures(1,&texture2);
    glBindTexture(GL_TEXTURE_2D,texture2);
    glTexParameteri(GL_TEXTURE_2D,GL_TEXTURE_WRAP_S,GL_REPEAT);
    glTexParameteri(GL_TEXTURE_2D,GL_TEXTURE_WRAP_T,GL_REPEAT);
    glTexParameteri(GL_TEXTURE_2D,GL_TEXTURE_MIN_FILTER,GL_LINEAR);
    glTexParameteri(GL_TEXTURE_2D,GL_TEXTURE_MAG_FILTER,GL_LINEAR);

    data = stbi_load("/Users/acezhang/Documents/GitHub/LearnOpenGL/05_CoordSystem/src/image/awesomeface.png", &width, &height, &nrChannels, 0);
    //data = stbi_load("D:/Studys_Files/GithubFiles/LearnOpenGL/04_TransformByGLM/src/image/awesomeface.png", &width, &height, &nrChannels, 0);
    if(data){
        glTexImage2D(GL_TEXTURE_2D,0,GL_RGBA,width,height,0,GL_RGBA,GL_UNSIGNED_BYTE,data);
        glGenerateMipmap(GL_TEXTURE_2D);
    }else{
        std::cout << "ERROR::TEXTURE::LOAD::FAILED TO LOAD TEXTURE IMAGE" << std::endl;
    }
    stbi_image_free(data);

    ourShader.use();
    //两种方式来设置纹理对应的纹理单元
    glUniform1i(glGetUniformLocation(ourShader.ID, "texture1"), 0);
    ourShader.setInt("texture2", 1);

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

        //绑定纹理
        glActiveTexture(GL_TEXTURE0);
        glBindTexture(GL_TEXTURE_2D,texture1);
        glActiveTexture(GL_TEXTURE1);
        glBindTexture(GL_TEXTURE_2D,texture2);

        ourShader.use();

        //设置笑脸贴图透明度
        ourShader.setFloat("alpha",mixValue);

        //设置投影矩阵
        glm::mat4 projection = glm::perspective(glm::radians(camera.Zoom),(float)SCR_WIDTH / (float)SCR_HEIGHT,0.1f,100.0f);
        ourShader.setMat4("projection",projection);
        //设置观测矩阵
        glm::mat4 view = camera.GetViewMatrix();
        ourShader.setMat4("view",view);

        glBindVertexArray(VAO);
        //每帧画10个箱子
        for(unsigned int i = 0; i < 10; i++){
            glm::mat4 model = glm::mat4 (1.0f);
            //设置箱子在世界坐标中的位置
            model = glm::translate(model,cubePositions[i]);

            float angle = glfwGetTime() * 25.0f + 25.0f * i;
            //设置箱子的旋转
            model = glm::rotate(model,glm::radians(angle),glm::vec3(1.0f,0.3f,0.5f));
            ourShader.setMat4("model",model);

            glDrawArrays(GL_TRIANGLES,0,36);
        }

        //交换缓存
        glfwSwapBuffers(window);
        glfwPollEvents();
    }

    //释放资源
    glDeleteVertexArrays(1, &VAO);
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
    if (glfwGetKey(window, GLFW_KEY_UP) == GLFW_PRESS){
        mixValue += 0.01f;
        if(mixValue >= 1.0f)
            mixValue = 1.0f;
    }
    if (glfwGetKey(window, GLFW_KEY_DOWN) == GLFW_PRESS){
        mixValue -= 0.01f;
        if(mixValue <= 0.0f)
            mixValue = 0.0f;
    }
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


