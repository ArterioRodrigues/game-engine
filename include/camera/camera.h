#ifndef CAMERA_H
#define CAMERA_H

#include <pch/pch.h>

class Camera {
    private:
        glm::vec3 mCameraPos;
        glm::vec3 mCameraFront;
        glm::vec3 mCameraUp;
        glm::mat4 mCameraView;

        float mCameraSpeed;
        float mMouseSensitivity;
        float mCameraXPos;
        float mCameraYPos;

        float yaw;
        float pitch;

        bool mFirstMouseMove;
        

    public:
        Camera();

        glm::mat4 getCameraView();

        void processInput(GLFWwindow *window, float deltaTime);
        void lookAt(glm::vec3 x, glm::vec3 y, glm::vec3 z);
        void setCameraSpeed(float speed);
        void setCameraMouseSentivity(float speed);
        void mouseCallback(GLFWwindow* window, double xpos, double ypos);


};

#endif