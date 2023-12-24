//
// Created by kirut on 9/29/2023.
//

#ifndef PROJECTBAHAMUT_MODEL_H
#define PROJECTBAHAMUT_MODEL_H


#include <vector>
#include "Shader.h"
#include "Mesh.h"
#include "Transformation.h"
#include <assimp/mesh.h>
#include <assimp/scene.h>
#include <assimp/Importer.hpp>
#include <assimp/postprocess.h>

class Model {
public:
    Transform transform;

    explicit Model(const char *path) {
        modelPath = path;
        loadModel(path);
    }

    virtual void draw(Shader &shader);

    std::string modelPath;
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
