//
// Created by kirut on 9/24/2024.
//

#ifndef PROJECTBAHAMUT_GLTFIMPORTER_H
#define PROJECTBAHAMUT_GLTFIMPORTER_H


#include <fstream>
#include <nlohmann/json.hpp>
#include "BaseModelImporter.h"
using json = nlohmann::json;

namespace glTF {
    enum gltfType {
        Json,
        Binary
    };

    struct Asset;
    struct Camera;
    struct Accessor;
    struct Skin;
    struct Sampler;
    struct BufferView;
    struct Image;
    struct Texture;
    struct TextureInfo;
    struct Material;
    struct Mesh;
    struct Node;
    struct Scene;
    struct Buffer;

    struct Asset {
        std::string *copyright = nullptr;
        std::string *generator = nullptr;
        std::string version;
        std::string *minVersion = nullptr;
        // extensions
        // extras
    };

    struct Camera {
        struct Orthographic {
            float xmag;
            float ymag;
            float zfar;
            float znear;
            // extensions
            // extras
        };
        struct Perspective {
            float *aspectRatio = nullptr;
            float yfov;
            float *zfar = nullptr;
            float znear;
            // extensions
            // extras
        };

        Orthographic *orthographic = nullptr;
        Perspective *perspective = nullptr;
        std::string *type = nullptr;
        std::string name;
        // extensions
        // extras
    };

    struct Accessor {
        struct Sparse {
            struct Indices {
                BufferView *bufferView;
                unsigned int byteOffset = 0;
                unsigned int componentType; // enum
                // extensions
                // extras
            };
            struct Values {
                BufferView *bufferView;
                unsigned int byteOffset = 0;
                // extensions
                // extras
            };

            unsigned int count;
            Indices indices;
            Values values;
            // extensions
            // extras
        };

        BufferView *bufferView = nullptr;
        unsigned int byteOffset = 0;
        unsigned int componentType; // enum
        bool normalized = false;
        unsigned int count;
        std::string type;
        float *max = nullptr;
        float *min = nullptr;
        Sparse *sparse = nullptr;
        std::string *name = nullptr;
        // extensions
        // extras
    };

    struct Skin {
        Accessor *inverseBindMatrices = nullptr;
        Node *skeleton = nullptr;
        Node *joints;
        std::string *name = nullptr;
        // extensions
        // extras
    };

    struct Sampler {
        int *magFilter = nullptr;
        int *minFilter = nullptr;
        int wrapS = 10497;
        int wrapT = 10497;
        std::string *name = nullptr;
        // extension
        // extra
    };

    struct BufferView {
        Buffer *buffer; // index
        unsigned int byteOffset = 0;
        unsigned int byteLength;
        unsigned int *byteStride = nullptr;
        unsigned int *target = nullptr;
        std::string *name = nullptr;
        // extensions
        // extras
    };

    struct Image {
        std::string *uri = nullptr;
        std::string *mimeType = nullptr;
        BufferView *bufferView;
        std::string *name = nullptr;
        // extensions
        // extras
    };

    struct Texture {
        Sampler *sampler = nullptr;
        Image *source = nullptr;
        std::string *name = nullptr;
        // extension
        // extras
    };

    struct TextureInfo {
        Texture *index;
        unsigned int texCoord; // index
        // extensions
        // extras
    };

    struct Material {
        struct PBRMetallicRoughness {
            float baseColorFactor[4] = {1,1,1,1};
            TextureInfo *baseColorTexture = nullptr;
            float metallicFactor = 1;
            float roughnessFactor = 1;
            TextureInfo *metallicRoughnessTexture = nullptr;
            // extensions
            // extras
        };
        struct NormalTextureInfo {
            Texture *index;
            unsigned int texCoord = 0; // index
            float scale = 1;
            // extensions
            // extras
        };
        struct OcclusionTextureInfo {
            Texture *index;
            unsigned int texCoord = 0; // index
            float strength = 1;
            // extensions
            // extras
        };

        std::string *name = nullptr;
        // extensions
        // extras
        PBRMetallicRoughness *pbrMetallicRoughness = nullptr;
        NormalTextureInfo *normalTexture = nullptr;
        OcclusionTextureInfo *occlusionTexture = nullptr;
        TextureInfo *emissiveTexture = nullptr;
        float emissiveFactor[3] = {0,0,0};
        std::string alphaMode = "OPAQUE";
        float alphaCutoff = 0.5f;
        bool doubleSided = false;
    };

    struct Mesh {
        struct Primitive {
            std::vector<float> positions;
            std::vector<float> normals;
            std::vector<float> texCoords;
            std::vector<unsigned int> indices;
            Material *material = nullptr;
            unsigned int mode = 4;
            // targets
            // extensions
            // extras
        };

        std::vector<Primitive> primitives;
        float *weights = nullptr;
        std::string *name = nullptr;
        // extensions
        // extras
    };

    struct Node {
        Camera *camera = nullptr;
        Node *children = nullptr;
        Skin *skin = nullptr;
        float matrix[4][4] = {{1,0,0,0}, {0,1,0,0}, {0,0,1,0}, {0,0,0,1}}; // 4x4 transform matrix
        Mesh *mesh = nullptr;
        float rotation[4] = {0,0,0,1}; // Quaternion (x,y,z,w)
        float scale[3] = {1,1,1}; // x,y,z
        float translation[3] = {0,0,0}; // xyz
        float *weights = nullptr;
        std::string *name = nullptr;
        // extension
        // extras
    };

    struct Scene {
        std::string *name = nullptr;
        Node *nodes = nullptr;
        // extensions
        // extras
    };

    struct Buffer {
        std::string *uri = nullptr;
        std::vector<uint8_t> parsedUri;
        unsigned int byteLength;
        std::string *name = nullptr;
        // extensions
        // extras
    };


    class Importer : public BaseModelImporter {
        std::vector<Accessor> accessors;
        std::vector<Buffer> buffers;

        static void jsonInterpreter(std::ifstream &fileStream);
        static Scene parseScenes(const json& glTFJson);
        static Node parseNodes(const json& glTFJson, unsigned int index);
        static Mesh* parseMesh(const json& glTFJson, unsigned int index);
        static Accessor parseAccessor(const json& glTFJson, unsigned int index);
        static BufferView* parseBufferView(const json& glTFJson, unsigned int index);
        static Buffer parseBuffer(const json& glTFJson, unsigned int index);
        static std::vector<uint8_t> parseUri(const std::string& uri);
    public:
        Importer(std::ifstream &fileStream, gltfType type);
    };
}



#endif //PROJECTBAHAMUT_GLTFIMPORTER_H
