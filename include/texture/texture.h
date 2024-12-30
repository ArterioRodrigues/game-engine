#ifndef TEXTURE_H
#define TEXTURE_H
#include <pch/pch.h>

enum Type {
    JPG, PNG
};

class Texture {
    private:
        unsigned int mTextureID;
        int mWidth;
        int mHeight;
        int mChannels;

    public:
        Texture(const char* path, Type textureType);
        unsigned int getTextureID() const;
};

#endif