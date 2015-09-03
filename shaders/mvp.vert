#version 150

in vec3 vertex;
out vec3 outColor;

uniform mat4 projMatrix;
uniform mat4 worldMatrix;
uniform mat4 cameraMatrix;

void main() {
    gl_Position = projMatrix * cameraMatrix * worldMatrix * vec4(vertex.xyz, 1.0);
    outColor = vec3(1.0, 1.0, 1.0);
}
