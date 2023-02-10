#include <iostream>
#include <glad/glad.h>
#include <GLFW/glfw3.h>

//声明窗口大小变化回调函数
void framebuffer_size_callback(GLFWwindow* window, int width, int height);
//声明窗口输入控制函数
void processInput(GLFWwindow *window);

const unsigned int SCR_WIDTH = 800;
const unsigned int SCR_HEIGHT = 600;

const char *vertexShaderSource = "#version 330 core\n"
                                 "layout (location = 0) in vec3 aPos;\n"
                                 "void main()\n"
                                 "{\n"
                                 "    gl_Position = vec4(aPos.x,aPos.y,aPos.z,1.0);\n"
                                 "}\0";
const char *fragmentShaderSource1 = "#version 330 core\n"
                                   "out vec4 FragColor;\n"
                                   "void main()\n"
                                   "{\n"
                                   "    FragColor = vec4(1.0f,0.5f,0.2f,1.0f);\n"
                                   "}\0";
const char *fragmentShaderSource2 = "#version 330 core\n"
                                   "out vec4 FragColor;\n"
                                   "void main()\n"
                                   "{\n"
                                   "    FragColor = vec4(1.0f,1.0f,0.0f,1.0f);\n"
                                   "}\0";

int main() {
    //初始化并设置GLFW
    glfwInit();
    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
#ifdef __APPLE__
    glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE);//MacOs需要加的设置
