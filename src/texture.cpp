#include <texture/texture.h>

Texture::Texture(const char* path, Type textureType){
    glGenTextures(1, &this->mTextureID);
    glBindTexture(GL_TEXTURE_2D, this->mTextureID);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);

    stbi_set_flip_vertically_on_load(true); 

    unsigned char *data = stbi_load(path, &this->mWidth, &this->mHeight, &this->mChannels, 0);
    if (data) {
        if(textureType == JPG)
            glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, this->mWidth, this->mHeight, 0, GL_RGB, GL_UNSIGNED_BYTE, data);
        else if(textureType == PNG)
            glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, this->mWidth, this->mHeight, 0, GL_RGBA, GL_UNSIGNED_BYTE, data);
        glGenerateMipmap(GL_TEXTURE_2D);
    }
    else {
        std::cout << "Failed to load texture" << std::endl;
    }

    stbi_image_free(data);
}

unsigned int Texture::getTextureID() const {
    return this->mTextureID;
}