#pragma once

#include <GL/glew.h>
#include <glm/glm.hpp>

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
    GLfloat* vertices;
    int* indices;
    GLfloat* normals;

    int vCount;
    int nCount;
    int triCount;

    int vSize();
    int nSize();
    int iSize();
    int iCount();

    Model(int vCount, int nCount, int triCount);
    ~Model();
};

class CubeGenerator {
private:
    vertex_t vertices[36] = {
        vertex_t(-1, -1, 1),
        vertex_t(1, -1, 1),
        vertex_t(1, 1, 1),

        vertex_t(1, 1, 1),
        vertex_t(-1, 1, 1),
        vertex_t(-1, -1, 1),

        vertex_t(1, -1, 1),
        vertex_t(1, -1, -1),
        vertex_t(1, 1, -1),

        vertex_t(1, 1, -1),
        vertex_t(1, 1, 1),
        vertex_t(1, -1, 1),

        vertex_t(1, -1, -1),
        vertex_t(-1, -1, -1),
        vertex_t(-1, 1, -1),

        vertex_t(-1, 1, -1),
        vertex_t(1, 1, -1),
        vertex_t(1, -1, -1),

        vertex_t(-1, -1, -1),
        vertex_t(-1, -1, 1),
        vertex_t(-1, 1, 1),

        vertex_t(-1, 1, 1),
        vertex_t(-1, 1, -1),
        vertex_t(-1, -1, -1),

        vertex_t(1, -1, 1),
        vertex_t(-1, -1, 1),
        vertex_t(-1, -1, -1),

        vertex_t(-1, -1, -1),
        vertex_t(1, -1, -1),
        vertex_t(1, -1, 1),

        vertex_t(1, 1, -1),
        vertex_t(-1, 1, -1),
        vertex_t(-1, 1, 1),

        vertex_t(-1, 1, 1),
        vertex_t(1, 1, 1),
        vertex_t(1, 1, -1),
    };

    vertex_t normals[36] = {
        vertex_t(0, 0, 1),
        vertex_t(0, 0, 1),
        vertex_t(0, 0, 1),

        vertex_t(0, 0, 1),
        vertex_t(0, 0, 1),
        vertex_t(0, 0, 1),

        vertex_t(1, 0, 0),
        vertex_t(1, 0, 0),
        vertex_t(1, 0, 0),

        vertex_t(1, 0, 0),
        vertex_t(1, 0, 0),
        vertex_t(1, 0, 0),

        vertex_t(0, 0, -1),
        vertex_t(0, 0, -1),
        vertex_t(0, 0, -1),

        vertex_t(0, 0, -1),
        vertex_t(0, 0, -1),
        vertex_t(0, 0, -1),

        vertex_t(-1, 0, 0),
        vertex_t(-1, 0, 0),
        vertex_t(-1, 0, 0),

        vertex_t(-1, 0, 0),
        vertex_t(-1, 0, 0),
        vertex_t(-1, 0, 0),

        vertex_t(0, -1, 0),
        vertex_t(0, -1, 0),
        vertex_t(0, -1, 0),

        vertex_t(0, -1, 0),
        vertex_t(0, -1, 0),
        vertex_t(0, -1, 0),

        vertex_t(0, 1, 0),
        vertex_t(0, 1, 0),
        vertex_t(0, 1, 0),

        vertex_t(0, 1, 0),
        vertex_t(0, 1, 0),
        vertex_t(0, 1, 0)
    };

    tri_t indices[12] = {
        tri_t(0, 1, 2),
        tri_t(3, 4, 5),
        tri_t(6, 7, 8),
        tri_t(9, 10, 11),
        tri_t(12, 13, 14),
        tri_t(15, 16, 17),
        tri_t(18, 19, 20),
        tri_t(21, 22, 23),
        tri_t(24, 25, 26),
        tri_t(27, 28, 29),
        tri_t(30, 31, 32),
        tri_t(33, 34, 35)
    };

public:
    CubeGenerator();
    Model* next();
};