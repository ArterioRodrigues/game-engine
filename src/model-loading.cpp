
#include <pch/pch.h>

struct DirLight {
    glm::vec3 direction;

    glm::vec3 ambient;
    glm::vec3 diffuse;
    glm::vec3 specular;
};

struct PointLight {
    glm::vec3 position;
    
    float constant;
    float linear;
    float quadratic;

    glm::vec3 ambient;
    glm::vec3 diffuse;
    glm::vec3 specular;
};

Camera CAMERA(glm::vec3(0.0f, 0.0f, 3.0f));
const unsigned int SCR_WIDTH = 800;
const unsigned int SCR_HEIGHT = 600;
float lastX = SCR_WIDTH / 2.0f;
float lastY = SCR_HEIGHT / 2.0f;
bool firstMouse = true;

float deltaTime = 0.0f;
float lastFrame = 0.0f;

glm::vec3 lightPos(3.2f, 1.0f, 2.0f);

float frameCounter = 0;
float prevFrame= static_cast<float>(glfwGetTime());

//Used to callback when ever the screen is resized
void framebuffer_size_callback(GLFWwindow* window, int width, int height){
    glViewport(0, 0, width, height);
}
void processInput(GLFWwindow *window){
    if(glfwGetKey(window, GLFW_KEY_ESCAPE) == GLFW_PRESS)
        glfwSetWindowShouldClose(window, true);
}
void mouse_callback(GLFWwindow* window, double xpos, double ypos){
    CAMERA.mouseCallback(window, xpos, ypos);
}
void printframeRate(float* currentFrame, float* prevFrame){
    frameCounter += 1;
     
    if(*currentFrame - *prevFrame >= 1.0){
        
        std::cout << "FRAMES: " << frameCounter << std::endl;
        *prevFrame = *currentFrame;
        frameCounter = 0;
    }
}
glm::vec3 getRandomVec3(float min, float max) {
    auto randomFloat = [](float min, float max) -> float {
        return min + static_cast<float>(rand()) / (static_cast<float>(RAND_MAX / (max - min)));
    };
    return glm::vec3(randomFloat(min, max), randomFloat(min, max), randomFloat(min, max));
}
float getRandomFloat(float min, float max) {
    return min + static_cast<float>(rand()) / (static_cast<float>(RAND_MAX / (max - min)));
}
void generateRandomVec3Vector(int size, std::vector<glm::vec3>& vec, float min, float max) {
    vec.clear();
    vec.reserve(size);

    for (int i = 0; i < size; ++i) {
        vec.push_back(getRandomVec3(min, max));
    }
}
void generatePointLight(std::vector<PointLight>& vec, std::vector<glm::vec3>& positions,int size = 4, float min = 3, float max = 3){
    vec.clear();

    // for(int i = 0; i < size; i++) {
    //     PointLight light;

    //     light.position = positions[i];
    //     light.constant = getRandomFloat(min, max);
    //     light.linear = getRandomFloat(min, max);
    //     light.quadratic = getRandomFloat(min, max);
    //     light.ambient = getRandomVec3(min, max);
    //     light.diffuse = getRandomVec3(min, max);
    //     light.specular = getRandomVec3(min, max);

    //     vec.push_back(light);
    // }

    PointLight light1;
    PointLight light2;
    PointLight light3;
    PointLight light4;

    light1.position = positions[0];
    light1.constant = 1.0f;
    light1.linear   = 0.7f;
    light1.quadratic = 1.8f;
    light1.ambient = glm::vec3(1.0f, 0.0f, 0.0f);
    light1.diffuse = glm::vec3(0.5f, 0.5f, 0.5f);
    light1.specular = glm::vec3(1.0f, 1.0f, 1.0f);

    light2.position = positions[1];
    light2.constant = 1.0f;
    light2.linear  = 0.35f;
    light2.quadratic = 0.44f;
    light2.ambient = glm::vec3(0.0f, 1.0f, 0.0f);
    light2.diffuse = glm::vec3(0.5f, 0.5f, 0.5f);
    light2.specular =glm::vec3(1.0f, 1.0f, 1.0f);

    light3.position = positions[2];
    light3.constant = 1.0f;
    light3.linear = 0.22f;
    light3.quadratic = 0.2f;
    light3.ambient = glm::vec3(0.0f, 0.0f, 1.0f);
    light3.diffuse = glm::vec3(0.5f, 0.5f, 0.5f);
    light3.specular =glm::vec3(1.0f, 1.0f, 1.0f);

    light4.position = positions[3];
    light4.constant = 1.0f;
    light4.linear = 0.14f;
    light4.quadratic = 0.07f;
    light4.ambient = glm::vec3(1.0f, 1.0f, 0.0f);
    light4.diffuse = glm::vec3(0.5f, 0.5f, 0.5f);
    light4.specular =glm::vec3(1.0f, 1.0f, 1.0f);

    vec.push_back(light1);
    vec.push_back(light2);
    vec.push_back(light3);
    vec.push_back(light4);
}

