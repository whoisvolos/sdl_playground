#pragma once

#include <GL/glew.h>
#include <glm/glm.hpp>

class Model {
public:
    GLfloat* vertices;
    int* indices;
    GLfloat* normals;

    const int vsize = sizeof(GLfloat);
    const int isize = sizeof(int);
    const int nsize = sizeof(GLfloat);

    const int vcount = 8 * 3;
    const int icount = 12 * 3;
    const int ncount = 8 * 3;

    const int vtsize = vcount * vsize;
    const int itsize = icount * isize;
    const int ntsize = ncount * nsize;


    ~Model();
};

class CubeGenerator {
private:
    GLfloat vertices[24] = {
            -1, -1, 1,
            1, -1, 1,
            1, 1, 1,
            -1, 1, 1,
            -1, -1, -1,
            1, -1, -1,
            1, 1, -1,
            -1, 1, -1
    };

    int indices[36] = {
            0, 1, 2,
            2, 3, 0,
            1, 5, 6,
            6, 2, 1,
            4, 5, 7,
            7, 6, 5,
            4, 0, 3,
            3, 7, 4,
            1, 0, 4,
            4, 5, 1,
            6, 7, 3,
            3, 2, 6
    };

    int prevIdx = 0;

public:
    CubeGenerator();
    Model* next();
};