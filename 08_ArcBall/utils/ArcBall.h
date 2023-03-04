#ifndef ArcBall_H
#define ArcBall_H

#include <glad/glad.h>
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <cmath>

#include <vector>

const static float sensitivity = 0.05f;

class ArcBall{
public:
    bool mouseClickDown = false;
    glm::vec3 startPosition;//鼠标开始位置
    glm::vec3 endPosition;//鼠标结束位置
    glm::vec3 RotationAxis;//旋转轴
    glm::mat4 RotationMat = glm::mat4(1.0f);//旋转矩阵
    float RotationAngle;//旋转角

    ArcBall(glm::vec3 start = glm::vec3(0.0f,0.0f,0.0f) , glm::vec3 end = glm::vec3(0.0f,0.0f,0.0f)){
        startPosition = start;
        endPosition = end;
    }

    //设置旋转矩阵
    void setRotation(){
        RotationAngle = (180 / 3.14159265) * acos(glm::dot(startPosition,endPosition)) * sensitivity;
        RotationAxis = glm::cross(startPosition,endPosition);
        startPosition = endPosition;
        RotationMat = glm::rotate(RotationMat,RotationAngle,RotationAxis);
    }

    glm::mat4 getRotation(){
        return RotationMat;
    }

    glm::vec3 getArcBallPosition(GLFWwindow* window, double x, double y){
        int width,height;
        glfwGetWindowSize(window,&width,&height);
        float px = (x - width /2) / (width / 2);
        float py = - (y - height /2) / (height / 2);
        float pz;
        float r = px * px + py * py;
        if(r > 1.0){
            px = 1.0f / glm::sqrt(r) * px;
            py = 1.0f / glm::sqrt(r) * py;
            pz = 0.0f;
        }else{
            pz = - glm::sqrt(1.0f - r);
        }
        return glm::vec3(px,py,pz);
    }

};


#endif
