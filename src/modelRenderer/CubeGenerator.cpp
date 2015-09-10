#include <stdio.h>
#include <string.h>
#include "CubeGenerator.h"

using namespace glm;

Model::~Model() {
    delete[] vertices;
    delete[] indices;
    delete[] normals;
}

CubeGenerator::CubeGenerator() {

}

Model* CubeGenerator::next() {
    Model* model = new Model;
    model->normals = new GLfloat[model->ncount];
    model->vertices = new GLfloat[model->vcount];
    model->indices = new int[model->icount];

    memcpy(model->vertices, vertices, model->vtsize);
    memcpy(model->indices, indices, model->itsize);

    for (int i = 0; i < model->icount; i += 3) {
        printf("%i\n", i);
        vec3 a(vertices[indices[i * 3]], vertices[indices[i * 3 + 1]], vertices[indices[i * 3 + 2]]);
        vec3 b(vertices[indices[(i + 1) * 3]], vertices[indices[(i + 1) * 3 + 1]], vertices[indices[(i + 1) * 3 + 2]]);
        vec3 c(vertices[indices[(i + 2) * 3]], vertices[indices[(i + 2) * 3 + 1]], vertices[indices[(i + 2) * 3 + 2]]);

        vec3 an = normalize(cross(a - b, a - c));
        vec3 bn = normalize(cross(b - a, b - c));
        vec3 cn = normalize(cross(c - b, c - a));

        model->normals[indices[i * 3]] = an.x;
        model->normals[indices[i * 3 + 1]] = an.y;
        model->normals[indices[i * 3 + 2]] = an.z;
        model->normals[indices[(i + 1) * 3]] = bn.x;
        model->normals[indices[(i + 1) * 3 + 1]] = bn.y;
        model->normals[indices[(i + 1) * 3 + 2]] = bn.z;
        model->normals[indices[(i + 2) * 3]] = cn.x;
        model->normals[indices[(i + 2) * 3 + 1]] = cn.y;
        model->normals[indices[(i + 3) * 3 + 2]] = cn.z;
    }

    return model;
}