#endif

    //创建窗口实例
    GLFWwindow  *window = glfwCreateWindow(SCR_WIDTH,SCR_HEIGHT,"Hello Triangle!",NULL,NULL);
    if(window == NULL){
        std::cout << "Failed to create GLFW window" << std::endl;
        glfwTerminate();
        return -1;
    }
    glfwMakeContextCurrent(window);
    //注册窗口大小变化回调函数
    glfwSetFramebufferSizeCallback(window,framebuffer_size_callback);

    //初始化Glad管理OpenGL函数指针
    if(!gladLoadGLLoader((GLADloadproc) glfwGetProcAddress)){
        std::cout << "Failed to initialize GLAD" << std::endl;
        return -1;
    }

    //编译着色器
    unsigned int vertexShader;
    vertexShader = glCreateShader(GL_VERTEX_SHADER);
    glShaderSource(vertexShader,1,&vertexShaderSource,NULL);
    glCompileShader(vertexShader);
    //检查顶点着色器编译结果
    int success;
    char infoLog[512];
    glGetShaderiv(vertexShader,GL_COMPILE_STATUS,&success);
    if(!success){
        glGetShaderInfoLog(vertexShader,512,NULL,infoLog);
        std::cout << "ERROR::SHADER::VERTEX::COMPILATION FAILED\n" << infoLog << std::endl;
    }

    //编译片段着色器1
    unsigned int fragmentShader1;
    fragmentShader1 = glCreateShader(GL_FRAGMENT_SHADER);
    glShaderSource(fragmentShader1,1,&fragmentShaderSource1,NULL);
    glCompileShader(fragmentShader1);
    //检查片段着色器编译结果
    glGetShaderiv(fragmentShader1,GL_COMPILE_STATUS,&success);
    if(!success){
        glGetShaderInfoLog(fragmentShader1,512,NULL,infoLog);
        std::cout << "ERROR::SHADER::FRAGMENT1::COMPILATION FAILED\n" << infoLog << std::endl;
    }

    //编译片段着色器2
    unsigned int fragmentShader2;
    fragmentShader2 = glCreateShader(GL_FRAGMENT_SHADER);
    glShaderSource(fragmentShader2,1,&fragmentShaderSource2,NULL);
    glCompileShader(fragmentShader2);
    //检查片段着色器编译结果
    glGetShaderiv(fragmentShader2,GL_COMPILE_STATUS,&success);
    if(!success){
        glGetShaderInfoLog(fragmentShader2,512,NULL,infoLog);
        std::cout << "ERROR::SHADER::FRAGMENT2::COMPILATION FAILED\n" << infoLog << std::endl;
    }

    //创建着色器程序1
    unsigned int shaderProgram1;
    shaderProgram1 = glCreateProgram();
    glAttachShader(shaderProgram1,vertexShader);
    glAttachShader(shaderProgram1,fragmentShader1);
    glLinkProgram(shaderProgram1);
    //检查着色器链接结果
    glGetProgramiv(shaderProgram1,GL_LINK_STATUS,&success);
    if(!success){
        glGetProgramInfoLog(shaderProgram1,512,NULL,infoLog);
        std::cout << "ERROR::PROGRAM1::LINK FAILED\n" << infoLog << std::endl;
    }
    glUseProgram(shaderProgram1);
    glDeleteShader(vertexShader);
    glDeleteShader(fragmentShader1);

    //创建着色器程序2
    unsigned int shaderProgram2;
    shaderProgram2 = glCreateProgram();
    glAttachShader(shaderProgram2,vertexShader);
    glAttachShader(shaderProgram2,fragmentShader2);
    glLinkProgram(shaderProgram2);
    //检查着色器链接结果
    glGetProgramiv(shaderProgram2,GL_LINK_STATUS,&success);
    if(!success){
        glGetProgramInfoLog(shaderProgram2,512,NULL,infoLog);
        std::cout << "ERROR::PROGRAM2::LINK FAILED\n" << infoLog << std::endl;
    }
    glUseProgram(shaderProgram2);
    glDeleteShader(vertexShader);
    glDeleteShader(fragmentShader2);

    //初始化顶点数据
    float triangle1[] = {
            -0.5f,-0.5f,0.0f,
            0.5f,-0.5f,0.0f,
            -0.5f,0.5f,0.0f,
    };
    float triangle2[] = {
            0.5f,0.5f,0.0f,
            -0.5f,0.5f,0.0f,
            0.5f,-0.5f,0.0f,
    };

    //创建VAO和VBO
    unsigned int VAOs[2],VBOs[2];
    glGenVertexArrays(2,VAOs);
    glGenBuffers(2,VBOs);
    //处理第一个三角形数据
    glBindVertexArray(VAOs[0]);
    glBindBuffer(GL_ARRAY_BUFFER,VBOs[0]);
    glBufferData(GL_ARRAY_BUFFER,sizeof(triangle1),triangle1,GL_STATIC_DRAW);
    glVertexAttribPointer(0,3,GL_FLOAT,GL_FALSE, 3 * sizeof (float),(void*)0);
    glEnableVertexAttribArray(0);
    //处理第二个三角形数据
    glBindVertexArray(VAOs[1]);
    glBindBuffer(GL_ARRAY_BUFFER,VBOs[1]);
    glBufferData(GL_ARRAY_BUFFER,sizeof(triangle2),triangle2,GL_STATIC_DRAW);
    glVertexAttribPointer(0,3,GL_FLOAT,GL_FALSE,3 * sizeof (float),(void*)0);
    glEnableVertexAttribArray(0);

    while(!glfwWindowShouldClose(window)){
        //处理输入
        processInput(window);

        //清理界面
        glClearColor(0.2f,0.3f,0.3f,1.0f);
        glClear(GL_COLOR_BUFFER_BIT);

        //渲染指令
        //使用第一个着色器程序
        glUseProgram(shaderProgram1);
        //使用第一个VAO
        glBindVertexArray(VAOs[0]);
        glDrawArrays(GL_TRIANGLES,0,3);

        //使用第二个着色器程序
        glUseProgram(shaderProgram2);
        //使用第二个VAO
        glBindVertexArray(VAOs[1]);
        glDrawArrays(GL_TRIANGLES,0,3);

        //交换缓存
        glfwSwapBuffers(window);
        glfwPollEvents();
    }

    //清理资源
    glDeleteVertexArrays(2,VAOs);
    glDeleteBuffers(2,VBOs);
    glDeleteProgram(shaderProgram1);
    glDeleteProgram(shaderProgram2);
    glfwTerminate();

    return 0;
}


/**
 * 窗口大小变化回掉函数
 * @param window
 * @param width
 * @param height
 */
void framebuffer_size_callback(GLFWwindow* window, int width, int height){
    glViewport(0, 0, width, height);
}

/**
 * 窗口输入控制函数
 * @param window
 */
void processInput(GLFWwindow *window)
{
    if(glfwGetKey(window, GLFW_KEY_ESCAPE) == GLFW_PRESS)
        glfwSetWindowShouldClose(window, true);
}
