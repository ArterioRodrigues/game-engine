#include <camera/camera.h>

Camera::Camera(){
    this->mCameraPos   = glm::vec3(0.0f, 0.0f, 5.0f);
    this->mCameraFront = glm::vec3(0.0f, 0.0f, -1.0f);
    this->mCameraUp    = glm::vec3(0.0f, 1.0f, 0.0f);

    this->mCameraView = glm::mat4(1.0f);
    this->mCameraView = glm::lookAt(this->mCameraPos, this->mCameraPos + this->mCameraFront, this->mCameraUp);

    this->mCameraSpeed = 2.5f;
    this->mMouseSensitivity = 0.1f;
    this->mFirstMouseMove = true;

    this->yaw = -90.0f;
    this->pitch = 0.0f;
}

void Camera::processInput(GLFWwindow *window, float deltaTime){
    
    float cameraSpeed = this->mCameraSpeed * deltaTime;

    if(glfwGetKey(window, GLFW_KEY_W) == GLFW_PRESS)
        this->mCameraPos += cameraSpeed * this->mCameraFront;
    if(glfwGetKey(window, GLFW_KEY_S) == GLFW_PRESS)
        this->mCameraPos -= cameraSpeed * this->mCameraFront;
    if(glfwGetKey(window, GLFW_KEY_A) == GLFW_PRESS)
        this->mCameraPos -= glm::normalize(glm::cross(this->mCameraFront, this->mCameraUp)) * cameraSpeed;
    if(glfwGetKey(window, GLFW_KEY_D) == GLFW_PRESS)
        this->mCameraPos += glm::normalize(glm::cross(this->mCameraFront, this->mCameraUp)) * cameraSpeed;

    this->mCameraView = glm::lookAt(this->mCameraPos, this->mCameraPos + this->mCameraFront, this->mCameraUp);
}

glm::mat4 Camera::getCameraView(){
    return this->mCameraView;
}

void Camera::lookAt(glm::vec3 x, glm::vec3 y, glm::vec3 z) {
    this->mCameraView = glm::lookAt(x, y, z);
}

void Camera::setCameraSpeed(float speed){
    this->mCameraSpeed = speed;
}

void Camera::setCameraMouseSentivity(float speed){
    this->mMouseSensitivity = speed;
}

void Camera::mouseCallback(GLFWwindow* window, double xpos, double ypos){
    if (this->mFirstMouseMove){
        this->mCameraXPos = xpos;
        this->mCameraYPos = ypos;
        this->mFirstMouseMove = false;
    }

    float xoffset = xpos - this->mCameraXPos;
    float yoffset = this->mCameraYPos - ypos;

    this->mCameraXPos = xpos;
    this->mCameraYPos = ypos;

    xoffset *= this->mMouseSensitivity;
    yoffset *= this->mMouseSensitivity;

    yaw += xoffset;
    pitch += yoffset;

    if(pitch > 89.0f) pitch = 89.0f;
    if(pitch < -89.0f) pitch = -89.0f;

    glm::vec3 direction;
    direction.x = cos(glm::radians(yaw)) * cos(glm::radians(pitch));
    direction.y = sin(glm::radians(pitch));
    direction.z = sin(glm::radians(yaw)) * cos(glm::radians(pitch));
    this->mCameraFront = glm::normalize(direction);

    std::cout << this->mCameraFront.x << this->mCameraFront.y << this->mCameraFront.z << std::endl;
}