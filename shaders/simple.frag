#version 150

in vec3 outColor;
out highp vec4 glFragColor;

void main() {
    glFragColor = vec4(outColor, 1.0);
}
