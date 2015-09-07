//
// Created by Sergey Golubev on 07.09.15.
//

#include "FuncModel.h"

FuncModel::FuncModel(std::function<float(float, float)> func): func(func) { }

float FuncModel::operator()(float x, float y) {
    return func(x, y);
}

int FuncModel::generateMesh(float xFrom, float xTo, float yFrom, float yTo, float dx, float dy) {
    int xsize = (int)floorf((xTo - xFrom) / dx) + 1;
    int ysize = (int)floorf((yTo - yFrom) / dy) + 1;
    int isize = ysize * xsize * 6;
    glm::vec3 *vertices = new glm::vec3[ysize * xsize];
    glm::vec3 *normals = new glm::vec3[ysize * xsize];
    int *indices = new int[isize];

    int vcount = -1;
    int icount = -1;
    for (int y = 0; y < ysize; ++y) {
        for (int x = 0; x < xsize; ++x) {
            auto cx = xFrom + dx * x;
            auto cy = yFrom + dy * y;
            printf("%f\t%f\t%f\n", cx, cy, func(cx, cy));
            *(vertices + ++vcount) = glm::vec3(cx, cy, func(cx, cy));
            if (x > 0 && y > 0) {
                indices[++icount] = (y - 1) * xsize + x - 1;
                indices[++icount] = (y - 1) * xsize + x;
                indices[++icount] = y * xsize + x;
                indices[++icount] = y * xsize + x;
                indices[++icount] = y * xsize + x - 1;
                indices[++icount] = (y - 1) * xsize + x - 1;
            }
        }
    }

    for (int i = 0; i < isize; i += 6) {
        auto aInd = indices[i];
        auto bInd = indices[i + 1];
        auto cInd = indices[i + 2];
        auto dInd = indices[i + 3];
        auto eInd = indices[i + 4];
        auto fInd = indices[i + 5];
        auto a = vertices[aInd];
        auto b = vertices[bInd];
        auto c = vertices[cInd];
        auto d = vertices[dInd];
        auto e = vertices[eInd];
        auto f = vertices[fInd];
        normals[aInd] = glm::cross(a - b, a - c);
        normals[bInd] = glm::cross(b - a, b - c);
        normals[cInd] = glm::cross(c - b, c - a);
        normals[dInd] = glm::cross(d - f, d - e);
        normals[eInd] = glm::cross(e - d, e - f);
        normals[fInd] = glm::cross(f - d, f - e);
    }

    return 0;
}
