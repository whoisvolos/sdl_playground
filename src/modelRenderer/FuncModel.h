#pragma once

#include <functional>
#include <vector>
#include <glm/glm.hpp>

class FuncModel {
private:
    std::function<float(float, float)> func;

public:
    FuncModel(std::function<float(float, float)> func);
    float operator()(float x, float y);
    int generateMesh(float xFrom, float xTo, float yFrom, float yTo, float dx, float dy);
};