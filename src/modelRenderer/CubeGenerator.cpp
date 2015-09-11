#include <stdio.h>
#include <string.h>
#include "CubeGenerator.h"
#include <glm/gtc/type_ptr.hpp>
#include <glm/gtc/matrix_transform.hpp>

using namespace glm;

int Model::vSize() {
    return vCount * sizeof(vertex_t);
}

int Model::nSize() {
    return nCount * sizeof(vertex_t);
}

int Model::iSize() {
    return triCount * sizeof(tri_t);
}

int Model::iCount() {
    return triCount * 3;
}

Model::Model(int vCount, int nCount, int triCount) : vCount(vCount), nCount(nCount), triCount(triCount) {
    vertices = new GLfloat[vCount * 3];
    normals = new GLfloat[nCount * 3];
    indices = new int[triCount * 3];
}

Model::~Model() {
    delete[] vertices;
    delete[] indices;
    delete[] normals;
}

CubeGenerator::CubeGenerator() {

}

Model* CubeGenerator::next() {
    Model* model = new Model(36, 36, 12);

    mat4 id = mat4(1.0f);
    vec3 tr = vec3(5, 0, 0);

    for (int i = 0; i < model->vCount; ++i) {
        vertex_t vertex = vertices[i];
        vec3 curVec(vertex.x, vertex.y, vertex.z);
        //curVec = vec3(translate(id, tr) * vec4(curVec, 1.0));
        memcpy(&model->vertices[i * 3], value_ptr(curVec), sizeof(vertex_t));
    }

    //memcpy(model->vertices, vertices, sizeof(vertices));
    memcpy(model->normals, normals, sizeof(normals));
    memcpy(model->indices, indices, sizeof(indices));

    return model;
}
