#ifndef MODEL_H
#define MODEL_H

#include <pch/pch.h>

class Model {
public:
    Model(char *path){
        loadModel(path);
    }
    void Draw(Shader &shader);

private:
    std::vector<Mesh> meshes;
    std::string directory;
    void loadModel(std::string path);
    void processNode(aiNode *node, const aiScene *scene);
    Mesh processMesh(aiMesh *mesh, const aiScene *scene);
    std::vector<Texture> loadMaterialTextures(aiMaterial *mat, aiTextureType type, std::string typeName);
};

#endif