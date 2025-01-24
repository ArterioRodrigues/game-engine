#ifndef TEXTURE_H
#define TEXTURE_H
#include <pch/pch.h>

enum ImageType {
    JPG, PNG
};

class Texture {
    private:
        unsigned int mTextureID;
        int mWidth;
        int mHeight;
        int mChannels;

    public:
        Texture(const char* path, ImageType textureType = JPG);
        unsigned int getTextureID() const;
};

#endif