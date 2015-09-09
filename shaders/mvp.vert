#version 330

layout(location = 0) in vec3 vertex;
layout(location = 1) in vec3 normal;

// Outputs mv-applied vector
out vec3 vert;
// Outputs mv-applied vector
out vec3 vertNormal;

uniform mat4 projMatrix;
uniform mat4 mvMatrix;
uniform mat4 cameraMatrix;
uniform mat3 normalMatrix;

void main() {
    highp vec4 curVertex = cameraMatrix * mvMatrix * vec4(vertex, 1.0);
    vertNormal = normalMatrix * normal;
    vert = curVertex.xyz;
    gl_Position = projMatrix * curVertex;
}
