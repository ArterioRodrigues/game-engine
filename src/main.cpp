#include <pch/pch.h>

Camera camera;

//Used to callback when ever the screen is resized
void framebuffer_size_callback(GLFWwindow* window, int width, int height){
    glViewport(0, 0, width, height);
}
void processInput(GLFWwindow *window){
    if(glfwGetKey(window, GLFW_KEY_ESCAPE) == GLFW_PRESS)
        glfwSetWindowShouldClose(window, true);
}
void mouse_callback(GLFWwindow* window, double xpos, double ypos){
    camera.mouseCallback(window, xpos, ypos);
}


int main() {
    //Initialize GLFW
    glfwInit();
    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
    glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE);

    //Create a window 
    GLFWwindow* window = glfwCreateWindow(800, 600, "ARC", NULL, NULL);
    if(window == NULL){
        std::cout << "Failed to create GLFW window" << std::endl;
        glfwTerminate();
        return -1;
    }

    //Set created window as context aka current window
    glfwMakeContextCurrent(window);
    if(!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress)){
        std::cout << "Failed to initialize GLAD" << std::endl;
        return -1;
    }

    glfwSetInputMode(window, GLFW_CURSOR, GLFW_CURSOR_DISABLED);
    //Uses the framebuffer_size_callback function to resize the window
    glfwSetFramebufferSizeCallback(window, framebuffer_size_callback);
    glfwSetCursorPosCallback(window, mouse_callback);

    //Defines locations of the points that make up the shape
    float vertices[] = {
        /*  positions   */   /*texcoords*/
        -0.5f, -0.5f, -0.5f, 0.0f, 0.0f,
         0.5f, -0.5f, -0.5f, 1.0f, 0.0f,
         0.5f,  0.5f, -0.5f, 1.0f, 1.0f,
         0.5f,  0.5f, -0.5f, 1.0f, 1.0f,
        -0.5f,  0.5f, -0.5f, 0.0f, 1.0f,
        -0.5f, -0.5f, -0.5f, 0.0f, 0.0f,

        -0.5f, -0.5f,  0.5f, 0.0f, 0.0f,
         0.5f, -0.5f,  0.5f, 1.0f, 0.0f,
         0.5f,  0.5f,  0.5f, 1.0f, 1.0f,
         0.5f,  0.5f,  0.5f, 1.0f, 1.0f,
        -0.5f,  0.5f,  0.5f, 0.0f, 1.0f,
        -0.5f, -0.5f,  0.5f, 0.0f, 0.0f,

        -0.5f,  0.5f,  0.5f, 1.0f, 0.0f,
        -0.5f,  0.5f, -0.5f, 1.0f, 1.0f,
        -0.5f, -0.5f, -0.5f, 0.0f, 1.0f,
        -0.5f, -0.5f, -0.5f, 0.0f, 1.0f,
        -0.5f, -0.5f,  0.5f, 0.0f, 0.0f,
        -0.5f,  0.5f,  0.5f, 1.0f, 0.0f,

         0.5f,  0.5f,  0.5f, 1.0f, 0.0f,
         0.5f,  0.5f, -0.5f, 1.0f, 1.0f,
         0.5f, -0.5f, -0.5f, 0.0f, 1.0f,
         0.5f, -0.5f, -0.5f, 0.0f, 1.0f,
         0.5f, -0.5f,  0.5f, 0.0f, 0.0f,
         0.5f,  0.5f,  0.5f, 1.0f, 0.0f,

        -0.5f, -0.5f, -0.5f, 0.0f, 1.0f,
         0.5f, -0.5f, -0.5f, 1.0f, 1.0f,
         0.5f, -0.5f,  0.5f, 1.0f, 0.0f,
         0.5f, -0.5f,  0.5f, 1.0f, 0.0f,
        -0.5f, -0.5f,  0.5f, 0.0f, 0.0f,
        -0.5f, -0.5f, -0.5f, 0.0f, 1.0f,

        -0.5f,  0.5f, -0.5f, 0.0f, 1.0f,
         0.5f,  0.5f, -0.5f, 1.0f, 1.0f,
         0.5f,  0.5f,  0.5f, 1.0f, 0.0f,
         0.5f,  0.5f,  0.5f, 1.0f, 0.0f,
        -0.5f,  0.5f,  0.5f, 0.0f, 0.0f,
        -0.5f,  0.5f, -0.5f, 0.0f, 1.0f
        };

    //Defines the connection of the vertices
    unsigned int indices[] = {
        0, 1, 3,
        1, 2, 3
    };

     //Buffers 
    //VBO: Stores vertex data
    //VAO: Groups vertex attributes and enables efficient binding
    //EBO: Stores indices for element drawing
    unsigned int EBO, VBO, VAO;
    glGenBuffers(1, &EBO);
    glGenBuffers(1, &VBO);
    glGenVertexArrays(1, &VAO);

    //Buffer Binding, configures how vertex data is interpreted and associates it with th shader
    glBindVertexArray(VAO);//All subsequent buffer and attribute configs are stored in VAO
    glBindBuffer(GL_ARRAY_BUFFER, VBO); //Make VBO current buffer
    glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW); //Pushes CPU vertices in GPU VBO buffer
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBO); //Binds EBO
    glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(indices), indices, GL_STATIC_DRAW);//Pushes CPU indices to GPU EBO buffer 
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 5 * sizeof(float), (void*)0); //Configures the format of vertex data for the shader program
    glEnableVertexAttribArray(0); //Let VAO be used by the shader program
    glVertexAttribPointer(1, 2, GL_FLOAT, GL_FALSE, 5 * sizeof(float), (void*)(3 * sizeof(float)));
    glEnableVertexAttribArray(1);

    unsigned int texture1, texture2;
    glGenTextures(1, &texture1);
    glBindTexture(GL_TEXTURE_2D, texture1);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);

    int width, height, nrChannels;
    stbi_set_flip_vertically_on_load(true); 

    unsigned char *data = stbi_load("./textures/container.jpg", &width, &height, &nrChannels, 0);
    if (data) {
        glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, width, height, 0, GL_RGB, GL_UNSIGNED_BYTE, data);
        glGenerateMipmap(GL_TEXTURE_2D);
    }
    else {
        std::cout << "Failed to load texture" << std::endl;
    }
    stbi_image_free(data);

    glGenTextures(1, &texture2);
    glBindTexture(GL_TEXTURE_2D, texture2);

    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);

    stbi_set_flip_vertically_on_load(true); 
    
    data = stbi_load("./textures/awesomeface.png", &width, &height, &nrChannels, 0);
    if (data) {
        glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, width, height, 0, GL_RGBA, GL_UNSIGNED_BYTE, data);
        glGenerateMipmap(GL_TEXTURE_2D);
    
    }
    else {
        std::cout << "Failed to load texture" << std::endl;
    }
    stbi_image_free(data);

    //Setting up shader program and attaching textures
    Shader shader("./shaders/shader.vs", "./shaders/shader.fs");
    shader.use();
    shader.setFloat("ourColor", 1.0f);
    shader.setInt("texture1", 0);
    shader.setInt("texture2", 1);


    //Create a vec4 and matrix and translating it
    glm::mat4 model = glm::mat4(1.0f);
    model = glm::rotate(model, glm::radians(-55.0f), glm::vec3(1.0f, 0.0f, 0.0f));
    shader.setMat4("model", model);

    glm::mat4 projection;
    projection = glm::perspective(glm::radians(45.0f), 800.0f / 600.f, 0.1f, 100.0f);
    shader.setMat4("projection", projection);

    
    shader.setMat4("view", camera.getCameraView());
    
    glm::vec3 cubePositions[] = {
        glm::vec3( 0.0f, 0.0f, 0.0f),
        glm::vec3( 0.0f, 0.0f, 1.0f),
        glm::vec3(-1.0f, 0.0f, 1.0f),
        glm::vec3( 1.0f, 0.0f, 1.0f),
        glm::vec3(-1.0f, 0.0f, 0.0f),
        glm::vec3( 1.0f, 0.0f, 0.0f),
        glm::vec3( -1.0f, 0.0f, -1.0f),
        glm::vec3( 1.0f, 0.0f, -1.0f),
        glm::vec3( 0.0f, 0.0f, -1.0f),
        glm::vec3( -1.0f, 0.0f, 0.0f),
    };
    
    float deltaTime = 0.0f;
    float lastFrame = 0.0f;
    float currentFrame;

    //Check each loop to see if window was closed
    while(!glfwWindowShouldClose(window)){

        processInput(window);

        glClearColor(0.2f, 0.3f, 0.3f, 1.0f); //Specifies the color for the screen to be clear with
        glClear(GL_COLOR_BUFFER_BIT); //Clear screen with that color
        
        glActiveTexture(GL_TEXTURE0);
        glBindTexture(GL_TEXTURE_2D, texture1);
        glActiveTexture(GL_TEXTURE1);
        glBindTexture(GL_TEXTURE_2D, texture2);

        glEnable(GL_DEPTH_TEST);
        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
        
        shader.use();
        glBindVertexArray(VAO); //Bind VAO with data

        currentFrame = glfwGetTime();
        deltaTime = currentFrame - lastFrame;
        lastFrame = currentFrame;

        camera.processInput(window, deltaTime);
        shader.setMat4("view", camera.getCameraView());

        for(unsigned int i = 0; i < 10; i++){
            glm::mat4 model = glm::mat4(1.0f);
            model = glm::translate(model, cubePositions[i]);
            shader.setMat4("model", model);
            glDrawArrays(GL_TRIANGLES, 0, 36);
        }
        
        //glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, 0);
        glfwSwapBuffers(window); //Swaps 2d image of window
        glfwPollEvents(); //Check if a event is triggered(ie. key press)
    }

    glDeleteVertexArrays(1, &VAO);
    glDeleteBuffers(1, &VBO);
    glDeleteBuffers(1, &EBO);
    glfwTerminate();
    return 0;
}