//
// Created by kirut on 9/29/2023.
//

#ifndef PROJECTBAHAMUT_MODEL_H
#define PROJECTBAHAMUT_MODEL_H


#include <vector>
#include "Shader.h"
#include "Mesh.h"
#include <assimp/mesh.h>
#include <assimp/scene.h>
#include <assimp/Importer.hpp>
#include <assimp/postprocess.h>

class Model {
public:
    explicit Model(const char *path) {
        modelPath = path;
        loadModel(path);
    }
    std::string modelPath;
    void draw(Shader &shader);
private:

    std::vector<Mesh> meshes;
    std::string directory;

    void loadModel(std::string path);
    void processNode(aiNode *node, const aiScene *scene);
    Mesh processMesh(aiMesh *mesh, const aiScene *scene);
    std::vector<MeshTexture> loadMaterialTextures(aiMaterial *mat, aiTextureType type, std::string typeName);
    static unsigned int TextureFromFile(const char *path, const std::string &directory);

    std::vector<Texture> textures_loaded;
};


#endif //PROJECTBAHAMUT_MODEL_H
