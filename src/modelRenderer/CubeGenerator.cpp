#include "CubeGenerator.h"

int Model::vSize() const {
    return vertices.size() * 3 * sizeof(GLfloat);
}

int Model::nSize() const {
    return normals.size() * 3 * sizeof(GLfloat);
}

int Model::iSize() const {
    return indices.size() * sizeof(int);;
}

int Model::iCount() const {
    return indices.size();
}

GLfloat* Model::getVertices() const {
    return const_cast<GLfloat *>((GLfloat *)vertices.data());
}

GLfloat* Model::getNormals() const {
    return const_cast<GLfloat *>((GLfloat *)normals.data());
}

int* Model::getIndices() const {
    return const_cast<int *>(indices.data());
}

Model::Model(const vector<vec3>& vertices, const vector<vec3>& normals, const vector<int>& indices):
    vertices(vertices), normals(normals), indices(indices) { }

Model::~Model() {
    vertices.clear();
    normals.clear();
    indices.clear();
}

CubeGenerator::CubeGenerator() {
    gvertices = vector<vec3>({
        vec3(-1, -1, 1),
        vec3(1, -1, 1),
        vec3(1, 1, 1),
        
        vec3(1, 1, 1),
        vec3(-1, 1, 1),
        vec3(-1, -1, 1),
        
        vec3(1, -1, 1),
        vec3(1, -1, -1),
        vec3(1, 1, -1),
        
        vec3(1, 1, -1),
        vec3(1, 1, 1),
        vec3(1, -1, 1),
        
        vec3(1, -1, -1),
        vec3(-1, -1, -1),
        vec3(-1, 1, -1),
        
        vec3(-1, 1, -1),
        vec3(1, 1, -1),
        vec3(1, -1, -1),
        
        vec3(-1, -1, -1),
        vec3(-1, -1, 1),
        vec3(-1, 1, 1),
        
        vec3(-1, 1, 1),
        vec3(-1, 1, -1),
        vec3(-1, -1, -1),
        
        vec3(1, -1, 1),
        vec3(-1, -1, 1),
        vec3(-1, -1, -1),
        
        vec3(-1, -1, -1),
        vec3(1, -1, -1),
        vec3(1, -1, 1),
        
        vec3(1, 1, -1),
        vec3(-1, 1, -1),
        vec3(-1, 1, 1),
        
        vec3(-1, 1, 1),
        vec3(1, 1, 1),
        vec3(1, 1, -1)
    });
    
    gnormals = vector<vec3>({
        vec3(0, 0, 1),
        vec3(0, 0, 1),
        vec3(0, 0, 1),

        vec3(0, 0, 1),
        vec3(0, 0, 1),
        vec3(0, 0, 1),

        vec3(1, 0, 0),
        vec3(1, 0, 0),
        vec3(1, 0, 0),

        vec3(1, 0, 0),
        vec3(1, 0, 0),
        vec3(1, 0, 0),

        vec3(0, 0, -1),
        vec3(0, 0, -1),
        vec3(0, 0, -1),

        vec3(0, 0, -1),
        vec3(0, 0, -1),
        vec3(0, 0, -1),

        vec3(-1, 0, 0),
        vec3(-1, 0, 0),
        vec3(-1, 0, 0),

        vec3(-1, 0, 0),
        vec3(-1, 0, 0),
        vec3(-1, 0, 0),

        vec3(0, -1, 0),
        vec3(0, -1, 0),
        vec3(0, -1, 0),

        vec3(0, -1, 0),
        vec3(0, -1, 0),
        vec3(0, -1, 0),

        vec3(0, 1, 0),
        vec3(0, 1, 0),
        vec3(0, 1, 0),

        vec3(0, 1, 0),
        vec3(0, 1, 0),
        vec3(0, 1, 0)
    });
}

Model* CubeGenerator::next(const vec3& scaleVec, const mat4& transform) {
    // Transform matrix with per-axis scale factor
    mat4 A = transform * glm::diagonal4x4(vec4(scaleVec, 1.0));
    // Affine matrix for normals rotation (but not translation)
    mat3 B = mat3(transform);
    vector<vec3> vertices, normals;
    vector<int> indices;
    for (int i = 0; i < gvertices.size(); ++i) {
        auto vec = vec3(A * vec4(gvertices[i], 1.0));
        vertices.push_back(vec);
    }
    for (int i = 0; i < gnormals.size(); ++i) {
        auto vec = B * gnormals[i];
        normals.push_back(vec);
    }
    for (int i = 0; i < 36; ++i) {
        indices.push_back(i);
    }
    return new Model(vertices, normals, indices);
}

Model* CubeGenerator::next(Model* toMergeWith, const vec3& scaleVec, const mat4& transform) {
    int lastIdx = toMergeWith->indices[toMergeWith->indices.size() - 1] + 1;
    for (int i = 0; i < 36; ++i) {
        toMergeWith->indices.push_back(i + lastIdx);
    }
    // Transform matrix with per-axis scale factor
    mat4 A = transform * glm::diagonal4x4(vec4(scaleVec, 1.0));
    // Affine matrix for normals rotation (but not translation)
    mat3 B = mat3(transform);
    vector<vec3> vertices, normals;
    vector<int> indices;
    for (int i = 0; i < gvertices.size(); ++i) {
        auto vec = vec3(A * vec4(gvertices[i], 1.0));
        toMergeWith->vertices.push_back(vec);
    }
    for (int i = 0; i < gnormals.size(); ++i) {
        auto vec = B * gnormals[i];
        toMergeWith->normals.push_back(vec);
    }
    return toMergeWith;
}