int main() {
    //Initialize GLFW
    glfwInit();
    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
    glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE);

#ifdef __APPLE__
    glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE);
#endif
    //Create a window 
    GLFWwindow* window = glfwCreateWindow(800, 600, "ARC", NULL, NULL);
    if(window == NULL){
        std::cout << "Failed to create GLFW window" << std::endl;
        glfwTerminate();
        return -1;
    }

    glfwSetInputMode(window, GLFW_CURSOR, GLFW_CURSOR_DISABLED);
    glfwSetFramebufferSizeCallback(window, framebuffer_size_callback);
    glfwSetCursorPosCallback(window, mouse_callback);
    glfwMakeContextCurrent(window); //Set created window as context aka current window
    if(!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress)){
        std::cout << "Failed to initialize GLAD" << std::endl;
        return -1;
    }

    glEnable(GL_DEPTH_TEST);
    

    Shader cubeShader("./shaders/multiple-lights/shader.vert", "./shaders/multiple-lights/shader.frag");
    Shader lightCubeShader("./shaders/light/shader.vert", "./shaders/light/shader.frag");
    Shader pointLightCubeShader("./shaders/light/shader.vert", "./shaders/light/shader.frag");

    float vertices[] = {
        // positions          // normals           // texture coords
        -0.5f, -0.5f, -0.5f,  0.0f,  0.0f, -1.0f,  0.0f,  0.0f,
         0.5f, -0.5f, -0.5f,  0.0f,  0.0f, -1.0f,  1.0f,  0.0f,
         0.5f,  0.5f, -0.5f,  0.0f,  0.0f, -1.0f,  1.0f,  1.0f,
         0.5f,  0.5f, -0.5f,  0.0f,  0.0f, -1.0f,  1.0f,  1.0f,
        -0.5f,  0.5f, -0.5f,  0.0f,  0.0f, -1.0f,  0.0f,  1.0f,
        -0.5f, -0.5f, -0.5f,  0.0f,  0.0f, -1.0f,  0.0f,  0.0f,

        -0.5f, -0.5f,  0.5f,  0.0f,  0.0f,  1.0f,  0.0f,  0.0f,
         0.5f, -0.5f,  0.5f,  0.0f,  0.0f,  1.0f,  1.0f,  0.0f,
         0.5f,  0.5f,  0.5f,  0.0f,  0.0f,  1.0f,  1.0f,  1.0f,
         0.5f,  0.5f,  0.5f,  0.0f,  0.0f,  1.0f,  1.0f,  1.0f,
        -0.5f,  0.5f,  0.5f,  0.0f,  0.0f,  1.0f,  0.0f,  1.0f,
        -0.5f, -0.5f,  0.5f,  0.0f,  0.0f,  1.0f,  0.0f,  0.0f,

        -0.5f,  0.5f,  0.5f, -1.0f,  0.0f,  0.0f,  1.0f,  0.0f,
        -0.5f,  0.5f, -0.5f, -1.0f,  0.0f,  0.0f,  1.0f,  1.0f,
        -0.5f, -0.5f, -0.5f, -1.0f,  0.0f,  0.0f,  0.0f,  1.0f,
        -0.5f, -0.5f, -0.5f, -1.0f,  0.0f,  0.0f,  0.0f,  1.0f,
        -0.5f, -0.5f,  0.5f, -1.0f,  0.0f,  0.0f,  0.0f,  0.0f,
        -0.5f,  0.5f,  0.5f, -1.0f,  0.0f,  0.0f,  1.0f,  0.0f,

         0.5f,  0.5f,  0.5f,  1.0f,  0.0f,  0.0f,  1.0f,  0.0f,
         0.5f,  0.5f, -0.5f,  1.0f,  0.0f,  0.0f,  1.0f,  1.0f,
         0.5f, -0.5f, -0.5f,  1.0f,  0.0f,  0.0f,  0.0f,  1.0f,
         0.5f, -0.5f, -0.5f,  1.0f,  0.0f,  0.0f,  0.0f,  1.0f,
         0.5f, -0.5f,  0.5f,  1.0f,  0.0f,  0.0f,  0.0f,  0.0f,
         0.5f,  0.5f,  0.5f,  1.0f,  0.0f,  0.0f,  1.0f,  0.0f,

        -0.5f, -0.5f, -0.5f,  0.0f, -1.0f,  0.0f,  0.0f,  1.0f,
         0.5f, -0.5f, -0.5f,  0.0f, -1.0f,  0.0f,  1.0f,  1.0f,
         0.5f, -0.5f,  0.5f,  0.0f, -1.0f,  0.0f,  1.0f,  0.0f,
         0.5f, -0.5f,  0.5f,  0.0f, -1.0f,  0.0f,  1.0f,  0.0f,
        -0.5f, -0.5f,  0.5f,  0.0f, -1.0f,  0.0f,  0.0f,  0.0f,
        -0.5f, -0.5f, -0.5f,  0.0f, -1.0f,  0.0f,  0.0f,  1.0f,

        -0.5f,  0.5f, -0.5f,  0.0f,  1.0f,  0.0f,  0.0f,  1.0f,
         0.5f,  0.5f, -0.5f,  0.0f,  1.0f,  0.0f,  1.0f,  1.0f,
         0.5f,  0.5f,  0.5f,  0.0f,  1.0f,  0.0f,  1.0f,  0.0f,
         0.5f,  0.5f,  0.5f,  0.0f,  1.0f,  0.0f,  1.0f,  0.0f,
        -0.5f,  0.5f,  0.5f,  0.0f,  1.0f,  0.0f,  0.0f,  0.0f,
        -0.5f,  0.5f, -0.5f,  0.0f,  1.0f,  0.0f,  0.0f,  1.0f
    };

    //########BINDS CUBE ####################//
    unsigned int VBO, cubeVAO;
    glGenVertexArrays(1, &cubeVAO);
    glGenBuffers(1, &VBO);

    glBindBuffer(GL_ARRAY_BUFFER, VBO); //Make VBO current buffer
    glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW); //Pushes CPU vertices in GPU VBO buffer

    glBindVertexArray(cubeVAO);//All subsequent buffer and attribute configs are stored in VAO

    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 8 * sizeof(float), (void*)0); //Configures the format of vertex data for the shader program
    glEnableVertexAttribArray(0); //Let VAO be used by the shader program
    glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 8  * sizeof(float), (void*)(3 * sizeof(float)));
    glEnableVertexAttribArray(1);
    glVertexAttribPointer(2, 2, GL_FLOAT, GL_FALSE, 8 * sizeof(float), (void*)(6 * sizeof(float)));
    glEnableVertexAttribArray(2);

    //########BINDS LIGHT CUBE ####################//
    unsigned int lightCubeVAO;
    glGenVertexArrays(1, &lightCubeVAO);
    glBindVertexArray(lightCubeVAO);

    glBindBuffer(GL_ARRAY_BUFFER, VBO);

    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 8 * sizeof(float), (void*)0); //Configures the format of vertex data for the shader program
    glEnableVertexAttribArray(0); //Let VAO be used by the shader program

    Texture diffuseMap("./assets/container2.png", ImageType::PNG);
    Texture specularMap("./assets/container2_specular.png", ImageType::PNG);

    cubeShader.use();
    cubeShader.setInt("material.diffuse", 0);
    cubeShader.setInt("material.specular", 1);

    std::vector<glm::vec3> cubePositions;
    generateRandomVec3Vector(10, cubePositions, -3.0f, 3.0f);

    std::vector<glm::vec3> pointLightPositions;
    generateRandomVec3Vector(4, pointLightPositions, -3.0f, 3.0f);

    std::vector<PointLight> pointLights;
    generatePointLight(pointLights, pointLightPositions, 4, -2.5f, 2.5f);
    
    //Check each loop to see if window was closed
    while(!glfwWindowShouldClose(window)){
        
        float currentFrame = static_cast<float>(glfwGetTime());
        deltaTime = currentFrame - lastFrame;
        lastFrame = currentFrame;

        //printframeRate(&currentFrame, &prevFrame);
        processInput(window);
        CAMERA.processInput(window, deltaTime);

        glClearColor(0.1f, 0.1f, 0.1f, 1.0f); //Specifies the color for the screen to be clear with
        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

        glm::mat4 projection = glm::perspective(glm::radians(90.0f), (float)SCR_WIDTH / (float)SCR_HEIGHT, 0.1f, 100.0f);
        glm::mat4 view = CAMERA.getCameraView();

        cubeShader.use();   
        cubeShader.setMat4("projection", projection);
        cubeShader.setMat4("view", view);
        
        cubeShader.setVec3("dirLight.direction", lightPos);
        cubeShader.setVec3("dirLight.ambient",  0.2f, 0.2f, 0.2f);
        cubeShader.setVec3("dirLight.diffuse", 0.5f, 0.5f, 0.5f);
        cubeShader.setVec3("dirLight.specular", 1.0f, 1.0f, 1.0f);

        for(unsigned int i = 0; i < pointLights.size(); i++){
            cubeShader.setVec3("pointLights["+std::to_string(i)+"].position", pointLights[i].position);

            cubeShader.setFloat("pointLights["+std::to_string(i)+"].constant", pointLights[i].constant);
            cubeShader.setFloat("pointLights["+std::to_string(i)+"].linear", pointLights[i].linear);
            cubeShader.setFloat("pointLights["+std::to_string(i)+"].quadratic", pointLights[i].quadratic);

            cubeShader.setVec3("pointLights["+std::to_string(i)+"].ambient", pointLights[i].ambient);
            cubeShader.setVec3("pointLights["+std::to_string(i)+"].diffuse", pointLights[i].diffuse);
            cubeShader.setVec3("pointLights["+std::to_string(i)+"].specular", pointLights[i].specular);
        }

        // material properties
        cubeShader.setVec3("material.specular", 0.5f, 0.5f, 0.5f);
        cubeShader.setFloat("material.shininess", 32.0f);

        
        for(unsigned int i = 0; i < cubePositions.size(); i++){
            glm::mat4 model = glm::mat4(1.0f);
            model = glm::translate(model, cubePositions[i]);
            float angle = 20.0f * i;
            model = glm::rotate(model, glm::radians(angle), glm::vec3(1.0f, 0.3f, 0.5f));
            cubeShader.setMat4("model", model);

            glActiveTexture(GL_TEXTURE0);
            glBindTexture(GL_TEXTURE_2D, diffuseMap.getTextureID());
            
            glActiveTexture(GL_TEXTURE1);
            glBindTexture(GL_TEXTURE_2D, specularMap.getTextureID());

            glBindVertexArray(cubeVAO); //Bind VAO with data
            glDrawArrays(GL_TRIANGLES, 0, 36);
        }

        //DRAW POINT LIGHTS
        pointLightCubeShader.use();
        pointLightCubeShader.setMat4("projection", projection);
        pointLightCubeShader.setMat4("view", view);

        for(unsigned int i = 0; i < pointLights.size(); i++){

            pointLightCubeShader.setVec3("lightColor", pointLights[i].ambient);

            glm::mat4 model = glm::mat4(1.0f);
            float angle = 20.0f * i;

            model = glm::translate(model, pointLights[i].position);
            model = glm::scale(model, glm::vec3(0.2f));
            pointLightCubeShader.setMat4("model", model);

            glBindVertexArray(cubeVAO); //Bind VAO with data
            glDrawArrays(GL_TRIANGLES, 0, 36);
        }

        // DRAWS THE SUN LIGHT
        lightCubeShader.use();
        lightCubeShader.setMat4("projection", projection);
        lightCubeShader.setMat4("view", view);

        glm::mat4 model = glm::mat4(1.0f);
        model = glm::translate(model, lightPos);
        model = glm::scale(model, glm::vec3(0.2f));
        lightCubeShader.setMat4("model", model);

        glBindVertexArray(lightCubeVAO);
        glDrawArrays(GL_TRIANGLES, 0, 36);

        glfwSwapBuffers(window); //Swaps 2d image of window
        glfwPollEvents(); //Check if a event is triggered(ie. key press)
    }

    glDeleteVertexArrays(1, &cubeVAO);
    glDeleteVertexArrays(1, &lightCubeVAO);
    glDeleteBuffers(1, &VBO);

    glfwTerminate();
    return 0;
}