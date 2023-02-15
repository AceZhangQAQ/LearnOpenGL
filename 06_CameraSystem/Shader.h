//
// Created by 20553 on 2023/2/9.
//

#ifndef GLSL_PRACTICE_SHADER_H
#define GLSL_PRACTICE_SHADER_H

#include <glad/glad.h>

#include <string>
#include <fstream>
#include <sstream>
#include <iostream>

class Shader{
public:
    //程序ID
    unsigned int ID;

    //构造器读取并构建着色器
    Shader(const char* vertexPath, const char* fragmentPath){
        //1.从文件路径中获取顶点/片段着色器
        std::string vertexCode;
        std::string fragmentCode;
        std::ifstream vShaderFile;
        std::ifstream fShaderFile;
        //保证ifstream对象可以正常抛出异常
        vShaderFile.exceptions(std::ifstream::failbit | std::ifstream::badbit);
        fShaderFile.exceptions(std::ifstream::failbit | std::ifstream::badbit);
        try{
            //打开文件
            vShaderFile.open(vertexPath);
            fShaderFile.open(fragmentPath);
            std::stringstream vShaderStream, fShaderStream;
            //读取文件的缓冲内容到数据流
            vShaderStream << vShaderFile.rdbuf();
            fShaderStream << fShaderFile.rdbuf();
            //关闭文件处理器
            vShaderFile.close();
            fShaderFile.close();
            //转换数据流到string
            vertexCode = vShaderStream.str();
            fragmentCode = fShaderStream.str();
        }catch(std::ifstream::failure e){
            std::cout << "ERROR::SHADER::FILE NOT SUCCESFULLY READ" << std::endl;
        }
        const char* vShaderCode = vertexCode.c_str();
        const char* fShaderCode = fragmentCode.c_str();

        //编译着色器
        unsigned int vertex, fragment;
        //顶点着色器
        vertex = glCreateShader(GL_VERTEX_SHADER);
        glShaderSource(vertex,1,&vShaderCode,NULL);
        glCompileShader(vertex);
        //打印输出错误
        checkCompileErrors(vertex, "VERTEX");

        //片段着色器
        fragment = glCreateShader(GL_FRAGMENT_SHADER);
        glShaderSource(fragment,1,&fShaderCode,NULL);
        glCompileShader(fragment);
        //打印输出错误
        checkCompileErrors(fragment, "FRAGMENT");

        //链接着色器
        ID = glCreateProgram();
        glAttachShader(ID,vertex);
        glAttachShader(ID,fragment);
        glLinkProgram(ID);
        glDeleteShader(vertex);
        glDeleteShader(fragment);
        //打印链接错误
        checkCompileErrors(ID, "PROGRAM");
    }
    //使用/激活程序
    void use(){
        glUseProgram(ID);
    }
    //uniform工具函数
    void setBool(const std::string &name,bool value) const{
        glUniform1i(glGetUniformLocation(ID, name.c_str()), (int)value);
    }
    void setInt(const std::string &name,int value) const{
        glUniform1i(glGetUniformLocation(ID, name.c_str()), value);
    }
    void setFloat(const std::string &name,float value) const{
        glUniform1f(glGetUniformLocation(ID, name.c_str()), value);
    }
    void setMat4(const std::string &name, const glm::mat4 &mat) const{
        glUniformMatrix4fv(glGetUniformLocation(ID, name.c_str()),1,GL_FALSE, &mat[0][0]);
    }

private:
    void checkCompileErrors(unsigned int shader, std::string type)
    {
        int success;
        char infoLog[1024];
        if (type != "PROGRAM")
        {
            glGetShaderiv(shader, GL_COMPILE_STATUS, &success);
            if (!success)
            {
                glGetShaderInfoLog(shader, 1024, NULL, infoLog);
                std::cout << "ERROR::SHADER_COMPILATION_ERROR of type: " << type << "\n" << infoLog << "\n -- --------------------------------------------------- -- " << std::endl;
            }
        }
        else
        {
            glGetProgramiv(shader, GL_LINK_STATUS, &success);
            if (!success)
            {
                glGetProgramInfoLog(shader, 1024, NULL, infoLog);
                std::cout << "ERROR::PROGRAM_LINKING_ERROR of type: " << type << "\n" << infoLog << "\n -- --------------------------------------------------- -- " << std::endl;
            }
        }
    }
};

#endif //GLSL_PRACTICE_SHADER_H