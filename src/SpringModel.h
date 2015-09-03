#pragma once

#include <glm/glm.hpp>

using namespace glm;

class SpringModel {
private:
    float km;

    vec2 x;
    vec2 center;
    vec2 speed;

public:
    SpringModel(float k, float m, vec2 center, vec2 x);
    SpringModel();

    vec2 coords();
    void update(float dt);
};
