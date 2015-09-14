#pragma once

#include <stdio.h>
#include <string.h>
#include <random>
#include <GL/glew.h>
#include <glm/glm.hpp>
#include <glm/gtc/type_ptr.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtx/matrix_operation.hpp>

using namespace std;
using namespace glm;

struct vertex_t {
    GLfloat x;
    GLfloat y;
    GLfloat z;

    vertex_t(GLfloat x, GLfloat y, GLfloat z): x(x), y(y), z(z) { }
};

struct tri_t {
    int indices[3];

    tri_t(int idx1, int idx2, int idx3) {
        indices[0] = idx1;
        indices[1] = idx2;
        indices[2] = idx3;
    }
};

class Model {
public:
    vector<vec3> vertices;
    vector<vec3> normals;
    vector<int> indices;

    int vSize() const;
    int nSize() const;
    int iSize() const;
    int iCount() const;

    GLfloat* getVertices() const;
    GLfloat* getNormals() const;
    int* getIndices() const;

    Model(const vector<vec3>& vertices, const vector<vec3>& normals, const vector<int>& indices);
    ~Model();
};

class CubeGenerator {
private:
    vector<vec3> gvertices;
    vector<vec3> gnormals;

public:
    CubeGenerator();
    Model* next(const vec3& scaleVec = vec3(1.0), const mat4& transform = mat4(1.0));
    Model* next(Model* toMergeWith, const vec3& scaleVec = vec3(1.0), const mat4& transform = mat4(1.0));
};