#include "SpringModel.h"

SpringModel::SpringModel() {}

SpringModel::SpringModel(float k, float m, vec2 center, vec2 x):
        km(-k/m),
        center(center),
        x(x),
        speed(vec2(0, 0)) { }

vec2 SpringModel::coords() {
    return x;
}

void SpringModel::update(float dt) {
    x = x + speed * dt;
    speed = speed + (x - center) * km * dt - speed * dt * 5.0f;
}
